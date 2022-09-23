#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "Libft/libft.h"


void    cd(char **cmd, char **env);
void	change_old_pwd(char *old_pwd, char **env);
void    export(char **cmd, char **env);
void    my_env(char **env);
void    unset(char **cmd, char **env);
char	**ft_free(char **str);
int     check_dup_env(char *cmd, char **env);
size_t  length(char *s);
void    echo(char **cmd, char **env);
void    exec(char **cmd, char **env);
void    signals();
void    execute_cmd(char **cmd, char **env);
char	*check_path(char **cmd, char **path);
char	*get_path(char **cmd, char *envp[]);
char **init_env(char **envp);
void check_builtins(char **cmd, char **env);

#endif