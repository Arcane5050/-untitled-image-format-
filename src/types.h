#pragma once

#include <stdint.h>
#define VERSION "2.0-alpha"
#define PREFIX "img: "

#define ALPHA_FLAG       0b0000000000000001
#define LEGACY_SIZE_FLAG 0b0000000000000010


typedef struct {
    uint16_t width;
    uint16_t height;
} metadata;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} RGBA;

typedef struct {
    uint8_t alpha;
    uint8_t legacy_size;
} flags;

typedef struct {
    uint16_t size;
    RGBA* data;
} palette;

typedef struct {
    metadata metadata;
    RGBA* pixel_data;
} img;

typedef struct {
    char* data;
} *file_access;

typedef struct {
    flags (*flags_handler)(uint16_t raw_flags);
    metadata (*metadata_handler)(file_access raw_metadata, flags flags);
    palette (*palette_handler)(file_access raw_palette, flags flags);
    RGBA* (*pixel_handler)(file_access raw_pixels, size_t raw_pixel_size, palette palette, flags flags);
} codec;