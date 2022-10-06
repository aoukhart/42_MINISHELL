/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an_ass <an_ass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:15:34 by an_ass            #+#    #+#             */
/*   Updated: 2022/10/06 18:59:55 by an_ass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_cmd(char **cmd, char **env)
{
    pid_t pid;
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
            exit(127);
        }
    }
    else if (pid >= 0)
        wait(NULL);
    ft_free(cmd);
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

void exec(char **cmd, char **env)
{

    if (access(cmd[0], X_OK) == 0)
    {
        execute_cmd(cmd, env);
        // if (cmd[0])
        // ft_free(cmd);
        return;
    }
    int i = 1;
    char *path;
    path = get_path(cmd, env);
    while (cmd[i])
    {
        path = ft_strjoin(path, " ");
        path = ft_strjoin(path, cmd[i]);
        i++;
    }
    execute_cmd(ft_split(path, ' '), env);
    free(path);
}

void check_builtins(char **cmd, char **env)
{
    if (ft_strncmp(cmd[0], "cd", 3) == 0)
        cd(cmd, env);
    else if (ft_strncmp(cmd[0], "env", 4) == 0)
        my_env(env);
    else if (ft_strncmp(cmd[0], "exit", 5) == 0)
    {
        printf("exit\n");
        exit(0);
    }
    else if (ft_strncmp(cmd[0], "export", 7) == 0)
        export(cmd, env);
    else if (ft_strncmp(cmd[0], "unset", 6) == 0)
        unset(cmd, env);
    else if (ft_strncmp(cmd[0], "echo", 5) == 0)
        echo(cmd, env);
    else
        exec(cmd, env);
    // ft_free(cmd);
}

char **init_env(char **envp)
{
    char **env;
    int i = 0;

    if (envp[0] == NULL)
        return (NULL);
    while (envp[i++])
        ;
    env = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (envp[i])
    {
        env[i] = ft_strdup(envp[i]);
        i++;
    }
    env[i] = 0;
    return (env);
}