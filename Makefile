# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/06 15:04:00 by jmunoz            #+#    #+#              #
#    Updated: 2016/05/17 14:44:04 by jmunoz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS= -I Includes -Wall -Wextra -Werror
SRC=	Sources/ft_ls.c\
		Sources/parsing.c\
		Sources/padding.c\
		Sources/build_lst.c\
		Sources/support.c\
		Sources/get_infos.c\
		Sources/print.c
OBJ=$(SRC:.c=.o)
NAME=ft_ls

all: lib $(NAME)

lib:
	make -C libft/

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME) : $(OBJ)
	 	$(CC) $(CFLAGS) $(OBJ) libft/libft.a -o $@

clean:
	rm -rf $(OBJ)
	make clean -C libft/

fclean: clean
	rm $(NAME)
	make fclean -C libft

re: fclean all
