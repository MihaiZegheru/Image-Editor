#ifndef IMAGE_LOADER_H__
#define IMAGE_LOADER_H__

#include <image.h>

#include <stdio.h>
#include <stdint.h>

image_t *image_loader_load(char *file_path);
void image_loader_save(image_t *image, char *file_path);

#endif // IMAGE_LOADER_H__
