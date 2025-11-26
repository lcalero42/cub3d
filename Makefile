# ---------------------------------------------------------------------------- #
#                                  USER CONFIG                                 #
# ---------------------------------------------------------------------------- #

# ---------------------------------- window ---------------------------------- #
WINDOW_WIDTH = 1920   # width of window
WINDOW_HEIGHT = 1080			# height of window

# --------------------------------- gameplay --------------------------------- #
MOVE_SPEED = 5.0f		   # player movement speed
CROSSHAIR_SIZE = 4		   # size of the crosshair
CROSSHAIR_THICKNESS = 2    # thickness of the crosshair
CROSSHAIR_COLOR = 0x00FF00 # color of the crosshair in hexa format
SENSITIVITY = 0.25f		   # player mouse sensitivity
RELOAD_TIME_MS = 1000	   # reload time of the weapon

# -------------------------------- performance ------------------------------- #
RENDER_DISTANCE = 1000	   # the maximum distance where the walls will be rendered

# ------------------------------------- - ------------------------------------ #

NAME = cub3D
NAME_BONUS = cub3D_bonus
MODE ?= release
CONFIG = -D WINDOW_WIDTH=$(WINDOW_WIDTH) -D WINDOW_HEIGHT=$(WINDOW_HEIGHT) -D MOVE_SPEED=$(MOVE_SPEED) -D ROT_SPEED=$(ROT_SPEED) -D RENDER_DISTANCE=$(RENDER_DISTANCE) \
		 -D CROSSHAIR_SIZE=$(CROSSHAIR_SIZE) -D CROSSHAIR_THICKNESS=$(CROSSHAIR_THICKNESS) -D CROSSHAIR_COLOR=$(CROSSHAIR_COLOR) -D SENSITIVITY=$(SENSITIVITY) \
		 -D RELOAD_TIME_MS=$(RELOAD_TIME_MS)
DEBUG_CONFIG = -D WINDOW_WIDTH=$(WINDOW_WIDTH) -D WINDOW_HEIGHT=$(WINDOW_HEIGHT) -D MOVE_SPEED=3.0f -D ROT_SPEED=2.0f -D RENDER_DISTANCE=10 \
			   -D CROSSHAIR_SIZE=$(CROSSHAIR_SIZE) -D CROSSHAIR_THICKNESS=$(CROSSHAIR_THICKNESS) -D CROSSHAIR_COLOR=$(CROSSHAIR_COLOR) \
			   -D SENSITIVITY=$(SENSITIVITY) -D RELOAD_TIME_MS=$(RELOAD_TIME_MS)
OPTI = -O3 -flto -march=native -mtune=native -funroll-loops

# Directory structure
ifeq ($(MODE), bonus)
	SRC_DIR = bonus
	OBJ_DIR = obj-bonus
	INC_DIR = bonus/inc
else
	SRC_DIR = mandatory
	OBJ_DIR = obj-release
	INC_DIR = mandatory/inc
endif

INCLUDES = -I$(INC_DIR) -Ilib/libft -Ilib/mlx
LIBS = lib/libft/libft.a lib/mlx/libmlx_Linux.a
CC = cc
CFLAGS = -g3 -Wall -Werror -Wextra -W -Wunused -MD -MP $(INCLUDES) $(CONFIG) $(OPTI)
MLXFLAGS = -lX11 -lXext -lm

ifeq ($(MODE), debug)
	CFLAGS = -Wall -Wextra -MD -MP $(INCLUDES) $(DEBUG_CONFIG) $(OPTI)
endif

VPATH = $(SRC_DIR)/srcs:$(SRC_DIR)/srcs/raycasting 	\
		$(SRC_DIR)/srcs:$(SRC_DIR)/srcs/player     	\
		$(SRC_DIR)/srcs:$(SRC_DIR)/srcs/parsing    	\
		$(SRC_DIR)/srcs:$(SRC_DIR)/srcs/checker    	\
		$(SRC_DIR)/srcs:$(SRC_DIR)/srcs/utils      	\
		$(SRC_DIR)/srcs:$(SRC_DIR)/srcs/rendering  	\
		$(SRC_DIR)/srcs:$(SRC_DIR)/srcs/mouse_move 	\
		$(SRC_DIR)/srcs:$(SRC_DIR)/srcs/sprite	   	\
		$(SRC_DIR)/srcs:$(SRC_DIR)/srcs/UI		   	\

# Mandatory source files
SRCS_MANDATORY = main.c						\
		pr_parse_config_lines.c				\
		pr_parse_file.c						\
		pr_parse_map.c						\
		pr_parse_texture.c					\
		pr_parse_color.c					\
		pr_check_file_extension.c			\
		pr_validate_config.c				\
		pr_find_player_pos.c				\
		c_check_map.c						\
		c_check_sourrounded_bw.c			\
		c_check_settings.c					\
		re_wall_render.c					\
		re_wall_texture.c					\
		re_render_fog.c						\
		r_wall_side.c						\
		r_raycast_dda.c						\
		r_raycast_init.c					\
		p_determine_movement.c				\
		p_delta_time.c						\
		u_calculate_map_width.c				\
		u_is_config_line.c					\
		u_is_empty_line.c					\
		u_skip_whitespace.c					\
		u_ft_free.c							\
		u_close_window.c					\
		u_rgb_to_hex.c						\
		u_print_error.c						\
		u_fog_rendering.c					\
		u_free_partial_grid.c			\
		u_rendering.c						\
		u_map_checking.c					\
		u_init.c							\
		u_ft_atoi_n_check.c					\
		c_validate_resolution.c				\
		c_check_map_content.c				\

# Bonus source files (with _bonus suffix)
SRCS_BONUS = main_bonus.c							\
		pr_parse_config_lines_bonus.c				\
		pr_parse_file_bonus.c						\
		pr_parse_map_bonus.c						\
		pr_parse_texture_bonus.c					\
		pr_parse_color_bonus.c						\
		pr_check_file_extension_bonus.c				\
		pr_validate_config_bonus.c					\
		pr_find_player_pos_bonus.c					\
		c_check_map_bonus.c							\
		c_check_sourrounded_bw_bonus.c				\
		c_validate_resolution_bonus.c				\
		c_check_map_content_bonus.c					\
		c_check_enemy_spawn_bonus.c					\
		c_check_settings_bonus.c					\
		re_wall_render_bonus.c						\
		re_wall_texture_bonus.c						\
		re_render_fog_bonus.c						\
		re_render_crosshair_bonus.c					\
		re_update_animations_bonus.c				\
		re_render_health_bar_bg_bonus.c				\
		re_fill_health_bar_bonus.c					\
		re_minimap_bonus.c							\
		re_minimap_utils_bonus.c					\
		re_minimap_ray_bonus.c						\
		re_stamina_bar_bonus.c						\
		r_wall_side_bonus.c							\
		r_door_handling_bonus.c						\
		r_raycast_dda_bonus.c						\
		r_raycast_init_bonus.c						\
		r_trace_shot_bonus.c						\
		r_perform_dda_bonus.c						\
		p_determine_movement_bonus.c				\
		p_delta_time_bonus.c						\
		p_check_collisions_bonus.c					\
		p_update_stamina_status_bonus.c 			\
		p_key_handling_bonus.c						\
		p_hooks_bonus.c								\
		u_calculate_map_width_bonus.c				\
		u_is_config_line_bonus.c					\
		u_is_empty_line_bonus.c						\
		u_ft_free_bonus.c							\
		u_close_window_bonus.c						\
		u_rgb_to_hex_bonus.c						\
		u_print_error_bonus.c						\
		u_fog_rendering_bonus.c						\
		u_skip_whitespace_bonus.c					\
		u_rendering_bonus.c							\
		u_map_checking_bonus.c						\
		u_init_bonus.c								\
		u_player_movement_bonus.c					\
		u_sprite_utils_bonus.c						\
		u_pathfinding_bonus.c						\
		u_get_current_speed_bonus.c 				\
		u_trace_shot_bonus.c						\
		u_calc_hitbox_bonus.c						\
		u_ft_atoi_n_check_bonus.c					\
		u_get_door_pixel_bonus.c					\
		u_check_wall_occlusion_bonus.c				\
		u_get_wall_texture_pixel_bonus.c			\
		u_door_utils_bonus.c						\
		u_free_partial_grid_bonus.c					\
		m_init_mouse_move_bonus.c					\
		m_mouse_move_bonus.c						\
		m_mouse_rotation_bonus.c					\
		m_mouse_utils_bonus.c						\
		s_sprite_render_bonus.c		    			\
		s_init_hpad_bonus.c							\
		s_hpad_sprite_calc_bonus.c					\
		s_hpad_bonus.c								\
		s_hpad_system_bonus.c						\
		s_hpad_collect_bonus.c						\
		s_hpad_transform_bonus.c					\
		s_hpad_bounds_bonus.c						\
		s_hpad_render_bonus.c						\
		s_enemy_movement_bonus.c					\
		s_render_gun_bonus.c						\
		s_enemy_find_path_bonus.c					\
		s_render_enemy_health_bonus.c				\
		ui_render_menu_bonus.c						\
		ui_render_game_over_bonus.c					\
		ui_handle_scene_bonus.c						\

# Select source files based on mode
ifeq ($(MODE), bonus)
	SRCS = $(SRCS_BONUS)
else
	SRCS = $(SRCS_MANDATORY)
endif

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

ifeq ($(MODE), bonus)
	BIN = $(NAME_BONUS)
else
	BIN = $(NAME)
endif

RESET			= \033[0m
GRAY			= \033[90m
RED				= \033[31m
GREEN			= \033[32m
YELLOW			= \033[33m
BLUE			= \033[34m

all:
	$(MAKE) libft
	$(MAKE) mlx
	$(MAKE) $(BIN)
	@if [ -f $(BIN) ]; then \
		printf "$(GREEN)✓ Build complete: $(BIN)$(RESET)\n"; \
	fi
	printf "$(RESET)"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/checker
	mkdir -p $(OBJ_DIR)/parsing
	mkdir -p $(OBJ_DIR)/player
	mkdir -p $(OBJ_DIR)/raycasting
	mkdir -p $(OBJ_DIR)/rendering
	mkdir -p $(OBJ_DIR)/utils
	mkdir -p $(OBJ_DIR)/mouse_move

libft:
	$(MAKE) -C lib/libft > /dev/null 2>&1

mlx:
	$(MAKE) -C lib/mlx > /dev/null 2>&1

mlx-verbose:
	$(MAKE) -C lib/mlx

$(OBJ_DIR)/%.o: %.c Makefile $(LIBS) | $(OBJ_DIR)
	printf "$(GRAY)compiling: $(BLUE)$<$(RESET)\n"
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@ $(MLXFLAGS)

clean:
	rm -rf obj-*
	$(MAKE) -C lib/libft clean
	$(MAKE) -C lib/mlx clean > /dev/null 2>&1
	printf "$(GREEN)✓ Objects cleaning done$(RESET)\n"

fclean: clean
	rm -f $(NAME_BONUS)
	rm -f $(NAME)
	$(MAKE) -C lib/libft fclean
	$(MAKE) -C lib/mlx clean > /dev/null 2>&1
	rm -f lib/mlx/libmlx.a
	printf "$(GREEN)✓ Binaries cleaning done$(RESET)\n"

re: fclean all

debug:
	$(MAKE) MODE=debug

release:
	$(MAKE) MODE=release

bonus:
	$(MAKE) MODE=bonus

see:
	$(MAKE) libft-verbose
	$(MAKE) mlx-verbose
	$(MAKE) $(BIN)
	printf "$(RESET)"

libft-verbose:
	$(MAKE) -C lib/libft

.PHONY: all libft libft-verbose mlx mlx-verbose clean fclean re debug release bonus see

-include $(DEPS)

.SILENT:
MAKEFLAGS=--no-print-directory
