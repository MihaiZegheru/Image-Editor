/**
 *	Copyright (c) 2023-2024 | Mihai Zegheru | 312CAb
*/

#ifndef COLOR_H__
#define COLOR_H__

#include <linux/types.h>

/**
 * @brief The color defines a 3 channel, 3D point, that resembles a color
 *
 */
typedef struct {
	/**
	 * @brief The r channel of color
	 *
	 */
	__u8 m_r;
	/**
	 * @brief The g channel of color
	 *
	 */
	__u8 m_g;
	/**
	 * @brief The b channel of color
	 *
	 */
	__u8 m_b;
} s_color_t;

#endif // COLOR_H__
