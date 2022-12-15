/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:25:26 by aoukhart          #+#    #+#             */
/*   Updated: 2021/11/25 03:48:16 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == 0)
		return ((char *)(haystack + i));
	if (len == 0)
		return (0);
	while (haystack[i] && len > i && len > 0)
	{
		j = 0;
		while (needle[j] && needle[j] == haystack[i + j] && i + j < len)
			j++;
		if (needle[j] == '\0')
			return ((char *)(haystack + i));
		i++;
	}
	return (0);
}

// int main()
// {
//  	char s1[30] = "aaabcabcd";
// 	char s2[10] = "abc";
// 	size_t max = ft_strlen(s1);
// 	printf("%s\n", ft_strnstr(s1, s2, max));
//  	return 0;
// }