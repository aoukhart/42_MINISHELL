/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:15:34 by an_ass            #+#    #+#             */
/*   Updated: 2022/10/28 22:39:22 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

void execute_cmd(char **cmd, char **env)
{
    pid_t pid;
    int status;
    pid = fork();
    signal(2, SIG_IGN);
    if (pid == -1)
    {
        perror("fork failed\n");
        return;
    }
    else if (pid == 0)
    {
        signal(2, SIG_DFL);
        if (execve(cmd[0], cmd, env) == -1)
        {
            perror("minishl");
            printf("nari 9wdtiha\n");
            exit(127);
        }
    }
    else
    {
        wait(&status);
        g_var = status >> 8;
    }
    //ft_free(cmd);
}

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



int    check_builtins(t_input *input, char **env)
{
    if (ft_strncmp(input->cmd[0], "cd", 3) == 0)
        cd(input->cmd, env);
    else if (ft_strncmp(input->cmd[0], "env", 4) == 0)
        my_env(env);
    else if (ft_strncmp(input->cmd[0], "exit", 5) == 0)
    {
        if (input->cmd[1])
            g_var = ft_atoi(input->cmd[1]);
        
        printf("%dexit\n", g_var);
        exit(0);
    }
    else if (ft_strncmp(input->cmd[0], "pwd", 4) == 0)
    {
        char tmp[256];
        getcwd(tmp, sizeof(tmp));
        printf("%s\n", tmp);
        g_var = 0;
    }
    else if (ft_strncmp(input->cmd[0], "export", 7) == 0)
        export(input->cmd, env);
    else if (ft_strncmp(input->cmd[0], "unset", 6) == 0)
        unset(input->cmd, env);
    else if (ft_strncmp(input->cmd[0], "echo", 5) == 0)
        echo(input, env);
    return (1); 
}

void execute(t_input *input, char **env)
{   

    if (check_builtins(input, env) 
        && ft_strncmp(input->cmd[0], "pwd", 4) 
        && ft_strncmp(input->cmd[0], "echo", 5))
        exec(input, env);
}

