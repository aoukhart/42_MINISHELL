/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:35:06 by ybachaki          #+#    #+#             */
/*   Updated: 2022/11/25 22:55:41 by ybachaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

void	init_struct2(t_redirect *data)
{
	data->fd = -1;
	data->type = '\0';
	data->next = NULL;
	data->delimiter = NULL;
}

void	input_reader(t_progres *progree, t_input *data)
{
		if(progree->input[progree->i] && progree->input[progree->i] != '|'
		&& progree->input[progree->i] != '<'
		&& progree->input[progree->i] != '>')
			arg(progree, data);
		if(progree->input[progree->i])
		{
			if ( progree->input[progree->i] == '>' || progree->input[progree->i] == '<')
					redirection_handler(progree, data);
			if (progree->input[progree->i] == '|')
			{
				data->pipe = 1;
				progree->i++;
			}
		}
}

void	print_list(t_input *data)
{
	t_redirect	*tmp;
	int i;

	while(data)
	{
		i = 0;
		tmp = data->redirrections;
		while(data->cmd && data->cmd[i])
		{
			printf("\tcmd line %d : \"%s\"\n", i, data->cmd[i]);
			i++;
		}
		printf("\tpipe : %d\n", data->pipe);
		while(tmp)
		{
			printf("\tredirection type : %c\n", tmp->type);
			printf("\tredirection FD : %d\n", tmp->fd);
			printf("\tdelimiter : %s\n", tmp->delimiter);
			tmp = tmp->next;
		}
		data = data->next;
		printf("\t*************************************************\n");
	}
}

void	step_one(char *str, t_input *input, char **envp)
{
	t_progres	*progree;
	t_input		*temp;

	progree = malloc(sizeof(t_progres));
	if (!input || !progree)
		return;
	temp = input;
	init_struct(input);
	progree->i = 0;
	progree->input = str;
	progree->envp = envp;
	while (progree->input[progree->i])
	{
		input_reader(progree,temp);
		if(progree->input[progree->i])
		{
			temp->next = malloc(sizeof(t_input));
			init_struct(temp->next);
			temp = temp->next;
		}
	}
	print_list(input);
}

void	init_struct(t_input	*data)
{
	data->cmd = NULL;
	data->pipe = 0;
	data->redirrections = NULL;
	data->next = NULL;
}

//int	main(int argc, char **argv, char **envp)
//{
//	char *ptr;
//
//	ptr = NULL;
//	while(1)
//	{
//		ptr = readline("BC_&_anaslm9awed_shell>");
//		if(*ptr)
//		{
//			step_one(ptr, envp);
//		}
//	}
//	return (0);
//}
