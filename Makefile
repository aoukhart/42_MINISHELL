SRC = main.c\
		builtins/cd.c\
		builtins/export.c\
		builtins/env.c\
		builtins/unset.c\
		builtins/echo.c\
		signals.c\
		execution/exec.c\

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror #-fsanitize=address

NAME = minishell

all : $(NAME)

$(NAME) : $(OBJ)
	@gcc $(FLAGS) $(SRC) Libft/libft.a -o $(NAME) -lreadline -L /goinfre/aoukhart/homebrew/opt/readline/lib -I /goinfre/aoukhart/homebrew/opt/readline/include

clean :
	@rm -rf $(OBJ)
	
fclean : clean
	@rm -rf $(NAME)

re : fclean all