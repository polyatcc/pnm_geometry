#include <string>
#include <stdlib.h>
#include <iostream>

using namespace std;

int a, widht, height, maxcol, num;

void swap(unsigned char &fir, unsigned char &sec) {
    unsigned char t = sec;
    sec = fir;
    fir = t;
}

bool writing(const char *s, int a, int widht, int height, int maxcol, unsigned char* m) {        //argv[2]
    FILE * copyFile;
    copyFile = fopen(s, "wb");
    if (copyFile == NULL) {   //не удалось открыть файл
        printf("the output file was not found \n");
        fclose(copyFile);
        return false;
    }
    fprintf(copyFile, "P%i\n%i %i\n%i\n", a, widht, height, maxcol);
    fwrite(m, sizeof(unsigned char), widht * height, copyFile);
    free(m);
    fclose(copyFile);
}
bool writing1(const char *s, int a, int widht, int height, int maxcol, unsigned char* m) {        //argv[2]
    FILE * copyFile;
    copyFile = fopen(s, "wb");
    if (copyFile == NULL) {   //не удалось открыть файл
        printf("the output file was not found \n");
        fclose(copyFile);
        return false;
    }
    fprintf(copyFile, "P%i\n%i %i\n%i\n", a, widht, height, maxcol);
    fwrite(m, sizeof(unsigned char), 3 * widht * height, copyFile);
    fclose(copyFile);
    free(m);
    return true;
}

int main(int argc, char * argv[]) {
    FILE * pFile;
    pFile = fopen(argv[1], "rb");
    if (pFile == NULL) {   //не удалось открыть файл
        printf("the file was not found \n");
        return 0;
    }
    fscanf(pFile, "P%i%i%i%i\n", &a, &widht, &height, &maxcol);
    if ((a != 5) && (a != 6)) {
        printf("unsupported type of file \n");
        fclose(pFile);
        return 0;
    }

    if (a == 5) {
        int count = 0;
        int ret = ftell(pFile);
        while (!feof(pFile)) {
            getc(pFile);
            count++;
        }
        if (count != height * widht) {
            printf( "Memory failed");
            fclose(pFile);
            return 0;
        }
        fseek(pFile, 1, ret);
        unsigned char * k;
        k = (unsigned char*) malloc (sizeof(unsigned char) * height * widht);
        if (k != NULL) {
            fread(k, sizeof(unsigned char), widht * height, pFile);
            num = stoi(argv[3]);
            switch (num) {
                case 0:
                    for (int i = 0 ; i < (widht * height); ++i) {
                        k[i] = 255 - k[i];
                    }
                    writing(argv[2], a, widht, height, maxcol, k);
                    break;
                case 2:
                    for (int i = 0; i < height / 2; ++i) {
                        for (int j = 0; j < widht; ++j) {
                            swap(k[i  * widht + j ], k[(height - i - 1) * widht + j]);
                        }
                    }
                    if (writing(argv[2], a, widht, height, maxcol, k) == 0) {
                        return 0;
                    }
                    break;
                case 1:
                    for (int i = 0; i < height; ++i) {
                        for (int j = 0; j < widht / 2; ++j) {
                            swap(k[ i * widht + j], k[(i + 1) * widht - j - 1]);
                        }
                    }
                    if (writing(argv[2], a, widht, height, maxcol, k) == 0) {
                        return 0;
                    }
                    break;
                case 3:
                    unsigned char * k1;
                    k1 = (unsigned char*) malloc (sizeof(unsigned char) * widht * height);
                    for ( int i = 0; i < height; ++i) {
                        for (int j = 0; j < widht; ++j) {
                            k1[j * height + height - i - 1] = k[i * widht + j];
                        }
                    }
                    if (writing(argv[2], a, height, widht, maxcol, k1) == 0) {
                        return 0;
                    }
                    free(k);
                    break;
                case 4:
                    unsigned char * k2;
                    k2 = (unsigned char*) malloc (sizeof(unsigned char) * widht * height);
                    for (int i = 0; i < height; ++i) {
                        for (int j = 0; j < widht; ++j) {
                            k2[(widht - j - 1) * height + i] = k[i * widht + j];
                        }
                    }
                    if (writing(argv[2], a, height, widht, maxcol, k2) == 0) {
                        return 0;
                    }
                    free(k);
                    break;
                default:
                    printf("unavailable action");
                    fclose(pFile);
                    free(k);
                    return 0;
            }

        } else {
            printf( "Allocation memory failed");
            fclose(pFile);
            free(k);
            return 0;
        }
    } else {
        int count = 0;
        int ret = ftell(pFile);
        while (!feof(pFile)) {
            getc(pFile);
            count++;
        }
        if (count - 1 != 3 * height * widht) {
            
            printf( "Memory failed");
            fclose(pFile);
            return 0;
        }
        fseek(pFile, 1, ret);
        unsigned char *k;
        k = (unsigned char *) malloc(sizeof(unsigned char) * 3 * height * widht);
        if (k != NULL) {
            fread(k, sizeof(unsigned char), 3 * widht * height, pFile);
            num = stoi(argv[3]);
            switch (num) {
                case 0:
                    for (int i = 0; i < (3 *widht * height); ++i) {
                        k[i] = 255 - k[i];
                    }
                    if (writing1(argv[2], a, widht, height, maxcol, k) == 0) {
                        return 0;
                    }
                    break;
                case 2:
                    for (int i = 0; i < height / 2; ++i) {
                        for (int j = 0; j < widht; j++) {
                            swap(k[i * 3 * widht + j * 3], k[(height - i - 1) * 3 * widht + j * 3]);
                            swap(k[i * 3 * widht + j * 3 + 1], k[(height - i - 1) * 3 * widht + j * 3 + 1]);
                            swap(k[i * 3 * widht + j * 3 + 2], k[(height - i - 1) * 3 * widht + j * 3 + 2]);
                        }
                    }
                    if (writing1(argv[2], a, widht, height, maxcol, k) == 0) {
                        return 0;
                    }

                    break;
                case 1:
                    for (int i = 0; i < height; ++i) {
                        for (int j = 0; j < widht / 2; j += 1) {
                            swap(k[i * 3 * widht + j * 3], k[(i + 1) * 3 * widht - (j + 1) * 3]);
                            swap(k[i * 3 * widht + j * 3 + 1], k[(i + 1) * 3 * widht - (j + 1) * 3 + 1]);
                            swap(k[i * 3 * widht + j * 3 + 2], k[(i + 1) * 3 * widht - (j + 1) * 3 + 2]);
                        }
                    }
                    if (writing1(argv[2], a, widht, height, maxcol, k) == 0) {
                        return 0;
                    }
                    break;
                case 3:
                    unsigned char * k1;
                    k1 = (unsigned char*) malloc (sizeof(unsigned char) * widht * height * 3);
                    for ( int i = 0; i < height ; ++i) {
                        for (int j = 0; j < widht; j++) {
                            k1[j * height * 3 + height * 3 - i * 3 - 3] = k[i *  widht * 3 + j * 3];
                            k1[j * height * 3 + height * 3 - i * 3 - 3 + 1] = k[i * widht * 3 + (j * 3) + 1];
                            k1[j * height * 3 + height * 3 - i * 3 - 3 + 2] = k[i * widht * 3 + (j * 3 + 2)];
                        }
                    }
                    if (writing1(argv[2], a, height, widht, maxcol, k1) == 0) {
                        return 0;
                    }
                    free(k);
                    break;
                case 4:
                    unsigned char * k2;
                    k2 = (unsigned char*) malloc (sizeof(unsigned char) * widht * height * 3);
                    for (int i = 0; i < height; ++i) {
                        for (int j = 0; j < widht; j++) {
                            k2[(widht - j - 1) * height * 3 + i * 3] = k[i * widht * 3 + j * 3];
                            k2[(widht - j - 1) * height * 3 + i * 3 + 1] = k[i * widht * 3 + j * 3 + 1];
                            k2[(widht - j - 1) * height * 3 + i * 3 + 2] = k[i * widht * 3 + (j * 3 + 2)];
                        }
                    }
                    if (writing1(argv[2], a, height, widht, maxcol, k2) == 0) {
                        return 0;
                    }
                    free(k);
                    break;
                default:
                    printf("unavailable action");
                    fclose(pFile);
                    free(k);
                    return 0;
            }

        }
         else {
            printf("Allocation memory failed");
            fclose(pFile);
            free(k);
            return 0;
         }
    }
    fclose(pFile);
    return 0;
}
