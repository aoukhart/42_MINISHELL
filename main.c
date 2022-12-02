/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:38:03 by an4ss             #+#    #+#             */
/*   Updated: 2022/12/02 15:55:12 by ybachaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "INCLUDE/minishell.h"

int	g_var;

char	**init_env(char **envp)
{
	char	**env;
	int		i = 0;

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

void	execution(t_input *input, char **env)
{
	signal(2, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (!input->redirrections && !input->pipe)
		execute(input, env);
	else if (input->redirrections && !input->pipe)
		ft_redic(input, env);
	else if (input->pipe)
		ft_pipes(input, env);
	printf("safi ra salaw\n");
}

void	init(t_progres	**progree, t_input **input, char **envp)
{
	*progree = malloc(sizeof(t_progres));
	*input = malloc(sizeof(t_input));
	(*progree)->i = 0;
	(*progree)->envp = envp;
	init_struct(*input);
}

int	check_progree(t_progres *progree)
{
	if (!progree->input)
	{
		free(progree);
		exit(0);
	}
	if (!progree->input[0])
	{
		free(progree->input);
		free(progree);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char		**env;
	t_progres	*progree;
	t_input		*input;

	(void)av;
	progree = NULL;
	input = NULL;
	if (ac == 1)
	{
		env = init_env(envp);
		g_var = 0;
		while (1)
		{
			init(&progree, &input, env);
			signals();
			progree->input = readline("minishell>>");
			if (check_progree(progree))
				continue ;
			add_history(progree->input);
			step_one(progree, input);
			ft_free1(progree, input);
		}
	}
	return (0);
}
