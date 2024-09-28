#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct imageInfo {
    unsigned long height;
    unsigned long width;
    unsigned long size;
    unsigned long image_offset;
    unsigned char bmp_header[54];
};

unsigned char *convertToBmp(long *matrix, unsigned long height, unsigned long width){
    unsigned char *pixelData = (unsigned char *)malloc(height * width * 3 * sizeof(unsigned char));
    size_t index = 0;
    for (unsigned long i = height - 1; i != (unsigned long)-1; i--) {
        for (unsigned long j = 0; j < width; j++) {
            if (matrix[i * width + j] == 1) {
                pixelData[index] = 0;
                pixelData[index + 1] = 0;
                pixelData[index + 2] = 0;
            } else {
                pixelData[index] = 255;
                pixelData[index + 1] = 255;
                pixelData[index + 2] = 255;
            }
            index += 3;
        }
    }
    return pixelData;
}

long *allocateArray(unsigned long height, unsigned long width) {
    long *arr = (long *)malloc(height * width * sizeof(long));
    if (arr == NULL)
        return NULL;
    return arr;
}

int countNeighbors(long *arr, unsigned long x, unsigned long y, unsigned long width, unsigned long height) {
    int sum = 0;
    for (long i = x - 1; i <= x + 1; i++) {
        for (long j = y - 1; j <= y + 1; j++) {
            if (i >= 0 && i < height && j >= 0 && j < width) {
                sum += arr[i * width + j];
            }
        }
    }
    if (arr[x * width + y] == 1)
        sum--;
    return sum;
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "ERROR, no arguments");
        return 1;
    }
    struct imageInfo info;
    FILE *image;
    unsigned long dump_freq = 1;
    unsigned long max_iter = 1;
    char *dirName;
    long *cur_gen;
    long *next_gen;

    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "--input") == 0) {
            image = fopen(argv[i + 1], "rb");
            if (image == NULL) {
                printf("Image can't open");
                return 0;
            }
        } else if (strcmp(argv[i], "--output") == 0)
            dirName = argv[i + 1];
        else if (strcmp(argv[i], "--max_iter") == 0)
            max_iter = strtol(argv[i + 1], NULL, 10);
        else if (strcmp(argv[i], "--dump_freq") == 0)
            dump_freq = strtol(argv[i + 1], NULL, 10);
    }

    fread(info.bmp_header, sizeof(unsigned char), 54, image);
    info.image_offset = info.bmp_header[0xD] << 24 | info.bmp_header[0xC] << 16 | info.bmp_header[0xB] << 8 | info.bmp_header[0xA];
    info.size = info.bmp_header[0x5] << 24 | info.bmp_header[0x4] << 16 | info.bmp_header[0x3] << 8 | info.bmp_header[0x2];
    info.width = info.bmp_header[0x15] << 24 | info.bmp_header[0x14] << 16 | info.bmp_header[0x13] << 8 | info.bmp_header[0x12];
    info.height = info.bmp_header[0x19] << 24 | info.bmp_header[0x18] << 16 | info.bmp_header[0x17] << 8 | info.bmp_header[0x16];
    printf("offset - %lu\n", info.image_offset);
    printf("size - %lu\n", info.size);
    printf("height - %lu\n", info.height);
    printf("width - %lu\n", info.width);

    cur_gen = allocateArray(info.height, info.width * 3);
    next_gen = allocateArray(info.height, info.width * 3);

    if ((cur_gen == NULL) || (next_gen == NULL))
        return 1;

    fseek(image, info.image_offset, SEEK_SET);
    char buffer[3];

    for (unsigned long i = info.height - 1; i != (unsigned long)-1; i--) {
        for (unsigned long j = 0; j < info.width; j++) {
            buffer[0] = fgetc(image);
            buffer[1] = fgetc(image);
            buffer[2] = fgetc(image);
            if (buffer[0] != 0 && buffer[1] != 0 && buffer[2] != 0)
                cur_gen[i * info.width + j] = 0;
            else
                cur_gen[i * info.width + j] = 1;
        }
    }
    char fileName[100];
    char directory[256];
    unsigned char *pixelInfo;
    for (unsigned long i = 0; i < info.height; i++) {
        for (unsigned long j = 0; j < info.width; j++)
            next_gen[i * info.width + j] = cur_gen[i * info.width + j];
    }

    int countOfNeighbors;
    for (unsigned long gameIteration = 0; gameIteration < max_iter; gameIteration++) {
        for (unsigned long i = 1; i < info.height - 1; i++) {
            for (unsigned long j = 1; j < info.width - 1; j++) {
                countOfNeighbors = countNeighbors(cur_gen, i, j, info.width, info.height);

                if (cur_gen[i * info.width + j] == 0 && countOfNeighbors == 3)
                    next_gen[i * info.width + j] = 1;
                else if (cur_gen[i * info.width + j] == 1) {
                    if (countOfNeighbors < 2 || countOfNeighbors > 3)
                        next_gen[i * info.width + j] = 0;
                }
            }
        }

        for (unsigned long i = 0; i < info.height; i++) {
            for (unsigned long j = 0; j < info.width; j++)
                cur_gen[i * info.width + j] = next_gen[i * info.width + j];
        }

        pixelInfo = convertToBmp(cur_gen, info.height, info.width);

        if (gameIteration % dump_freq == 0) {
            sprintf(fileName, "%lu", gameIteration);
            strcpy(directory, dirName);
            strcat(directory, "/");
            strcat(directory, fileName);
            strcat(directory, ".bmp");

            FILE *new_bmp = fopen(directory, "wb");
            if (new_bmp != NULL)
                printf("File created\n");
            else
                printf("File can't be open\n");
            fwrite(info.bmp_header, 1, 54, new_bmp);
            fwrite(pixelInfo, 1, 3 * info.width * info.height, new_bmp);
            fclose(new_bmp);
        }
    }

    free(cur_gen);
    free(next_gen);
    free(pixelInfo);
    fclose(image);
    return 0;
}
