SRC = main.c\
		signals.c\
		builtins/cd.c\
		builtins/export.c\
		builtins/env.c\
		builtins/unset.c\
		builtins/pwd.c\
		builtins/echo.c\
		builtins/exit.c\
		execution/exec.c\
		execution/exec_utils.c\
		parsing/args.c\
		parsing/env.c\
		parsing/parsing.c\
		parsing/quotes.c\
		parsing/redirections.c\
		parsing/utiles.c\
		parsing/utiles1.c\
		parsing/utiles2.c\
		pipes/pipes.c\
		pipes/pipes_utils.c\
		redirections/redirection.c\
		redirections/redirect_utils.c\
		redirections/redirect_utils2.c\
		redirections/heredoc.c\

FLAGS = -Wall -Wextra -Werror

NAME = minishell

all : $(NAME)

$(NAME) : $(SRC)
	@gcc $(FLAGS) $(SRC) Libft/libft.a -o $(NAME) -lreadline -L /goinfre/aoukhart/homebrew/opt/readline/lib -I /goinfre/aoukhart/homebrew/opt/readline/include #-fsanitize=address -g
clean :
	@rm -rf $(NAME)
	
fclean : clean

re : fclean all

# @gcc $(FLAGS) $(SRC) Libft/libft.a -o $(NAME) -lreadline -L /goinfre/aoukhart/homebrew/opt/readline/lib -I /goinfre/aoukhart/homebrew/opt/readline/include