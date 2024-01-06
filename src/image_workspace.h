/**
 *	Copyright (c) 2023-2024 | Mihai Zegheru | 312CAb
*/

#ifndef IMAGE_WORKSPACE_H__
#define IMAGE_WORKSPACE_H__

#include <image.h>
#include <vector2.h>

/**
 * @brief The image_workspace defines the currently operating image and its
 *		  active selection
 *
 */
typedef struct {
	/**
	 * @brief The image currently operating on
	 *
	 */
	s_image_t *m_image;
	/**
	 * @brief The up-right corner of the selection
	 *
	 */
	s_vector2_t m_selection_point_a;
	/**
	 * @brief The down-left corner of the selection
	 *
	 */
	s_vector2_t m_selection_point_b;
} s_image_workspace_t;

#endif // IMAGE_WORKSPACE_H__
