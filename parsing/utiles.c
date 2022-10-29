/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:35:17 by ybachaki          #+#    #+#             */
/*   Updated: 2022/10/26 21:32:05 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"../INCLUDE/minishell.h"

char	*ft_strjoin2(char *s1, char *s2)
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
	return (res);
}

static int	leftcheck(char const *s, char const *set)
{
	int	i;

	i = 0;
	while (*(s + i) && ft_strchr(set, *(s + i)))
		i++;
	return (i);
}

static int	rightcheck(char const *s, char const *set)
{
	int	len;
	int	i;

	len = ft_strlen(s) - 1;
	i = 0;
	while (len >= 0 && ft_strchr(set, *(s + len)))
	{
		len--;
		i++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*res;

	res = NULL;
	if (!s1 || !set)
		return (0);
	len = ft_strlen(s1);
	if (*set == '\0')
		return (ft_strdup(s1));
	if (len - (rightcheck(s1, set) + leftcheck(s1, set)) <= 0)
		return (ft_strdup(""));
	len -= rightcheck(s1, set) + leftcheck(s1, set);
	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1 + leftcheck(s1, set), len + 1);
	return (res);
}
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*(s + i))
	{
		if (*(s + i) == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (*(s + i) == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

char	*ft_strdup3(const char *s1, int len)
{
	int		i;
	char	*res;

	i = 0;
	res = calloc(len + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	while (i < len)
	{
		*(res + i) = *(s1 + i);
		i++;
	}
	return (res);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	len = ft_strlen(s1);
	res = ft_calloc(len + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	while (*(s1 + i))
	{
		*(res + i) = *(s1 + i);
		i++;
	}
	return (res);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(dst);
	if (dstsize > 0)
	{
		while (*(dst + i))
			i++;
		while (i < dstsize - 1 && *(src + j))
		{
			*(dst + i) = *(src + j);
			i++;
			j++;
		}
		*(dst + i) = '\0';
	}
	if (dstsize >= len)
		return (ft_strlen(src) + len);
	return (dstsize + ft_strlen(src));
}
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (i < dstsize - 1 && *(src + i))
		{
			*(dst + i) = *(src + i);
			i++;
		}
		*(dst + i) = '\0';
	}
	return (ft_strlen (src));
}
void	*ft_calloc(size_t count, size_t size)
{
	void	*res;

	res = malloc(count * size);
	if (res == NULL)
		return (NULL);
	ft_bzero(res, count * size);
	return (res);
}
size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*(s + i))
		i++;
	return (i);
}
void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)(s + i) = 0;
		i++;
	}
}
