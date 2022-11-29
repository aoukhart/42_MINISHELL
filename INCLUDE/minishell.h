/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 23:40:57 by ybachaki          #+#    #+#             */
/*   Updated: 2022/11/28 09:20:26 by ybachaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include "../Libft/libft.h"

extern int	g_var;

typedef struct s_progres
{
	char	**envp;
	char	*input;
	int		i;
}	t_progres;

typedef struct s_redirect
{
	char				type;
	int					fd;
	char				*delimiter;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_input
{
	char				**cmd;
	int					pipe;
	t_redirect			*redirrections;
	int					exit_val;
	struct s_input		*next;
}	t_input;

char		*env_3(t_progres *progree);
char		*env_num(t_progres *progree);
char		*env_alpha(t_progres *progree);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
void		*ft_calloc(size_t count, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
void		ft_bzero(void *s, size_t n);
void		input_parsser(t_progres *progree, t_input *data);
char		*ft_strjoin1(char *s1, char *s2);
void		skip_spaces(t_progres *progree);
void		input_reader(t_progres *progree, t_input *data);
void		init_struct(t_input	*data);
void		step_one(char *str, t_input *input, char **envp);
void		redirection_handler(t_progres *progree, t_input *data);
void		arg(t_progres *progree, t_input *data);
char		*quotes_handler(t_progres *progree);
char		*ft_chr(char **env, char *variabel);
char		*d_quotes_handler(t_progres *progree);
char		*env_var(t_progres *progree);
char		*s_quotes_handler(t_progres *progree);
void		add(t_input *data, char *str);
void		init_struct2(t_redirect *data);
char		*env_var2(t_progres *progree);
void		ft_open(t_progres *progree, t_redirect *tmp, int i);
char		*word_extract(t_progres *progree);
void		redirect(t_progres *progree, t_redirect *tmp);
int			car_check(char c, int i);
char		*car_join(char *s1, char c);
void		ft_free1(t_progres *progree, t_input *data);
void		ft_free2(t_input *data);
char	*heredoc(t_progres *progree);
/*EXEC*/
void		ft_redic(t_input *input, char **env);
int			ft_heredoc(char *s, char **env);
void		exec_cmds(t_input *input, char **env);
void		ft_pipes(t_input *input, char **env);
void		cd(char **cmd, char **env);
void		change_old_pwd(char *old_pwd, char **env);
void		export(char **cmd, char **env);
void		my_env(char **env);
void		unset(char **cmd, char **env);
char		**ft_free(char **str);
int			check_dup_env(char *cmd, char **env);
size_t		length(char *s);
void		echo(t_input *input, char **env);
void		exec(t_input *input, char **env);
void		signals(void);
void		execute_cmd(char **cmd, char **env);
char		*check_path(char **cmd, char **path);
char		*get_path(char **cmd, char *envp[]);
char		**init_env(char **envp);
void		execute(t_input *input, char **env);
void		close_all(int fd[2]);
void		wait_all(int *pid, int x);
int			get_in(t_input *tmp, int fd_in, char **env);
int			get_out(t_input *tmp, int fd_out);

#endif