# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/29 17:51:18 by nmanzini          #+#    #+#              #
#    Updated: 2018/01/23 15:01:43 by nmanzini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = 	./main.c 				\
		./call_keys.c			\
		./call_keys_utils.c		\
		./change.c 				\
		./input.c				\
		./input_util.c			\
		./mlx_utils.c			\
		./project.c				\

OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

HEADER = -c -I fdf.h

W_FLAGS = -Wall -Werror -Wextra

MLX_FLAGS = -lmlx -framework Opengl -framework Appkit

all: $(NAME)

$(OBJ): %.o: %.c
		-@gcc -c  -I libft/ $< -o $@

$(LIBFT):
	-@ make -C libft 

$(NAME): $(LIBFT) $(OBJ)
	-@ gcc $(W_FLAGS) $(MLX_FLAGS) $(OBJ) $(LIBFT) -o $(NAME)

clean:
	-@ /bin/rm -f $(OBJ)
	-@ make -C libft clean

fclean: clean
	-@ /bin/rm -f $(NAME)
	-@ make -C libft fclean

re: fclean all
