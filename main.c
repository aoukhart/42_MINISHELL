/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:38:03 by an4ss             #+#    #+#             */
/*   Updated: 2022/12/02 14:05:40 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "INCLUDE/minishell.h"

int g_var;

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

void execution(t_input *input, char **env)
{
	signal(2, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (!input->pipe)
		execute_single_cmd(input, env);
	else
		ft_pipes(input, env);
}

int main(int ac, char **av, char **envp)
{
	char **env;
	(void)av;
	t_progres	*progree;
	if (ac == 1) // main khasso it3awed
	{
		env = init_env(envp);
		
		g_var = 0;
		while (1)
		{
			progree = malloc(sizeof(t_progres));
			progree->envp = env;
			progree->i = 0;
			signals();
			progree->input = readline("minishell>>");
			if (!progree->input)
				exit(0);
			if (!progree->input[0])
			{
				
				free(progree->input);
				free(progree);
				continue;
			}
			add_history(progree->input);
			step_one(progree);
			//execution(input, env);
		}
	}
	return 0;
}
