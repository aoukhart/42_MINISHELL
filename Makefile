SRC = main.c\
		builtins/cd.c\
		builtins/export.c\
		builtins/env.c\
		builtins/unset.c\
		builtins/echo.c\
		execution/exec.c\
		signals.c\
		parsing/args.c\
		parsing/env.c\
		parsing/parsing.c\
		parsing/quotes.c\
		parsing/redirections.c\
		parsing/utiles.c\
		parsing/utiles2.c\
		pipes/pipes.c\
		redirections/redirection.c\

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