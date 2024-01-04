#ifndef IMAGE_KERNEL_TYPE_H__
#define IMAGE_KERNEL_TYPE_H__

typedef enum {
	IKT_NONE,
	IKT_INVALID,
	IKT_EDGE,
	IKT_SHARPEN,
	IKT_BOX_BLUR,
	IKT_GAUSSIAN_BLUR,
} e_image_kernel_type_t;

void image_kernel_type_get_name(char *name,
								e_image_kernel_type_t image_kernel_type);

#endif // IMAGE_KERNEL_TYPE_H__
