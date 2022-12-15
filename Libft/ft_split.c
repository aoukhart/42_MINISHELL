/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:05:30 by aoukhart          #+#    #+#             */
/*   Updated: 2021/11/25 00:59:26 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_size(char const *s, char c)
{	
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (s[i] && s[i] != c)
	{	
		y++;
		i++;
	}
	return (y);
}

static int	ft_word_count(char const *s, char c)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			y++;
			i += ft_word_size(&s[i], c);
		}
		else
			i++;
	}
	return (y);
}

static char	*ft_word_copy(char const *src, char *dest, char c)
{
	int	i;

	i = 0;
	while (src[i] != c && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	**ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		n;
	int		i;

	if (!s)
		return (NULL);
	str = ft_calloc((ft_word_count(s, c) + 1), sizeof(char *));
	if (!str)
		return (NULL);
	n = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			str[n] = malloc((ft_word_size(&s[i], c) + 1) * sizeof(char));
			if (!str)
				return (ft_free(str));
			ft_word_copy(&s[i], str[n++], c);
			i += ft_word_size(&s[i], c);
		}
		else
			i++;
	}
	return (str);
}
// int main()
// {
// 	char **stock;
// 	char *str;
// 	int  i;
// 	str = "hhhhhh  qw qw eqw eqwe ";
// 	stock = ft_split(str, 'z');
// 	while (i < ft_word_count(str, 'z'))
// 	{
// 		printf("%s\n", stock[i]);
// 		i++;
// 	}
// 	return (0);
// }