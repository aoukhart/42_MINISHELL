/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 23:40:57 by ybachaki          #+#    #+#             */
/*   Updated: 2022/12/14 14:14:53 by aoukhart         ###   ########.fr       */
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

#define NOT_BUILT_IN -1
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
void		free_dptr(t_input *input, int j);
int			ft_len(char **tab);
void		print_list(t_input *data);
int			check_spaces(char *str);
char		*file_name_extract(t_progres *progree);
int			input_checker(t_input *input);
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
void		step_one(t_progres *progree, t_input *input);
void		redirection_handler(t_progres *progree, t_input *data);
void		arg(t_progres *progree, t_input *data);
char		*quotes_handler(t_progres *progree, int i);
char		*ft_chr(char **env, char *variabel);
char		*d_quotes_handler(t_progres *progree, int i);
char		*env_var(t_progres *progree);
char		*s_quotes_handler(t_progres *progree);
void		add(t_input *data, char *str);
void		init_struct2(t_redirect *data);
char		*env_var2(t_progres *progree);
void		ft_open(t_progres *progree, t_redirect *tmp, int i, t_input *input);
char		*word_extract(t_progres *progree, int i, t_input *input);
void		redirect(t_progres *progree, t_redirect *tmp, t_input *input);
int			car_check(char c, int i);
char		*car_join(char *s1, char c);
void		ft_free1(t_progres *progree, t_input *data);
void		ft_free2(t_input *data);
char		*heredoc(t_progres *progree);
/*EXEC*/
void 		execution(t_input *input, t_progres *progress);
void		ft_redic(t_input *input, char **env);
int			ft_heredoc(char *s, char **env);
void		exec_cmds(t_input *input, char **env);
void		ft_pipes(t_input *input, t_progres *progress);
void		cd(t_input *input, t_progres *progress);
void		change_old_pwd(char *old_pwd, char **env);
void		export(t_input *input, t_progres *progress);
void		my_env(t_input *input, t_progres *progress);
void		unset(t_input *input, t_progres *progress);
char		**ft_free(char **str);
int			check_dup_env(char *cmd, char **env);
size_t		length(char *s);
void		echo(t_input *input, t_progres *progress);
void		exec(t_input *input, char **env);
void		signals(void);
void		execute_cmd(char **cmd, char **env);
char		*check_path(char **cmd, char **path);
char		*get_path(char **cmd, char *envp[]);
char		**init_env(char **envp);
void		execute_single_cmd(t_input *input, t_progres *progress);
void		close_all(int fd[2]);
void		wait_all(int *pid, int x);
int			get_in(t_input *tmp, int fd_in);
int			get_out(t_input *tmp, int fd_out);
void    check_builtins(t_input *input, char **env);
int check_builtins_2(t_input *input, char **env);
int check_builtins_1(t_input *input, char **env);
int    is_builtin(t_input*input);
void    execute_builtin(t_input *input, t_progres *progress, int index);
void exec_in_child(t_input *input, char **env);
int execute_heredocs(t_input *input, char **env);
int get_in_v2(t_input *tmp, int fd_in, int index);
void heredoc_manager_v2(t_progres ptr, int fd, char *delim);
void ft_heredoc_v2(char *s, char **env, int fd);
int execute_heredocs(t_input *input, char **env);
int get_line_len(t_input *input);
void open_file(int i, char *s, char **env);
void open_herdoc_file(t_input *input, char **env);
void handle_exit_val(int pid);
void dup_in_out(int in, int out);
void restore_fd(int in, int out, int new_in, int new_out);
void pwd(t_input *input, t_progres *progress);
void redic_not_builtin(t_input *input, char **env);
void redic_builtin(t_input *input, t_progres *progress);
void    ft_exit(t_input *input, t_progres *progress);
void	check_error(int in, int out);

#endif