# Directories
SRC_DIR      := ./src
OBJ_DIR      := ./obj
INCLUDES_DIR := ./includes
LIBFT_DIR    := ./library/libft
LIBFT        := $(LIBFT_DIR)/libft.a
MLX_DIR	     := ./library/mlx
MLX	     	:=  $(MLX_DIR)/libmlx.a

# Compiler and flags
CC       := clang
LEAKCHECK:= #-fsanitize=address
CFLAGS   := -g -O3 -Wall -Wextra -Werror -Wno-unused-result $(LEAKCHECK)
LFLAGS   := -L$(LIBFT_DIR) -lft
IFLAGS   := -I$(LIBFT_DIR) -I$(INCLUDES_DIR)
MLXFLAGS := -L$(MLX_DIR) -lmlx -lXext -lX11 -lbsd -lm

RM    := rm -fr
NORM  := norminette

# Name of the executable
NAME := miniRT

# Includes files
INCLUDES_FILES :=	minirt.h
INCLUDES       := $(addprefix $(INCLUDES_DIR)/, $(INCLUDES_FILES))

# Srcs
SRC_FILES :=	main.c \
				checks.c \
				checks1.c \
				check_util1.c \
				check_util2.c \
				save.c \
				save1.c \
				utils.c \
				init_struct.c \
				movement.c \
				handlers.c \
				free.c	\
				render.c \
				rgb.c \
				mlx_image.c \
				ray_logic.c \
				vector_op.c

SRC := $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_FILES := $(SRC_FILES:.c=.o)
OBJ       := $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

# Compilation rules
$(NAME): $(LIBFT) $(MLX) $(OBJ) $(INCLUDES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LFLAGS) $(IFLAGS) $(MLXFLAGS)

all: $(NAME)

$(LIBFT):
	@echo "Building libft..."
	@make -C $(LIBFT_DIR) --no-print-directory

$(MLX):
	@if [ ! -d $(MLXDIR) ] || [ ! -f $(MLX) ]; then \
		echo "MLX not found. Cloning and building ..."; \
		$(RM) $(MLX_DIR); \
		git submodule deinit -f $(MLX_DIR); \
		git submodule update --init $(MLX_DIR); \
		make -C $(MLX_DIR) all; \
	else \
		echo "MLX already exists. Skipping ..."; \
	fi

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(IFLAGS)

.PHONY: all bonus

# Cleanup rules
clean:
	$(RM) -r $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@make -C $(MLX_DIR) clean

re: fclean all

.PHONY: clean fclean re

# Norminette
norm:
	@$(NORM) $(SRC_DIR)/*.c $(INCLUDES_DIR)/*.h

.PHONY: norm

# Custom commands
leaks: $(NAME)
	valgrind -s --leak-check=full --show-reachable=yes \
	--show-leak-kinds=all --trace-children=yes --track-fds=yes \
	--suppressions=./readline.supp \
	--track-origins=yes \
	./miniRT

.PHONY: leaks
