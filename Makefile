SRC = ft_printf.c
CC = cc
OBJS = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a
L_CRT = ar rcs

$(NAME) : $(OBJS)
	$(L_CRT) $(NAME) $(?)

	
all :$(NAME)

clean :
	rm -f $(OBJS)
	
fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all bonus re fclean clean
