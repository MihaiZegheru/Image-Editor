#ifndef IMAGE_KERNEL_TYPE_H__
#define IMAGE_KERNEL_TYPE_H__

typedef enum {
    IKT_NONE,
    IKT_EDGE,
    IKT_SHARPEN,
    IKT_BOX_BLUR,
    IKT_GAUSSIAN_BLUR
} image_kernel_type_t;

#endif // IMAGE_KERNEL_TYPE_H__