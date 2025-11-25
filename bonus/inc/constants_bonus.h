/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:17:32 by lcalero           #+#    #+#             */
/*   Updated: 2025/11/24 15:14:19 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_BONUS_H
# define CONSTANTS_BONUS_H

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
#  define MOVE_SPEED 7.0f
# endif

# define ENEMY_SPEED 4.0f

# ifndef SENSITIVITY
#  define SENSITIVITY 1.0f
# endif

# ifndef RENDER_DISTANCE
#  define RENDER_DISTANCE 1000
# endif

# define FOG_START_DISTANCE 0.1f
# define FOG_END_DISTANCE 5.0f
# define FOG_MAX_ALPHA 255
# define FOG_COLOR_R 0
# define FOG_COLOR_G 0
# define FOG_COLOR_B 0

# define CAMERA_PLANE_LENGTH 0.57735f

# define RAY_HIT 1
# define RAY_CONTINUE 0

# ifndef CROSSHAIR_SIZE
#  define CROSSHAIR_SIZE 10
# endif

# ifndef CROSSHAIR_THICKNESS
#  define CROSSHAIR_THICKNESS 2
# endif

# ifndef CROSSHAIR_COLOR
#  define CROSSHAIR_COLOR 0x00FF00
# endif

# define MAX_GRID_HEIGHT 400
# define MAX_GRID_WIDTH 400
# define MAX_NODES 4096

# ifndef PITCH_MAX
#  define PITCH_MAX 3.0f
# endif

# ifndef PITCH_MIN
#  define PITCH_MIN -3.0f
# endif

# ifndef STAMINA_DRAIN_RATE
#  define STAMINA_DRAIN_RATE 20.0f
# endif

# ifndef STAMINA_REGEN_RATE
#  define STAMINA_REGEN_RATE 10.0f
# endif

# ifndef MAX_STAMINA
#  define MAX_STAMINA 15.0f
# endif

# ifndef RUN_MULTIPLIER
#  define RUN_MULTIPLIER 1.6f
# endif

# ifndef RELOAD_TIME_MS
#  define RELOAD_TIME_MS 2000ll
# endif

# ifndef LIFE_DRAIN_RATE
#  define LIFE_DRAIN_RATE 20.0f
# endif

# define MAX_ANIM_LENGTH 4
# define ENEMY_RADIUS 0.380f
# define HEALTH_BAR_WIDTH 200
# define HEALTH_BAR_HEIGHT 20
# define HEALTH_BAR_X 50
# define HEALTH_BAR_Y 50
# define MAX_HEALTH 100

# define MAX_DOORS 64
# define MAX_HEALTH_PAD 64

# define MAX_RAY_HIT 20

#endif