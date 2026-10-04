#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "../types.h"

inline extern flags v2_0_flags(const uint16_t raw_flags) {
    flags result;
    if (raw_flags & ALPHA_FLAG) {
        result.alpha = 1;
    } else {
        result.alpha = 0;
    }
    if (raw_flags & LEGACY_SIZE_FLAG) {
        result.legacy_size = 1;
    } else {
        result.legacy_size = 0;
    }
    return result;
}
inline extern metadata v2_0_metadata(file_access raw_metadata, const flags flags) {
    metadata result;
    uint16_t width = (uint16_t)*raw_metadata->data << 8;
    if (!flags.legacy_size) {
        width += (uint16_t)*++raw_metadata->data;
    }
    uint16_t height = (uint16_t)*++raw_metadata->data << 8;
    if (!flags.legacy_size) {
        height += (uint16_t)*++raw_metadata->data;
    }
    result.width = width;
    result.height = height;
    raw_metadata->data++;
    return result;
}
inline extern palette v2_0_palette(file_access raw_palette, const flags flags) {
    palette result;
    const uint16_t size = (uint8_t)*raw_palette->data + 1;
    result.data = malloc(size * sizeof(RGBA));
    printf("%p\n", result.data);
    if (result.data == NULL) {
        printf(PREFIX "unknown memory issue\n");
        exit(1);
    }
    result.data[0] = (RGBA){
        .r = 0,
        .g = 0,
        .b = 0,
        .a = 0,
    };
    result.size = 1;
    raw_palette->data++;
    while (result.size != size) {
        RGBA current_pixel;
        current_pixel.r = (uint8_t)*raw_palette->data;
        raw_palette->data++;
        current_pixel.g = (uint8_t)*raw_palette->data;
        raw_palette->data++;
        current_pixel.b = (uint8_t)*raw_palette->data;
        raw_palette->data++;
        if (flags.alpha) {
            current_pixel.a = (uint8_t)*raw_palette->data;
            raw_palette->data++;
        } else {
            current_pixel.a = 255;
        }
        result.data[result.size] = current_pixel;
        result.size++;
    }
    return result;
}
inline extern RGBA* v2_0_pixels(file_access raw_pixels, const size_t raw_pixel_size, palette palette, flags flags) {
    RGBA* pixels = malloc(raw_pixel_size);
    const char* start = raw_pixels->data;
    size_t pixel_number = raw_pixels->data - start;
    while (pixel_number < raw_pixel_size - 1) {
        pixel_number = raw_pixels->data - start;
        if (palette.size <= *raw_pixels->data) {
            printf(PREFIX "palette index at %zu is out of range\n", pixel_number);
            exit(1);
        }
        RGBA palette_color = palette.data[*raw_pixels->data];
        pixels[pixel_number] = palette_color;
        raw_pixels->data++;
    }
    return pixels;
}