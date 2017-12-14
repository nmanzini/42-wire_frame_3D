# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/29 17:51:18 by nmanzini          #+#    #+#              #
#    Updated: 2017/12/14 17:35:19 by nmanzini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = 	main.c

OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

HEADER = -c -I fdf.h

W_FLAGS = -Wall -Werror -Wextra

MLX_FLAGS = -lmlx -framework Opengl -framework Appkit

all: $(NAME)

$(OBJ): %.o: %.c
		-@gcc -c $(W_FLAGS) -I libft/ $< -o $@

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
