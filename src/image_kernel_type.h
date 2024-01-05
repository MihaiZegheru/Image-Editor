#ifndef IMAGE_KERNEL_TYPE_H__
#define IMAGE_KERNEL_TYPE_H__

/**
 * @brief The image_kernel_type defines the kernel type for an image effect
 *
 */
typedef enum {
	IKT_NONE,
	IKT_INVALID,
	IKT_EDGE,
	IKT_SHARPEN,
	IKT_BOX_BLUR,
	IKT_GAUSSIAN_BLUR,
} e_image_kernel_type_t;

/**
 * @brief Interface for associating an image_kernel_type with its coresponding
 * 		  name as string
 *
 * @param out_name
 * @param image_kernel_type
 */
void image_kernel_type_get_name(char *out_name,
								e_image_kernel_type_t image_kernel_type);

#endif // IMAGE_KERNEL_TYPE_H__
