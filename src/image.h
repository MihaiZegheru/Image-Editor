#ifndef IMAGE_H__
#define IMAGE_H__

#include <linux/types.h>
#include <stddef.h>

#include <color.h>
#include <image_data.h>
#include <vector2.h>

/**
 * @brief The image defines the pixels and image_data of an image
 *
 */
typedef struct {
	/**
	 * @brief The pixels array (liniarised)
	 *
	 */
	s_color_t *m_pixels;
	/**
	 * @brief The data about the image
	 *
	 */
	s_image_data_t m_image_data;
} s_image_t;

/**
 * @brief Instantiate a new empty image in memory based on provided image_data
 *
 * @param image_data
 * @return s_image_t*
 */
s_image_t *image_new(s_image_data_t image_data);

/**
 * @brief Delete image from memory
 *
 * @param image
 */
void image_delete(s_image_t *image);

/**
 * @brief Get pixel/color at coords
 *
 * @param coords
 * @param image
 * @return s_color_t
 */
s_color_t image_get_pixel(s_vector2_t coords, s_image_t *image);

/**
 * @brief Set pixel at coords
 *
 * @param coords
 * @param pixel
 * @param image
 */
void image_set_pixel(s_vector2_t coords, s_color_t pixel, s_image_t *image);

/**
 * @brief Get image width in pixels
 *
 * @param image
 * @return size_t
 */
size_t image_get_width(s_image_t *image);

/**
 * @brief Get image height in pixels
 *
 * @param image
 * @return size_t
 */
size_t image_get_height(s_image_t *image);

/**
 * @brief Perform a check on coords and decides wether they are in bounds of the
 * 		  image or not
 *
 * @param coords
 * @param image
 * @return __s8 - 1 if in bounds, 0 if not
 */
__s8 image_coords_in_bounds(s_vector2_t coords, s_image_t *image);

#endif // IMAGE_H__
