SRC = main.c\
		builtins/cd.c\
		builtins/export.c\
		builtins/env.c\
		builtins/unset.c\
		builtins/echo.c\

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -lreadline #-fsanitize=address

NAME = minishell

all : $(NAME)

$(NAME) : $(OBJ)
	@gcc $(FLAGS) $(SRC) Libft/libft.a -o $(NAME)

clean :
	@rm -rf $(OBJ)
	
fclean : clean
	@rm -rf $(NAME)

re : fclean all