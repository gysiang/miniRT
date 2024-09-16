# Directories
SRC_DIR      := ./src
OBJ_DIR      := ./obj
INCLUDES_DIR := ./includes
LIBFT_DIR    := ./library/libft
LIBFT        := $(LIBFT_DIR)/libft.a
MLX_DIR	     := ./library/mlx
MLX	     	:=  $(MLX_DIR)/libmlx.a

# Compiler and flags
CC       := gcc
LEAKCHECK:= #-fsanitize=address
CFLAGS   := -g -O3 -Wall -Wextra -Werror -Wno-unused-result $(LEAKCHECK)
LFLAGS   := -L./libft -lft -lreadline
IFLAGS   := -I$(LIBFT_DIR) -I$(INCLUDES_DIR)
MLXFLAGS := -L./mlx -lmlx -lXext -lX11 -lbsd -lm

RM    := rm -f
NORM  := norminette

# Name of the executable
NAME := minirt

# Includes files
INCLUDES_FILES := main.c \
				  checks.c

INCLUDES       := $(addprefix $(INCLUDES_DIR)/, $(INCLUDES_FILES))

# Srcs
SRC_FILES := main.c

SRC := $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_FILES := $(SRC_FILES:.c=.o)
OBJ       := $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

# Compilation rules
$(NAME): $(LIBFT) $(MLX) $(OBJ) $(INCLUDES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LFLAGS) $(IFLAGS)

all: $(NAME)

$(LIBFT):
	@echo "Building libft..."
	@make -C $(LIBFT_DIR) --no-print-directory

$(MLX):
	@echo "Building mlx.."
	@make -C $(MLX_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(IFLAGS)

.PHONY: all bonus

# Cleanup rules
clean:
	@make -C $(LIBFT_DIR) clean --no-print-directory
	@make -C $(MLX_DIR) clean
	$(RM) -r $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@make -C $(MLX_DIR) clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re

.PHONY: norm

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
	./minishell

.PHONY: leaks
