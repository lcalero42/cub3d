/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:49:33 by lcalero           #+#    #+#             */
/*   Updated: 2025/11/24 17:51:01 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# ifndef MIN_WIDTH
#  define MIN_WIDTH	640
# endif

# ifndef MIN_HEIGHT
#  define MIN_HEIGHT 360
# endif

# ifndef MAX_WIDTH
#  define MAX_WIDTH	1920
# endif

# ifndef MAX_HEIGHT
#  define MAX_HEIGHT 1080
# endif

# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH 1280
# endif

# ifndef WINDOW_HEIGHT
#  define WINDOW_HEIGHT	720
# endif

# ifndef MAX_MAP_LINES
#  define MAX_MAP_LINES 100
# endif

# ifndef MAX_LINE_LEN
#  define MAX_LINE_LEN 100
# endif

# ifndef MOVE_SPEED
#  define MOVE_SPEED 3.0f
# endif

# ifndef SENSITIVITY
#  define SENSITIVITY 100
# endif

# ifndef ROTATION_SPEED
#  define ROTATION_SPEED 3.0f
# endif

# ifndef RENDER_DISTANCE
#  define RENDER_DISTANCE 1000
# endif

# define FOG_START_DISTANCE 0.1f
# define FOG_END_DISTANCE 8.0f
# define FOG_MAX_ALPHA 255
# define FOG_COLOR_R 0
# define FOG_COLOR_G 0
# define FOG_COLOR_B 0

# define CAMERA_PLANE_LENGTH 0.57735f

#endif