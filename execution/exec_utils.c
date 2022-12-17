/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 19:37:07 by an4ss             #+#    #+#             */
/*   Updated: 2022/12/17 01:17:18 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

char	**ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

char	*check_path(char **cmd, char **path)
{
	int		i;
	char	*new_cmd;
	char	*new_path;

	i = -1;
	while (path[++i])
	{
		new_cmd = ft_strjoin("/", cmd[0]);
		new_path = ft_strjoin(path[i], new_cmd);
		free(new_cmd);
		if (access(new_path, F_OK) == 0)
		{
			ft_free(path);
			return (new_path);
		}
		free(new_path);
	}
	ft_free(path);
	return (ft_strdup(cmd[0]));
}

char	*get_path(char **cmd, char **envp)
{
	int		i;
	char	**path;

	i = 0;
	if (!ft_chr(envp, ft_strdup("PATH")))
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		exit(127);
	}
	while (ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	path = ft_split(envp[i] + 5, ':');
	return (check_path(cmd, path));
}

void	exec_in_child(t_input *input, char **env)
{
	input->cmd[0] = get_path(input->cmd, env);
	if (execve(input->cmd[0], input->cmd, env) == -1)
	{
		check_permission();
		perror("minishell");
		exit(127);
	}
}

void	execution(t_input *input, t_progres *progres)
{
	signal(SIGINT, SIG_IGN);
	if (!input->pipe)
		execute_single_cmd(input, progres);
	else
		ft_pipes(input, progres);
}
