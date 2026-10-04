#include "converting.h"

#include "types.h"

void mcimg_to_raw_data(img img, char* dest) {
    const size_t max = (img.metadata.width * img.metadata.height) * 4;
    size_t pixel_index = 0;
    for (size_t i = 0; i < max; i++) {
        char written;
        if (i % 4 == 0) {
            written = (char)img.pixel_data[pixel_index].r;
        } else if (i % 4 == 1) {
            written = (char)img.pixel_data[pixel_index].g;
        } else if (i % 4 == 2) {
            written = (char)img.pixel_data[pixel_index].b;
        } else {
            written = (char)img.pixel_data[pixel_index].a;
            pixel_index++;
        }
        dest[i] = written;
    }
}