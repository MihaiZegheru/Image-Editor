#ifndef VECTOR2_H__
#define VECTOR2_H__

#include <linux/types.h>

/**
 * @brief The vector2 defines a point in 2D space
 *
 */
typedef struct {
	/**
	 * @brief The x coordinate
	 *
	 */
	__s64 m_x;
	/**
	 * @brief The y coordinate
	 *
	 */
	__s64 m_y;
} s_vector2_t;

#endif // VECTOR2_H__
