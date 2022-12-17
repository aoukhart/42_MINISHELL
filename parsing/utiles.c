/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:35:17 by ybachaki          #+#    #+#             */
/*   Updated: 2022/12/16 23:33:00 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../INCLUDE/minishell.h"

char	*ft_strjoin1(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	i = -1;
	if (!s1)
		s1 = ft_calloc(1, 1);
	if (!s1 || !s2)
		return (s1);
	res = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
	if (!res)
		return (NULL);
	while (*(s1 + ++i))
		*(res + i) = *(s1 + i);
	j = i;
	i = 0;
	while (*(s2 + i))
		*(res + j++) = *(s2 + i++);
	free((void *)s1);
	free(s2);
	return (res);
}

void	close_files(t_input *input)
{
	int	n;
	int	i;

	n = pipes_len(input);
	i = 0;
	while (i < n)
	{
		unlink(ft_strjoin("minishell_", ft_itoa(i)));
		i++;
	}
}
