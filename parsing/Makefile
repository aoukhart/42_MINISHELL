SRC =	args.c\
		env.c\
		parsing.c\
		quotes.c\
		redirections.c\
		utiles.c\
		utiles2.c\
		utiles1.c\

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -fsanitize=address

NAME = pars

all : $(NAME)

$(NAME) : $(OBJ)
	@gcc $(FLAGS) $(SRC) ../Libft/libft.a -o $(NAME) -lreadline

clean :
	@rm -rf $(OBJ)
	
fclean : clean
	@rm -rf $(NAME)

re : fclean all