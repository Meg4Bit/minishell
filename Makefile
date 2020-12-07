NAME = minishell
LIB = libft
CC = gcc
SRC =   main.c\
		command_line.c\
		list_parser.c\
		ft_echo.c\
		ft_pwd.c\
		ft_env.c\
		ft_export.c\
		ft_unset.c\
		ft_cd.c\
		ft_exit.c\
		func_checker.c\
		signal_handlers.c
OBJ = $(SRC:.c=.o)
#CFLAGS = -Wall -Wextra -Werror

all: libfta $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -L$(LIB) -lft -L/usr/lib -lm -lbsd -o $(NAME)

libfta:
	@cd $(LIB) && make

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -O3 -c $< -o $@

bonus:
	$(MAKE) all

clean:
	/bin/rm -f *.o
	make clean -C libft

fclean: clean
	/bin/rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re