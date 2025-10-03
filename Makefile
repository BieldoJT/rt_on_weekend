NAME = miniRT

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MINILIBX_FLAGS = -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm -lpthread -O2

MLX_LIB = minilibx-linux/libmlx.a

SRC_DIR = src
MAT_DIR = $(SRC_DIR)/material/
CAM_DIR = $(SRC_DIR)/camera/
INTER_DIR = $(SRC_DIR)/interval/
CYL_DIR = $(SRC_DIR)/cylinder/
PARSER_DIR = $(SRC_DIR)/parser_rt/
LIB_DIR = lib

LIBFT = $(LIB_DIR)/libft.a
LIBVEC3 = $(SRC_DIR)/vec3/libvec3.a

SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/mlx_usage.c \
	$(SRC_DIR)/color/color.c \
	$(SRC_DIR)/color/ray_color.c \
	$(SRC_DIR)/ray.c \
	$(SRC_DIR)/sphere.c \
	$(SRC_DIR)/hittable.c \
	$(MAT_DIR)dielectric.c \
	$(MAT_DIR)dielectric_utils.c \
	$(MAT_DIR)lambertian.c \
	$(MAT_DIR)metal.c \
	$(CAM_DIR)camera.c \
	$(CAM_DIR)camera_utils.c \
	$(SRC_DIR)/init/init_variables.c \
	$(SRC_DIR)/init/init_utils.c \
	$(INTER_DIR)interval.c \
	$(INTER_DIR)interval_utils.c \
	$(SRC_DIR)/lights.c \
	$(SRC_DIR)/render/render.c \
	$(SRC_DIR)/render/render_utils.c \
	$(CYL_DIR)cylinder.c \
	$(CYL_DIR)utils_cyld.c \
	$(SRC_DIR)/plane.c \
	$(PARSER_DIR)free.c \
	$(PARSER_DIR)ft_atof.c \
	$(PARSER_DIR)ft_split2.c \
	$(PARSER_DIR)parser.c \
	$(PARSER_DIR)utils.c \
	$(PARSER_DIR)vf_utils.c \
	$(PARSER_DIR)world_params.c \
	$(PARSER_DIR)objects_params.c \
	$(PARSER_DIR)gnl/get_next_line.c \
	$(PARSER_DIR)gnl/get_next_line_utils.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(LIBVEC3) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBVEC3) $(MINILIBX_FLAGS) -o $(NAME)
	@clear
	@echo "✅ $(NAME) is compiled."

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIB_DIR)

$(LIBVEC3):
	@make -C $(SRC_DIR)/vec3

$(MLX_LIB):
	@make -C minilibx-linux

val:
	@clear
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

run: all
	@clear
	./$(NAME)

clean:
	@make -C $(LIB_DIR) clean
	@make -C $(SRC_DIR)/vec3 clean
	@make -C minilibx-linux clean
	@rm -f $(OBJS)
	@clear
	@echo "🗑️ Objects removed."

fclean: clean
	@make -C $(LIB_DIR) fclean
	@make -C $(SRC_DIR)/vec3 fclean
	@rm -f $(NAME)
	@clear
	@echo "🗑️ Program and objects removed."

re: fclean all
