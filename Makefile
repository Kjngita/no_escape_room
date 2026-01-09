NAME = cub3D

FLAGS = -Wall -Wextra -Werror -g
HEADER = inc/header_cub3d.h
INCLUDES = -Iinc -I$(LIBFT_DIR) -I$(MLX_DIR)/include

S_DIR = src
CFILES = $(S_DIR)/map_validate.c \
	$(S_DIR)/map_graphics.c \
	$(S_DIR)/map_textures.c

O_DIR = objdir
OFILES = $(CFILES:$(S_DIR)/%.c=$(O_DIR)/%.o)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = MLX42
MLX_LIB = $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm

all: $(MLX_DIR) $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_DIR):
	git clone https://github.com/codam-coding-college/MLX42 $(MLX_DIR)
	cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

$(NAME): $(OFILES)
	cc $(FLAGS) $(OFILES) $(LIBFT) $(MLX_LIB) $(INCLUDES) -o $(NAME)
	@echo "┌───────────────────────────┐"
	@echo "│ ~~ \033[33m 🎮 Game ready! ✅ \033[0m ~~ │"
	@echo "└───────────────────────────┘"

$(O_DIR):
	mkdir -p $@

$(O_DIR)/%.o: $(S_DIR)/%.c $(HEADER) | $(O_DIR)
	cc $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(O_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)
	@echo "\033[33m** Object files deleted **\033[0m"

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "\033[33m** Program deleted **\033[0m"

re: fclean all

.SECONDARY: $(OFILES)

.PHONY: all clean fclean re

.SILENT: