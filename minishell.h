#ifndef MNISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "Libft/libft.h"

void    cd(char **cmd, char **env);
void	change_old_pwd(char *old_pwd, char **env);


#endif