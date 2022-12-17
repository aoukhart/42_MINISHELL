/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:45:51 by aoukhart          #+#    #+#             */
/*   Updated: 2022/12/17 02:01:20 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

void	pwd(t_input *input, t_progres *progress)
{
	char	s[1052];

	(void)input;
	(void)progress;
	getcwd(s, sizeof (s));
	printf("%s\n", s);
}
