/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 15:18:13 by aoukhart          #+#    #+#             */
/*   Updated: 2021/11/24 22:51:50 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*malloced;

	i = 0;
	if (!s)
		return (NULL);
	malloced = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!malloced)
		return (NULL);
	while (s[i])
	{
		malloced[i] = f(i, s[i]);
		i++;
	}
	malloced[i] = '\0';
	return (malloced);
}
// char upper(unsigned int i, char s)
// {
//     if (s >= 'a' && s <= 'z')
//     {
//         s -= 32;
//     }
//     return (s);
// }
// int main()
// {   
//     int i;
//     char *str = "abcd";
//     printf("%s\n", ft_strmapi(str, upper));
// }