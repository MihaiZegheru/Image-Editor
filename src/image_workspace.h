#ifndef IMAGE_WORKSPACE_H__
#define IMAGE_WORKSPACE_H__

#include <image.h>
#include <vector2.h>

typedef struct {
	s_image_t *image;
	s_vector2_t selection_point_a;
	s_vector2_t selection_point_b;
} s_image_workspace_t;

#endif // IMAGE_WORKSPACE_H__
