#ifndef MINISHE_H
# define MINISHE_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "../Libft/libft.h"

extern int g_var;

typedef	struct	s_progres
{
	char	**envp;
	char	*input;
	int		i;
}	t_progres;

typedef	struct	s_redirect
{
	char	type; // change
	int		fd;
	struct	s_redirect *next;
}	t_redirect;

typedef struct s_input
{
	char				**cmd;
	int					pipe;
	t_redirect			*redirrections;
	int					exit_val;
	struct	s_input		*next;
}	t_input;


//static int	leftcheck(char const *s, char const *set);
//static int	rightcheck(char const *s, char const *set);
//char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strdup3(const char *s1, int len);
char		*ft_strjoin2(char *s1, char *s2);
void		input_parsser(t_progres *progree, t_input *data);
void		skip_spaces(t_progres *progree);
void		input_reader(t_progres *progree, t_input *data);
void		init_struct(t_input	*data);
void		step_one(char *str, t_input *input ,char **envp);
void		redirection_handler(t_progres *progree, t_input *data);
void		arg(t_progres *progree, t_input *data);
char		*ft_chr(char **env, char *variabel);
void		add(t_input *data, char *str);
char		*quotes_handler(t_progres *progree);
char		*ft_chr(char **env, char *variabel);
char		*d_quotes_handler(t_progres *progree);
char		*env_var(t_progres *progree);
char		*s_quotes_handler(t_progres *progree);
void		init_struct2(t_redirect *data);
char		*env_var2(t_progres *progree);
void		ft_open(t_progres *progree, t_redirect *tmp, int	i);
char		*word_extract(t_progres *progree);
void		redirect(t_progres *progree, t_redirect *tmp);
                /*EXEC*/
void    ft_redic(t_input *input, char **env);
int	ft_heredoc(char *s);
void exec_cmds(t_input *input, char **env);
void	ft_pipes(t_input *input, char **env);
void    cd(char **cmd, char **env);
void	change_old_pwd(char *old_pwd, char **env);
void    export(char **cmd, char **env);
void    my_env(char **env);
void    unset(char **cmd, char **env);
char	**ft_free(char **str);
int     check_dup_env(char *cmd, char **env);
size_t  length(char *s);
void    echo(t_input *input, char **env);
void    exec(t_input *input, char **env);
void    signals();
void    execute_cmd(char **cmd, char **env);
char	*check_path(char **cmd, char **path);
char	*get_path(char **cmd, char *envp[]);
char **init_env(char **envp);
void execute(t_input *input, char **env);
int get_fd_in(t_input *input);
int get_fd_out(t_input *input);

#endif