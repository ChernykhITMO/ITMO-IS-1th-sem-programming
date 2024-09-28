#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void createArchive(char* archiveName, char* files[], int numFiles) {
    FILE* archive = fopen(archiveName, "wb");
    if (archive == NULL) {
        fprintf(stderr, "Error opening archive\n");
        return;
    }
    for (int i = 0; i < numFiles; i++) {
        FILE* file = fopen(files[i], "rb");
        if (file == NULL)
            fprintf(stderr,"Error opening file %s\n", files[i]);
        fseek(file, 0, SEEK_END);
        long sizeFile = ftell(file);
        rewind(file);
        fwrite(&sizeFile, sizeof(long), 1, archive);
        int lengthFile = strlen(files[i]);
        fwrite(&lengthFile, sizeof(int), 1, archive);
        fwrite(files[i], sizeof(char), lengthFile, archive);
        char* buffer = (char*)malloc(sizeFile);
        fread(buffer, 1, sizeFile, file);
        fwrite(buffer, 1, sizeFile, archive);
        free(buffer);
        fclose(file);
    }
    fclose(archive);
}

void extractArchive(char* archiveName) {
    FILE* archive = fopen(archiveName, "rb");
    if (archive == NULL) {
        fprintf(stderr, "Error opening archive\n");
        return;
    }
    int fileNum = 1;
    long sizeFile;
    while (fread(&sizeFile, sizeof(long), 1, archive) == 1) {
        char filename[50];
        sprintf(filename, "extracted_file%d.txt", fileNum);
        FILE* file = fopen(filename, "wb");
        if (file == NULL) {
            fprintf(stderr, "Error creating file %s\n", filename);
            return;
        }
        char* buffer = (char*)malloc(sizeFile);
        fread(buffer, 1, sizeFile, archive);
        fwrite(buffer, 1, sizeFile, file);
        free(buffer);
        fclose(file);
        fileNum++;
    }
    fclose(archive);
}

void listFilesInArchive(char* archiveName) {
    FILE* archive = fopen(archiveName, "rb");
    if (archive == NULL) {
        fprintf(stderr, "Error opening archive\n");
        return;
    }
    int fileNum = 1;
    long sizeFile;
    while (fread(&sizeFile, sizeof(long), 1, archive) == 1) {
        int fileNameLength;
        fread(&fileNameLength, sizeof(int), 1, archive);
        char filename[fileNameLength + 1];
        fread(filename, sizeof(char), fileNameLength, archive);
        filename[fileNameLength] = '\0';
        printf("File %d: %s, size %ld bytes\n", fileNum++, filename, sizeFile);
        fseek(archive, sizeFile, SEEK_CUR);
    }
    fclose(archive);
}


int main(int argc, char* argv[]) {
    if (argc < 4) {
        fprintf(stderr, "ERROR, the program is not working");
        return 1;
    }

    char* archiveName = NULL;
    char* files[100];
    int numFiles = 0;
    int extractingArchive = 0;
    int listingFiles = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--file") == 0) {
            archiveName = argv[i+1];
            i++;
        }
        else if (strcmp(argv[i], "--create") == 0) {
            for (int j = i+1; j < argc; j++) {
                if (argv[j][0] != '-')
                    files[numFiles++] = argv[j];
                else break;
            }
        }
        else if (strcmp(argv[i], "--extract") == 0)
            extractingArchive = 1;
        else if (strcmp(argv[i], "--list") == 0)
            listingFiles = 1;
    }
    if (archiveName) {
        if (extractingArchive)
            extractArchive(archiveName);
        else if (listingFiles)
            listFilesInArchive(archiveName);
        else if (numFiles > 0)
            createArchive(archiveName, files, numFiles);
        else {
            fprintf(stderr, "No files specified for creating archive\n");
            return 1;
        }
    } else {
        fprintf(stderr, "Archive name not specified\n");
        return 1;
    }
    return 0;
}
