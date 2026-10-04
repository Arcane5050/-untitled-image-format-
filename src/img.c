#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "converting.h"
#include "codecs/codecs.h"
#include "types.h"

static int strsame(const char* str1, const char* str2) {
    return strcmp(str1, str2) == 0;
}

int main(const int argc, char** argv) {
    if (argc == 1) {
        printf("usage: img [--version] <to|from> [src<.jpg|.png>] <dest<.png|.jpg>>\n");
        return 0;
    }
    if (strsame(argv[1], "--version")) {
        printf("<untitled image format> version " VERSION "\ncompiled at " __TIME__ " on " __DATE__ "\n");
        return 0;
    }
    if (strsame(argv[1], "to")) {

    } else if (strsame(argv[1], "from")) {
        FILE* in = fopen(argv[2], "rb");
        if (in == NULL) {
            printf(PREFIX "file could not open\n");
            return 1;
        }
        fseek(in, 0L, SEEK_END);
        size_t length = ftell(in);
        rewind(in);
        char* data = malloc(length);
        fread(data, length, 1, in);
        fclose(in);
        codec default_codec = generate_latest_codec();
        img image = run_codec(data, length, default_codec);
        free(data);
        char* pixel_data = calloc(1, (image.metadata.width * image.metadata.height) * 4);
        img_to_raw_data(image, pixel_data);
        stbi_write_png(argv[3], image.metadata.width, image.metadata.height, 4, pixel_data, 4);
        printf(PREFIX "converted image successfully\n");
    } else {
        printf(PREFIX "expected 'to' or 'from' as argument 1\n");
        return 1;
    }

    return 0;
}
