#ifndef FSIZE_H
#define FSIZE_H
#include <cstdio>
/* Данная функция выдаёт размер файла в байтах, если
 * fptr != NULL, и (-1) в противном случае. */
long fsize(FILE* fptr);
#endif


