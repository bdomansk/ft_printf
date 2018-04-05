# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bdomansk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/11 18:07:42 by bdomansk          #+#    #+#              #
#    Updated: 2018/02/23 11:40:26 by bdomansk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
HEADER = ft_printf.h 
FLAGS = -Wall -Wextra -Werror
SRC = ft_printf.c ft_strlen.c ft_add_to_buffer.c ft_select_type.c ft_putd.c \
	ft_find_specifiers.c ft_putc.c ft_puts.c ft_putoux.c ft_uitoa.c \
	ft_put_bigs.c
OBJ = *.o
NORM = norminette
DEL = /bin/rm -f

.PHONY : all clean n fclean re test

all : $(NAME)

$(NAME) : $(OBJ)
	@echo "libftprintf.a creating"
	@ar rc $(NAME) $(OBJ)
$(OBJ) : $(SRC)
	@echo "libftprintf objects creating"
	@gcc $(FLAGS) -c -I $(HEADER) $(SRC)
n :
	@$(NORM) $(SRC) $(HEADER)
clean:
	@echo "Cleaning objects"
	@$(DEL) $(OBJ)
fclean : clean
	@echo "Cleaning .a file"
	@$(DEL) $(NAME)
re : fclean all
test :
	gcc $(FLAGS) -o f main.c $(NAME)
