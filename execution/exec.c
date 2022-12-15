/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:15:34 by an_ass            #+#    #+#             */
/*   Updated: 2022/12/15 06:43:25 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

void	exec(t_input *input, t_progres *progress)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed\n");
		return ;
	}
	else if (pid == 0)
	{
		signal(2, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (execve(get_path(input->cmd, progress->envp),
				input->cmd, progress->envp) == -1)
		{
			if (errno = 8)
			{
				ft_putstr_fd("minishell: permission denied\n", 2);
				exit(126);
			}
			exit(127);
		}
	}
	else
		handle_exit_val(pid);
}

void	execute_builtin(t_input *input, t_progres *progress, int index)
{
	void (*fcts[7])(t_input*, t_progres*) = {
		cd, my_env, export, unset, echo, pwd, ft_exit
	};
	fcts[index](input, progress);
}

char	**add_after_split(char **src, char **dest)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	j = 1;
	res = ft_calloc(ft_len(src) + ft_len(dest), sizeof(char *));
	while (dest[i])
	{
		res[i] = dest[i];
		i++;
	}
	while (src[j])
	{
		res[i] = src[j];
		j++;
		i++;
	}
	free(dest);
    free(src[0]);
	free(src);
	return (res);
}
int	check_error_single_cmd(t_input *input)
{
    if (input->redirrections && (input->redirrections->fd) == -2)
    {
        ft_putstr_fd("minishell: ambigious redirect\n", 2);
		g_var = 1;
        return (0);
    }
    else if (input->redirrections && (input->redirrections->fd) == -1)
    {
        perror("minishell");
		g_var = 1;
        return (0);
    }
    return (1);
}

void execute_single_cmd(t_input *input, t_progres *progress)
{
    if (execute_heredocs(input, progress->envp))
    {
        g_var = 1;
        return;
    }
    if (!check_error_single_cmd(input))
        return;
    if(input->cmd)
    {
        int cmd_type = is_builtin(input);
        if (input->redirrections)
        {
            if (is_builtin(input) == NOT_BUILT_IN)
                redic_not_builtin(input, progress->envp);
            else
                redic_builtin(input, progress);
        }
        else
        {
            if (cmd_type == NOT_BUILT_IN)
                exec(input, progress);
            else
                execute_builtin(input, progress, cmd_type);
        }
    }
    else
        unlink("minishell_0");
}
