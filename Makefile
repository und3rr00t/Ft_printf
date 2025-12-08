NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
HEADER = ft_printf.h
SRC = ft_printf.c ft_printf_utils.c ft_printf_hex_ptr.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean