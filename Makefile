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
INCLUDES_FILES :=	minirt.h \
					vector.h
INCLUDES       := $(addprefix $(INCLUDES_DIR)/, $(INCLUDES_FILES))

# Srcs
SRC_ALL	:=	main.c \
			checks.c \
			check_elems.c \
			check_util1.c \
			check_util2.c \
			save.c \
			save1.c \
			init_struct.c \
			handlers.c \
			handlers1.c \
			handlers_cam.c \
			render.c \
			rgb.c \
			mlx_image.c \
			ray_logic.c \
			ray_hits.c \
			ray_hits_cy.c \
			ray_hits_cy1.c \
			ray_light_shadow.c \
			vector_op.c \
			vector_op1.c

SRC_MAND	:=	manage_elems_light.c \
				ray_light_calc.c \
				free.c

SRC_BONUS	:=	$(addsuffix _b.c, $(basename $(SRC_MAND)))

ifdef O_BONUS
SRC_FILES:= $(SRC_ALL) $(SRC_BONUS)
else
SRC_FILES:= $(SRC_ALL) $(SRC_MAND)
endif

SRC		:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_ALL		:= $(SRC_FILES:.c=.o)
OBJ_MAND	:= $(SRC_FILES_MAND:.c=.o)
OBJ_BONUS	:= $(SRC_FILES_BONUS:.c=.o)

ifdef O_BONUS
OBJ_FILES:= $(OBJ_ALL) $(OBJ_BONUS)
else
OBJ_FILES:= $(OBJ_ALL) $(OBJ_MAND)
endif

OBJ		:= $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

ifdef FALLOFF_I
FALLFLAGS := $(shell touch $(SRC_DIR)/ray_light_shadow.c)
FALLFLAGS := -D FALLOFF_I=$(FALLOFF_I)
endif

# Compilation rules
$(NAME): $(LIBFT) $(MLX) $(OBJ) $(INCLUDES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LFLAGS) $(IFLAGS) $(MLXFLAGS)

all: $(NAME)

$(LIBFT) libft:
	@echo "Building libft..."
	@make -C $(LIBFT_DIR) --no-print-directory

$(MLX):
	@if [ ! -d $(MLXDIR) ] || [ ! -f $(MLX) ]; then \
		echo "MLX not found. Cloning and building ..."; \
		git submodule deinit -f $(MLX_DIR); \
		git submodule update --init $(MLX_DIR); \
		make -C $(MLX_DIR) all; \
	else \
		echo "MLX already exists. Skipping ..."; \
	fi

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(FALLFLAGS) -c $< -o $@ $(IFLAGS)

.PHONY: all bonus libft

# Cleanup rules
clean:
	$(RM) -r $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@make -C $(MLX_DIR) clean

re: fclean all

bonus:
	@make O_BONUS=1 all

.PHONY: clean fclean re bonus

# Custom commands
norm:
	@$(NORM) $(SRC_DIR)/*.c $(INCLUDES_DIR)/*.h

leaks: $(NAME)
	valgrind -s --leak-check=full --show-reachable=yes \
	--show-leak-kinds=all --trace-children=yes --track-fds=yes \
	--track-origins=yes \
	./miniRT

.PHONY: norm leaks
