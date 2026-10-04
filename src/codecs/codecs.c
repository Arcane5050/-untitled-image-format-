#include "codecs.h"

#include "v2.0.h"

codec generate_latest_codec(void) {
    return (codec){
        .flags_handler    = &v2_0_flags,
        .metadata_handler = &v2_0_metadata,
        .palette_handler  = &v2_0_palette,
        .pixel_handler    = &v2_0_pixels,
    };
}

img run_codec(char* data, size_t data_size, const codec codec) {
    img result;
    file_access access = malloc(sizeof(file_access));
    access->data = data;
    const char* const start_pos = access->data;
    const uint16_t raw_flags = (uint16_t)(access->data[0] << 8) + (uint16_t)access->data[1];
    const flags flags = codec.flags_handler(raw_flags);
    access->data += 2;
    result.metadata = codec.metadata_handler(access, flags);
    const palette palette = codec.palette_handler(access, flags);
    const size_t raw_pixel_size = data_size - (access->data - start_pos);
    result.pixel_data = codec.pixel_handler(access, raw_pixel_size, palette, flags);
    printf("%p\n", palette.data);
    free(palette.data);
    free(access);
    return result;
}