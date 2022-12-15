/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 15:57:40 by aoukhart          #+#    #+#             */
/*   Updated: 2021/11/25 03:54:02 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	if (s == NULL)
		return (NULL);
	i = 0;
	if (start > ft_strlen(s))
	{
		sub = malloc(sizeof(char));
		sub[0] = 0;
		return (sub);
	}
	if (len <= ft_strlen(s))
		sub = malloc((len + 1) * sizeof(char));
	if (len > ft_strlen(s))
	{
		sub = malloc((ft_strlen(s) + 1) * sizeof(char));
		len = ft_strlen(s);
	}
	if (!sub)
		return (NULL);
	while (s[i] && len--)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}
