# ---------------------------------------------------------------------------- #
#                                  USER CONFIG                                 #
# ---------------------------------------------------------------------------- #

# ---------------------------------- window ---------------------------------- #
WINDOW_WIDTH = 1920		# width of window
WINDOW_HEIGHT = 1080		# height of window

# --------------------------------- gameplay --------------------------------- #
MOVE_SPEED = 0.02		# player movement speed
ROT_SPEED = 0.1		# player rotation speed

# -------------------------------- performance ------------------------------- #		# check your cpu for best value
TEXTURE_SIZE = 64		# texture resolution (64x64)

# ------------------------------------- - ------------------------------------ #

NAME = cub3d
MODE ?= release
CONFIG = -D WINDOW_WIDTH=$(WINDOW_WIDTH) -D WINDOW_HEIGHT=$(WINDOW_HEIGHT) -D MOVE_SPEED=$(MOVE_SPEED) -D ROT_SPEED=$(ROT_SPEED) -D TEXTURE_SIZE=$(TEXTURE_SIZE)
DEBUG_CONFIG = -D WINDOW_WIDTH=$(WINDOW_WIDTH) -D WINDOW_HEIGHT=$(WINDOW_HEIGHT) -D MOVE_SPEED=0.05 -D ROT_SPEED=0.02 -D TEXTURE_SIZE=32
OPTI = -O3 -flto -march=native -mtune=native -funroll-loops
OBJ_DIR = obj-$(MODE)
INCLUDES = -Iincludes -Ilibft -Iminilibx-linux
LIBS = libft/libft.a minilibx-linux/libmlx_Linux.a
CC = cc
CFLAGS = -Wall -Werror -Wextra -MD -MP -Iinc $(INCLUDES) $(CONFIG) $(OPTI)
MLXFLAGS = -lX11 -lXext -lm

ifeq ($(MODE), debug)
	CFLAGS = -Wall -Wextra -MD -MP -Iinc $(INCLUDES) -g3 $(DEBUG_CONFIG)
endif

VPATH = srcs:srcs/raycasting \
		srcs:srcs/player	 \
		srcs:srcs/parsing	 \
		srcs:srcs/utils		 \

SRCS =	main.c						\
		pr_parse_config_lines.c		\
		pr_parse_file.c				\
		pr_parse_map.c				\
		pr_parse_texture.c			\
		pr_parse_color.c			\
		pr_check_file_extension.c	\
		pr_validate_config.c		\
		r_raycast_dda.c				\
		r_raycast_init.c			\
		r_wall_render.c				\
		r_wall_texture.c			\
		r_wall_side.c				\
		p_determine_movement.c		\
		u_calculate_map_width.c		\
		u_is_config_line.c			\
		u_is_empty_line.c			\
		u_ft_free.c					\

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)
BIN = $(NAME)

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
	printf "$(RESET)"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

libft:
	$(MAKE) -C libft > /dev/null 2>&1

mlx:
	$(MAKE) -C minilibx-linux > /dev/null 2>&1

mlx-verbose:
	$(MAKE) -C minilibx-linux

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@ $(MLXFLAGS)

$(OBJ_DIR)/%.o: %.c Makefile $(LIBS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	printf "$(GRAY)compiling: $(BLUE)%-40s $(GRAY)[%d/%d]\n" "$<" "$$(ls $(OBJ_DIR) | grep -c '\.o')" "$(words $(SRCS))"

clean:
	rm -rf obj-*
	$(MAKE) -C libft clean
	$(MAKE) -C minilibx-linux clean > /dev/null 2>&1

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean
	$(MAKE) -C minilibx-linux clean > /dev/null 2>&1
	rm -f minilibx-linux/libmlx.a

re: fclean all

debug:
	$(MAKE) MODE=debug

release:
	$(MAKE) MODE=release

see:
	$(MAKE) libft-verbose
	$(MAKE) mlx-verbose
	$(MAKE) $(BIN)
	printf "$(RESET)"

libft-verbose:
	$(MAKE) -C libft

.PHONY: all libft libft-verbose mlx mlx-verbose clean fclean re debug release see

-include $(DEPS)

.SILENT:
MAKEFLAGS=--no-print-directory