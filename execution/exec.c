/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:15:34 by an_ass            #+#    #+#             */
/*   Updated: 2022/12/01 17:22:23 by an4ss            ###   ########.fr       */
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
        if (execve(cmd[0], cmd, env) == -1)
        {
            perror("minishl");
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

int    check_builtins_1(t_input *input, char **env)
{
    char *built_in[5] = {
        "cd", "env", "export", "unset", "echo"
    };
    void (*fcts[5])(t_input*, char**) = {
        cd, my_env, export, unset, echo
    };
    int i = -1;
    while (++i < 5)
    {
        if (ft_strncmp(input->cmd[0], built_in[i],
             ft_strlen(built_in[i]) + 1) == 0)
        {
            fcts[i](input, env);
        }
    }    
    if (ft_strncmp(input->cmd[0], "cd", 3) == 0)
    {
        cd(input, env);
        return 0;
    }
    else if (ft_strncmp(input->cmd[0], "env", 4) == 0)
    {
        my_env(input, env);
        return 0;
    }
    else if (ft_strncmp(input->cmd[0], "exit", 5) == 0)
    {
        printf("exit\n");
        exit(0);
    }
    return 1;
}

int check_builtins_2(t_input *input, char **env)
{
    if (ft_strncmp(input->cmd[0], "pwd", 4) == 0)
    {
        char tmp[256];
        printf("%s\n", getcwd(tmp, sizeof(tmp)));
        g_var = 0;
        return 0;
    }
    else if (ft_strncmp(input->cmd[0], "export", 7) == 0)
    {
        export(input, env);
        return 0;
    }
    else if (ft_strncmp(input->cmd[0], "unset", 6) == 0)
    {
        unset(input, env);
        return 0;
    }
    else if (ft_strncmp(input->cmd[0], "echo", 5) == 0)
    {
        echo(input, env);
        return 0;
    }
    return 1;
}

int    check_builtins(t_input *input, char **env)
{
    return (check_builtins_1(input, env) 
        & check_builtins_2(input, env));
}

void execute(t_input *input, char **env)
{   

    if (check_builtins(input, env) 
        && ft_strncmp(input->cmd[0], "pwd", 4) 
        && ft_strncmp(input->cmd[0], "echo", 5))
        exec(input, env);
}
