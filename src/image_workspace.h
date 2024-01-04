#ifndef IMAGE_WORKSPACE_H__
#define IMAGE_WORKSPACE_H__

#include <image.h>
#include <vector2.h>

typedef struct {
	image_t *image;
	vector2_t selection_point_a;
	vector2_t selection_point_b;
} image_workspace_t;

#endif // IMAGE_WORKSPACE_H__
