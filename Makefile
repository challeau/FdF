NAME			=	fdf

SRC_PATH		= 	./srcs
SRC_NAME		=	main.c		\
				fdf.c		\
				parser.c	\
				utils.c
OBJ_PATH = objs
OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

SRCS_UTILS_PATH		=	./srcs/utils
SRCS_UTILS_NAME		=	mat3.c			\
				mat4.c			\
				maths_utils.c		\
				vec2f.c			\
				vec2f_ops.c		\
				vec2f_scal_ops.c	\
				vec3f.c			\
				vec3f_ops.c		\
				vec3f_scal_ops.c	\
				vec4f.c			\
				vec_mat_ops.c

OBJS_UTILS_PATH	=	objs/utils
OBJS_UTILS_NAME	=	$(SRCS_UTILS_NAME:.c=.o)

SRCS_UTILS = $(addprefix $(SRCS_UTILS_PATH)/,$(SRCS_UTILS_NAME))
OBJS_UTILS = $(addprefix $(OBJS_UTILS_PATH)/,$(OBJS_UTILS_NAME))

CC		=	clang
CFLAGS		=	-Wall -Werror -Wextra -g 

CPPFLAGS	=	-I inc/libft/ -I inc/minilibx-linux/

LDFLAGS		=	inc/libft/libft.a inc/minilibx-linux/libmlx_Linux.a
LDLIBS		=	-lm -lX11 -lXext

all: $(NAME)

$(NAME): $(OBJ) $(OBJS_UTILS)
	@make -C inc/libft
	@make -C inc/minilibx-linux
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $^ $(LDFLAGS) $(LDLIBS)
	@echo "Compilation \033[1;32mOK\033[m"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) -c $< $(CPPFLAGS) -o $@

$(OBJS_UTILS_PATH)/%.o: $(SRCS_UTILS_PATH)/%.c
	@mkdir $(OBJS_UTILS_PATH)   2> /dev/null || true
	@$(CC) $(CFLAGS) -c $< $(CPPFLAGS) -o $@

clean:
	@make -C inc/libft clean
	@make -C inc/minilibx-linux clean
	@rm -f $(OBJ) $(OBJS_UTILS)
	@rmdir $(OBJ_PATH) $(OBJS_UTILS_PATH)
	@echo "Removing objs"

fclean: clean
	@make -C inc/libft fclean
	@make -C inc/minilibx-linux clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
