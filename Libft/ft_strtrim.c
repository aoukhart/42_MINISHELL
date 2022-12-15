/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 12:04:35 by aoukhart          #+#    #+#             */
/*   Updated: 2021/11/25 03:52:30 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*malloced;
	int		i;
	int		j;

	i = 0;
	if (!s1 || !set)
		return (0);
	j = ft_strlen(s1);
	if (*set == '\0')
		return (ft_strdup(s1));
	while (s1[i] && ft_strchr(set, s1[i]) != 0)
		i++;
	while (j > i && ft_strchr(set, s1[j]) != 0)
		j--;
	malloced = malloc((j - i + 1) + 1 * sizeof(char));
	if (malloced == NULL)
		return (NULL);
	malloced = (char *)ft_memcpy(malloced, (const char *)(s1 + i), (j - i + 1));
	malloced[j - i + 1] = '\0';
	return (malloced);
}

// int main()
// {
//     printf("%s", ft_strtrim("  123 4 56   ", " "));
//     return 0;
// }