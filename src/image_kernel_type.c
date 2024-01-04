#include <image_kernel_type.h>

void image_kernel_type_get_name(char *name,
								image_kernel_type_t image_kernel_type)
{
	switch (image_kernel_type) {
	case IKT_EDGE:
		name = "EDGE";
		break;
	case IKT_SHARPEN:
		name = "SHARPEN";
		break;
	case IKT_BOX_BLUR:
		name = "BLUR";
		break;
	case IKT_GAUSSIAN_BLUR:
		name = "GAUSSIAN_BLUR";
		break;
	default:
		break;
	}
}
