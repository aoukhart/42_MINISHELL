/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 19:37:07 by an4ss             #+#    #+#             */
/*   Updated: 2022/11/13 04:49:25 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

char **ft_free(char **str)
{
    int i;

    i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
    return (NULL);
}

char *check_path(char **cmd, char **path)
{
    int i;
    char *new_cmd;
    char *new_path;

    i = 0;
    while (path[i++])
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
    return (ft_strdup(cmd[0])); // leak;
}

char *get_path(char **cmd, char *envp[])
{
    int i;
    char **path;

    i = 0;
    while (ft_strncmp(envp[i], "PATH", 4) != 0)
        i++;
    path = ft_split(envp[i] + 5, ':');
    i = 0;
    return (check_path(cmd, path));
}

void exec(t_input *input, char **env)
{

    if (access(input->cmd[0], X_OK) == 0)
    {
        execute_cmd(input->cmd, env);
        // if (cmd[0])
        // ft_free(cmd);
        return;
    }
    int i = 1;
    char *path;
    path = get_path(input->cmd, env);
    while (input->cmd[i])
    {
        path = ft_strjoin(path, " ");
        path = ft_strjoin(path, input->cmd[i]);
        i++;
    }
    execute_cmd(ft_split(path, ' '), env);
    free(path);
}

void exec_cmds(t_input *input, char **env)
{

	if (ft_strncmp(input->cmd[0], "env", 4) == 0)
		my_env(env);
	else if (ft_strncmp(input->cmd[0], "export", 7) == 0)
		export(input->cmd, env);
	else if (ft_strncmp(input->cmd[0], "echo", 5) == 0)
		echo(input, env);
	else
	{
		if (execve(get_path(input->cmd, env), input->cmd, env) == -1)
		{
			//printf("%s\n", get_path(input->cmd, env));
			perror("MINISHE");
			exit(127);
		}
	}
	exit(0);
}
