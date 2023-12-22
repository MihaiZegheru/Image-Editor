#ifndef IMAGE_LOADER_H__
#define IMAGE_LOADER_H__

#include <image.h>

#include <stdio.h>
#include <stdint.h>

image_t *image_loader_load(const char *file_path);
image_t *image_loader_get_ppm(FILE *file);

#endif // IMAGE_LOADER_H__
