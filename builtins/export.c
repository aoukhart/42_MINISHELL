#include "../INCLUDE/minishell.h"

void    printf_export(char *env)
{
    int i = 0;
    printf("declare -x ");
    if (ft_strchr(env, '='))
    {
        while (env[i]!= '=')
            printf("%c", env[i++]);
        printf("=\"");
        i++;
        printf("%s\"\n", (env + i));
    }
    else
        printf("%s\n", env);
}

int check_dup_env(char *cmd, char **env)
{

    int i = 0;
    if (cmd == NULL)
        return 0;
    while (env[i])
    {
        if (!ft_strncmp(env[i], cmd, length(env[i])) && (length(cmd) == length(env[i])))
            return (i);
        else
            i++;
    }
    return 0;
}

void    export_1(char *cmd, t_progres *progress, int len)
{
    char **env1;
    int i;
    int x;

    i = 0;
    if ((x = check_dup_env(cmd, progress->envp)) && !ft_strchr(cmd, '=')
        && length(progress->envp[x]) == length(cmd))
    {
        printf("%d\n", x);
        return;
    }
    if ((x = check_dup_env(cmd, progress->envp)) && ft_strchr(cmd, '=') 
        && (length(cmd) == length(progress->envp[x])))
        {
            progress->envp[x] = ft_strdup(cmd);
            printf("%d\n", x);
        }
    else
    {
        env1 = malloc(sizeof(char*) * (len + 2));
        env1[len + 1] = NULL;
        env1[len] = ft_strdup(cmd);
        i = -1;
        while (++i < len)
            env1[i] = progress->envp[i];
        free(progress->envp);
        progress->envp = env1;
    }
}

int export_check(char *cmd)
{
    int  i = 1;
    if (cmd[0] != '_' && !ft_isalpha(cmd[0]))
    {
        ft_putstr_fd("Minishell: not a valid identifier\n", 2);
        g_var = 1;
        return (0);
    }
    while (i < (int)length(cmd))
    {
        if (cmd[i] != '_' && !ft_isalnum(cmd[i]))
        {
            ft_putstr_fd("Minishell: not a valid identifier\n", 2);
            g_var = 1;
            return (0);
        }
        i++;
    }
    if (ft_strncmp(cmd, " ", 2)== 0)
    {
        ft_putstr_fd("Minishell: not a valid identifier\n", 2);
        g_var = 1;
        return (0);
    }
    return (1);
}

void export(t_input *input, t_progres *progress)
{
    int i;
    int len;

    if (input->cmd[1])
    {
        i = 1;
        while (input->cmd[i])
        {
            if (export_check(input->cmd[i]) == 1)
            {
                len = -1;
                while (progress->envp[++len]);
                export_1(input->cmd[i], progress, len);
            }
            i++;
        }
    }
    else
    {
        i = 0;
        while (progress->envp[i])
        {
            printf_export(progress->envp[i]);
            i++;
        }
    }
}
