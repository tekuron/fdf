PROJECT = fdf
NAME = fdf

SRC_DIR = src
INC_DIR = inc
INCLUDE = -I $(INC_DIR) -I libft/inc -I minilibx-linux
OBJ_DIR = obj
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Ofast -D BUFFER_SIZE=1000
RM = rm -rf
AR = ar rcs

LIB_DIR = libft
LIB = $(LIB_DIR)/libft.a

MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L $(MLX_DIR) -lmlx -lXext -lX11 -lm

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
CYAN = \033[0;36m

SRCS = $(shell find $(SRC_DIR) -name "*.c")

OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(NAME)

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(LIB):
	@make -C $(LIB_DIR)

$(NAME): $(LIB) $(MLX_LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIB) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)$(PROJECT) built: $(NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)Compiling: $<"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@make clean -C $(LIB_DIR)
	@make clean -C $(MLX_DIR)
	@echo "$(BLUE)$(PROJECT) object files removed"

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIB_DIR)
	@echo "$(BLUE)$(PROJECT) clean (library removed)"

re: fclean all
	@echo "$(GREEN)$(PROJECT) rebuilt"

pclean:
	@$(RM) $(OBJ_DIR)
	@echo "$(BLUE)$(PROJECT) non-library object files removed"

pfclean: pclean
	@$(RM) $(NAME)
	@echo "$(BLUE)$(PROJECT) pclean (library removed)"

pre: pfclean all

.PHONY: all clean fclean re