NAME			=	fdf

SRC_PATH		= 	./srcs
SRC_NAME		=	main.c		\
				events.c	\
				error.c		\
				parser.c	\
				parser_utils.c	\
				maths_utils.c	\
				draw.c
OBJ_PATH = objs
OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

CC		=	clang
CFLAGS		=	-Wall -Werror -Wextra -g 

CPPFLAGS	=	-I inc/libft/ -I inc/minilibx-linux/

LDFLAGS		=	inc/libft/libft.a inc/minilibx-linux/libmlx_Linux.a
LDLIBS		=	-lm -lX11 -lXext

all: $(NAME)
$(NAME): $(OBJ)
	@make -C inc/libft
	@make -C inc/minilibx-linux
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $^ $(LDFLAGS) $(LDLIBS)
	@echo "Compilation \033[1;32mOK\033[m"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) -c $< $(CPPFLAGS) -o $@

clean:
	@make -C inc/libft clean
	@make -C inc/minilibx-linux clean
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH)

fclean: clean
	@make -C inc/libft fclean
	@make -C inc/minilibx-linux clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
