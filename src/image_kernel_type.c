#include <image_kernel_type.h>

#include <string.h>

void image_kernel_type_get_name(char *name,
								image_kernel_type_t image_kernel_type)
{
	switch (image_kernel_type) {
	case IKT_EDGE:
		strcpy(name, "EDGE");
		break;
	case IKT_SHARPEN:
		strcpy(name, "SHARPEN");
		break;
	case IKT_BOX_BLUR:
		strcpy(name, "BLUR");
		break;
	case IKT_GAUSSIAN_BLUR:
		strcpy(name, "GAUSSIAN_BLUR");
		break;
	default:
		break;
	}
}
