/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:54:44 by aoukhart          #+#    #+#             */
/*   Updated: 2022/12/17 02:06:24 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

int	get_line_len(t_input *input)
{
	t_input	*tmp;
	int		pipe;

	pipe = 0;
	tmp = input;
	while (tmp)
	{
		if (tmp->pipe)
			pipe++;
		tmp = tmp->next;
	}
	return (pipe);
}

void	open_file(int i, char *s, char **env)
{
	int	fd;

	fd = open(ft_strjoin("minishell_", ft_itoa(i)), \
		O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell");
		exit(1);
	}
	ft_heredoc_v2(s, env, fd);
	close(fd);
}

void	ft_heredoc_v2(char *s, char **env, int fd)
{
	t_progres	ptr;
	char		*str;

	ptr.i = 0;
	ptr.envp = env;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_DFL);
	ptr.input = readline(">");
	while (ptr.input && ft_strncmp(ptr.input, s, ft_strlen(s) + 1))
	{
		str = heredoc(&ptr);
		if (!str)
			str = s;
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		ptr.i = 0;
		ptr.input = readline(">");
	}
}

void	open_herdoc_file(t_input *input, char **env)
{
	int			i;
	int			len;
	t_input		*tmp;
	t_redirect	*redir;

	i = 0;
	tmp = input;
	len = get_line_len(tmp);
	while (i <= len && tmp)
	{
		redir = tmp->redirrections;
		while (redir)
		{
			if (redir->type == '<' && redir->delimiter)
				open_file(i, redir->delimiter, env);
			redir = redir->next;
		}
		i++;
		tmp = tmp->next;
	}
	exit(0);
}
