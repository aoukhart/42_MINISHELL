/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:38:03 by an4ss             #+#    #+#             */
/*   Updated: 2022/11/27 06:32:04 by ybachaki         ###   ########.fr       */
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
	if (!input->redirrections && !input->pipe)
		execute(input, env);
	else if (input->redirrections && !input->pipe)
		ft_redic(input, env);
	else if (input->pipe)
		ft_pipes(input, env);
}

int main(int ac, char **av, char **envp)
{
	char *s;
	char **env;
	(void)av;
	t_input *input;
	if (ac == 1)
	{
		env = init_env(envp);
		input = malloc(sizeof(t_input));
		g_var = 0;
		while (1)
		{

			signals();
			s = readline("minishell>>");
			if (!s)
				exit(0);
			if (!s[0])
			{
				free(s);
				continue;
			}
			add_history(s);
			step_one(s, input, env);
			execution(input, env);
		}
	}
	return 0;
}
