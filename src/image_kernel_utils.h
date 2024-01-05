#ifndef KERNEL_UTILS_H__
#define KERNEL_UTILS_H__

#include <linux/types.h>

/**
 * @brief Provides through parameters the required inverse_modifier and kernel
 * 		  for the EDGE effect
 *
 * @param inverse_modifier this is inverse in order to avoid floating point
 * 						   errors
 * @param kernel
 */
void image_kernel_utils_edge(double *inverse_modifier, __s8 kernel[3][3]);

/**
 * @brief Provides through parameters the required inverse_modifier and kernel
 * 		  for the SHARPEN effect
 *
 * @param inverse_modifier this is inverse in order to avoid floating point
 * 						   errors
 * @param kernel
 */
void image_kernel_utils_sharpen(double *inverse_modifier, __s8 kernel[3][3]);

/**
 * @brief Provides through parameters the required inverse_modifier and kernel
 * 		  for the BLUR effect
 *
 * @param inverse_modifier this is inverse in order to avoid floating point
 * 						   errors
 * @param kernel
 */
void image_kernel_utils_box_blur(double *inverse_modifier, __s8 kernel[3][3]);

/**
 * @brief Provides through parameters the required inverse_modifier and kernel
 * 		  for the GAUSSIAN_BLUR effect
 *
 * @param inverse_modifier this is inverse in order to avoid floating point
 * 						   errors
 * @param kernel
 */
void image_kernel_utils_gaussian_blur(double *inverse_modifier,
									  __s8 kernel[3][3]);

#endif // KERNEL_UTILS_H__
