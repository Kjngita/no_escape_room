NAME = cub3D

FLAGS = -Wall -Wextra -Werror -g
HEADER = inc/header_cub3d.h
INCLUDES = -Iinc -I$(LIBFT_DIR) -I$(MLX_DIR)/include

S_DIR = src
PAR = parsing
EXE = execution

CFILES = $(S_DIR)/main.c \
  $(S_DIR)/$(PAR)/input_check.c \
	$(S_DIR)/$(PAR)/input_sort.c \
	$(S_DIR)/$(PAR)/texture_register.c \
	$(S_DIR)/$(PAR)/color_register.c \
	$(S_DIR)/$(PAR)/map_extraction.c \
	$(S_DIR)/$(PAR)/cleanup.c \
  $(S_DIR)/$(EXE)/controls.c \
  $(S_DIR)/$(EXE)/init.c \
  $(S_DIR)/$(EXE)/draw_map.c \
  $(S_DIR)/$(EXE)/init_ray.c \
  $(S_DIR)/$(EXE)/draw_ray.c \
  $(S_DIR)/$(EXE)/cast_rays.c \
  $(S_DIR)/$(EXE)/render_walls.c

O_DIR = objdir
OFILES = $(CFILES:$(S_DIR)/%.c=$(O_DIR)/%.o)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = MLX42

MLX_LIB = $(MLX_DIR)/build/libmlx42.a
MLX_FLAGS = -ldl -lglfw -pthread -lm

all: $(MLX_LIB) $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	@if [ ! -d "$(MLX_DIR)" ]; then git clone https://github.com/codam-coding-college/MLX42 $(MLX_DIR); fi
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

$(NAME): $(OFILES)
	cc $(FLAGS) $(OFILES) $(LIBFT) $(MLX_LIB) $(MLX_FLAGS) $(INCLUDES) -o $(NAME)
	@echo "┌───────────────────────────┐"
	@echo "│ ~~ \033[33m 🎮 Game ready! ✅ \033[0m ~~ │"
	@echo "└───────────────────────────┘"

$(O_DIR):
	mkdir -p $(O_DIR)/$(PAR)
	mkdir -p $(O_DIR)/$(EXE)

$(O_DIR)/%.o: $(S_DIR)/%.c $(HEADER) | $(O_DIR)
	cc $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(O_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(MLX_DIR)/build
	@echo "\033[33m** Object files deleted **\033[0m"

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "\033[33m** Program deleted **\033[0m"

re: fclean all

.SECONDARY: $(OFILES)

.PHONY: all clean fclean re

.SILENT: