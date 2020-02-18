#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

int a, widht, height, maxcol, num;

void swap(unsigned char &fir, unsigned char &sec) {
    unsigned char t = sec;
    sec = fir;
    fir = t;
}

int main(int argc, char * argv[]) {

    FILE * pFile;
    FILE * copyFile;
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
        unsigned char * k;
        k = (unsigned char*) malloc (sizeof(unsigned char) * height * widht);
        if (k != NULL) {
            fread(k, sizeof(unsigned char), widht * height, pFile);
            copyFile = fopen(argv[2], "wb");

            num = stoi(argv[3]);
            switch (num) {
                case 0:
                    for (int i = 0 ; i < (widht * height); ++i) {
                        k[i] = 255 - k[i];
                    }
                    fprintf(copyFile, "P%i\n%i %i\n%i\n", a, widht, height, maxcol);
                    fwrite(k, sizeof(unsigned char), widht * height, copyFile);
                    free(k);
                    break;
                case 2:
                    for (int i = 0; i < height / 2; ++i) {
                        for (int j = 0; j < widht; ++j) {
                            swap(k[i * widht + j ], k[(height - i - 1) * widht + j]);
                        }
                    }
                    fprintf(copyFile, "P%i\n%i %i\n%i\n", a, widht, height, maxcol);
                    fwrite(k, sizeof(unsigned char), widht * height, copyFile);
                    free(k);
                    break;
                case 1:
                    for (int i = 0; i < height; ++i) {
                        for (int j = 0; j < widht / 2; ++j) {
                            swap(k[ i * widht + j], k[(i + 1) * widht - j - 1]);
                        }
                    }
                    fprintf(copyFile, "P%i\n%i %i\n%i\n", a, widht, height, maxcol);
                    fwrite(k, sizeof(unsigned char), widht * height, copyFile);
                    free(k);
                    break;
                case 3:
                    unsigned char * k1;
                    k1 = (unsigned char*) malloc (sizeof(unsigned char) * widht * height);
                    for ( int i = 0; i < height; ++i) {
                        for (int j = 0; j < widht; ++j) {
                            k1[j * height + height - i - 1] = k[i * widht + j];
                        }
                    }
                    fprintf(copyFile, "P%i\n%i %i\n%i\n", a, height, widht, maxcol);
                    fwrite(k1, sizeof(unsigned char), height * widht, copyFile);
                    free(k1);
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
                    fprintf(copyFile, "P%i\n%i %i\n%i\n", a, height, widht, maxcol);
                    fwrite(k2, sizeof(unsigned char), height * widht, copyFile);
                    free(k1);
                    free(k);
                    break;
                default:
                    printf("unavailable action");
                    fclose(pFile);
                    fclose(copyFile);
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
        unsigned char *k;
        k = (unsigned char *) malloc(sizeof(unsigned char) * 3 * height * widht);
        if (k != NULL) {
            fread(k, sizeof(unsigned char), 3 * widht * height, pFile);
            copyFile = fopen(argv[2], "wb");
            num = stoi(argv[3]);
            switch (num) {
                case 0:
                    fprintf(copyFile, "P%i\n%i %i\n%i\n", a, widht, height, maxcol);
                    for (int i = 0; i < (3 *widht * height); ++i) {
                        k[i] = 255 - k[i];
                    }
                    fwrite(k, sizeof(unsigned char), 3 * widht * height, copyFile);
                    free(k);
                    break;
                case 2:
                    for (int i = 0; i < height / 2; ++i) {
                        for (int j = 0; j < widht; j++) {
                            swap(k[i * 3 * widht + j * 3], k[(height - i - 1) * 3 * widht + j * 3]);
                            swap(k[i * 3 * widht + j * 3 + 1], k[(height - i - 1) * 3 * widht + j * 3 + 1]);
                            swap(k[i * 3 * widht + j * 3 + 2], k[(height - i - 1) * 3 * widht + j * 3 + 2]);
                        }
                    }
                    fprintf(copyFile, "P%i\n%i %i\n%i\n", a, widht, height, maxcol);
                    fwrite(k, sizeof(unsigned char), 3 * widht * height, copyFile);
                    free(k);
                    break;
                case 1:
                    for (int i = 0; i < height; ++i) {
                        for (int j = 0; j < widht / 2; j += 1) {
                            swap(k[i * 3 * widht + j * 3], k[(i + 1) * 3 * widht - (j - 1) * 3]);
                            swap(k[i * 3 * widht + j * 3 + 1], k[(i + 1) * 3 * widht - (j - 1) * 3 + 1]);
                            swap(k[i * 3 * widht + j * 3 + 2], k[(i + 1) * 3 * widht - (j - 1) * 3 + 2]);
                        }
                    }
                    fprintf(copyFile, "P%i\n%i %i\n%i\n", a, widht, height, maxcol);
                    fwrite(k, sizeof(unsigned char), 3 * widht * height, copyFile);
                    free(k);
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
                    fprintf(copyFile, "P%i\n%i %i\n%i\n", a, height, widht, maxcol);
                    fwrite(k1, sizeof(unsigned char), 3 * height * widht, copyFile);
                    free(k1);
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
                    fprintf(copyFile, "P%i\n%i %i\n%i\n", a, height, widht, maxcol);
                    fwrite(k2, sizeof(unsigned char), 3 * height * widht, copyFile);
                    free(k1);
                    free(k);
                    break;
                default:
                    printf("unavailable action");
                    fclose(pFile);
                    fclose(copyFile);
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
    fclose(copyFile);
    return 0;
}
