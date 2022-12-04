/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:15:34 by an_ass            #+#    #+#             */
/*   Updated: 2022/12/02 14:36:10 by an4ss            ###   ########.fr       */
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

void    execute_builtin(t_input *input, char **env, int index)
{
    void (*fcts[5])(t_input*, char**) = {
        cd, my_env, export, unset, echo
    };
    fcts[index](input, env);
    
}


void execute_single_cmd(t_input *input, char **env)
{   
    int cmd_type = is_builtin(input);
    if (cmd_type == NOT_BUILT_IN)
    {
        if (input->redirrections)
            ft_redic(input, env);
        else
            exec(input, env);
    }
    else
        execute_builtin(input, env, cmd_type);
}
