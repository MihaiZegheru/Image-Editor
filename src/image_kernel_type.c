#include <image_kernel_type.h>

#include <string.h>

void image_kernel_type_get_name(char *out_name,
								e_image_kernel_type_t image_kernel_type)
{
	switch (image_kernel_type) {
	case IKT_EDGE:
		strcpy(out_name, "EDGE");
		break;
	case IKT_SHARPEN:
		strcpy(out_name, "SHARPEN");
		break;
	case IKT_BOX_BLUR:
		strcpy(out_name, "BLUR");
		break;
	case IKT_GAUSSIAN_BLUR:
		strcpy(out_name, "GAUSSIAN_BLUR");
		break;
	default:
		break;
	}
}
