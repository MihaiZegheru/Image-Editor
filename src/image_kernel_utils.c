#include <image_kernel_utils.h>

void image_kernel_utils_edge(double *inverse_modifier, __s8 kernel[3][3])
{
	*inverse_modifier = 1;
	kernel[0][0] = -1;
	kernel[0][1] = -1;
	kernel[0][2] = -1;
	kernel[1][0] = -1;
	kernel[1][1] = 8;
	kernel[1][2] = -1;
	kernel[2][0] = -1;
	kernel[2][1] = -1;
	kernel[2][2] = -1;
}

void image_kernel_utils_sharpen(double *inverse_modifier, __s8 kernel[3][3])
{
	*inverse_modifier = 1;
	kernel[0][0] = 0;
	kernel[0][1] = -1;
	kernel[0][2] = 0;
	kernel[1][0] = -1;
	kernel[1][1] = 5;
	kernel[1][2] = -1;
	kernel[2][0] = 0;
	kernel[2][1] = -1;
	kernel[2][2] = 0;
}

void image_kernel_utils_box_blur(double *inverse_modifier, __s8 kernel[3][3])
{
	*inverse_modifier = 9;
	kernel[0][0] = 1;
	kernel[0][1] = 1;
	kernel[0][2] = 1;
	kernel[1][0] = 1;
	kernel[1][1] = 1;
	kernel[1][2] = 1;
	kernel[2][0] = 1;
	kernel[2][1] = 1;
	kernel[2][2] = 1;
}

void image_kernel_utils_gaussian_blur(double *inverse_modifier,
									  __s8 kernel[3][3])
{
	*inverse_modifier = 16;
	kernel[0][0] = 1;
	kernel[0][1] = 2;
	kernel[0][2] = 1;
	kernel[1][0] = 2;
	kernel[1][1] = 4;
	kernel[1][2] = 2;
	kernel[2][0] = 1;
	kernel[2][1] = 2;
	kernel[2][2] = 1;
}
