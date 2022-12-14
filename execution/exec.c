/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:15:34 by an_ass            #+#    #+#             */
/*   Updated: 2022/12/14 16:24:12 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

void execute_cmd(char **cmd, char **env)
{
    pid_t pid;
    int status;
    pid = fork();
    if (pid == -1)
    {
        perror("fork failed\n");
        return;
    }
    else if (pid == 0)
    {
        signal(2, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        if (execve(get_path(cmd, env), cmd, env) == -1)
        {
            perror("minishell wst execute_cmd");
            exit(127);
        }
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            g_var = WEXITSTATUS(status);
        else
            g_var = 128 + WTERMSIG(status);
    }
    //ft_free(cmd);
}

void    execute_builtin(t_input *input, t_progres *progress, int index)
{
    void (*fcts[7])(t_input*, t_progres*) = {
        cd, my_env, export, unset, echo, pwd, ft_exit
    };
	//ft_putstr_fd(input->cmd[0], 1);
    fcts[index](input, progress);
}

char    **add_after_split(char **src, char **dest)
{
	int	i;
	int	j;
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
void check_error_single_cmd(t_input *input)
{
    if (input->redirrections && (input->redirrections->fd) == -2)
    {
        ft_putstr_fd("minishell: ambigious redirect\n", 2);
		g_var = 1;
        return;
    }
    else if (input->redirrections && (input->redirrections->fd) == -1)
    {
        perror("minishell");
        // ft_putstr_fd("minishell: ambigious redirect\n", 2);
		g_var = 1;
        return;
    }
}

void execute_single_cmd(t_input *input, t_progres *progress)
{
    if (execute_heredocs(input, progress->envp))
    {
        g_var = 1;
        return;
    }
    check_error_single_cmd(input);
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
                exec(input, progress->envp);
            else
                execute_builtin(input, progress, cmd_type);
        }
    }
    else
        unlink("minishell_0");
}
