/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:05:29 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/07/07 11:23:21 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * this func cherche for the last ocu of the char c in the string s
 * it go through the string archive each ocu in  r and if we reach the end we 
 * return the last archive ocu
 * ### hard cases
 * 1- if the char we look for is the null '\0' the we return the null terminator
 * of s
 */
char	*ft_strrchr(const char *s, int c)
{
	int	i;

	if ((unsigned char)c == 0)
		return ((char *)(s + ft_strlen(s)));
	if (*s == 0)
		return (NULL);
	i = ft_strlen(s);
	while (i > 0)
	{
		if ((unsigned char)s[i - 1] == (unsigned char)c)
		{
			return ((char *)(s + i - 1));
		}
		i--;
	}
	return (NULL);
}
