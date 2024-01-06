/**
 *	Copyright (c) 2023-2024 | Mihai Zegheru | 312CAb
*/

#ifndef IMAGE_LOADER_H__
#define IMAGE_LOADER_H__

#include <image.h>

#define LINE_MAX_BUFFER 255

/**
 * @brief Load an image from the file_path into memory
 *
 * @param file_path
 * @return s_image_t*
 */
s_image_t *image_loader_load(char *file_path);

/**
 * @brief Save an image from memory at the file_path
 *
 * @param image
 * @param file_path
 */
void image_loader_save(s_image_t *image, char *file_path);

#endif // IMAGE_LOADER_H__
