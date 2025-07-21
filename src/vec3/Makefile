# lib/vec3/Makefile

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = libvec3.a

SRC = \
	vec3_add.c \
	vec3_add_inplace.c \
	vec3_sub.c \
	vec3_cross.c \
	vec3_dot.c \
	vec3_div.c \
	vec3_div_inplace.c \
	vec3_length.c \
	vec3_len_squared.c \
	vec3_mul.c \
	vec3_mul_inplace.c \
	vec3_mul_vecs.c \
	vec3_neg.c \
	vec3_near_zero.c \
	vec3_reflect.c \
	vec3_refract.c \
	vec3_unit_vector.c \
	vec3.c \
	random_double.c \
	random_double_range.c \
	random_vec3.c \
	random_vec3_in_range.c \
	random_unit_vector.c \
	random_on_hemisphere.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
