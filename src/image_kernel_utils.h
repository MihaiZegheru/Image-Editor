#ifndef KERNEL_UTILS_H__
#define KERNEL_UTILS_H__

#include <linux/types.h>

void image_kernel_utils_edge(double *inverse_modifier, __s8 kernel[3][3]);
void image_kernel_utils_sharpen(double *inverse_modifier, __s8 kernel[3][3]);
void image_kernel_utils_box_blur(double *inverse_modifier, __s8 kernel[3][3]);
void image_kernel_utils_gaussian_blur(double *inverse_modifier,
									  __s8 kernel[3][3]);

#endif // KERNEL_UTILS_H__
