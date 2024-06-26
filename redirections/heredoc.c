/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:54:44 by an4ss             #+#    #+#             */
/*   Updated: 2022/12/08 19:03:15 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

int get_line_len(t_input *input)
{
	t_input *tmp;
	int pipe = 0;
	tmp = input;
	while (tmp)
	{
		if (tmp->pipe)
			pipe++;
		tmp = tmp->next;
	}
	return pipe;
}

void open_file(int i, char *s, char **env)
{
	int fd = open(ft_strjoin("minishell_", ft_itoa(i)), \
				O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell");
		exit(1);
	}
	ft_heredoc_v2(s, env, fd);
	close(fd);
}

void ft_heredoc_v2(char *s, char **env, int fd)
{
	t_progres ptr;
    char *str;

	ptr.i = 0;
	ptr.envp = env;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_DFL);
	ptr.input = readline(">");
	str = heredoc(&ptr);
	while (str && ft_strncmp(s, str, ft_strlen(s) + 1))
	{
		if (!str)
			str = s;
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		ptr.i = 0;
		ptr.input = readline(">");
		str = heredoc(&ptr);
	}
}

void open_herdoc_file(t_input *input, char **env)
{
	int i = 0;
	t_input *tmp;
	t_redirect *redir;
	tmp = input;
	int len = get_line_len(tmp);
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
