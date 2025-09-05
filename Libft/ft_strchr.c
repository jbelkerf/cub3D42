/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:07:49 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/09/05 14:40:00 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * the strchr look for the first ocu of c in s and return a pointer to that ocu
 */
char	*ft_strchr(const char *s, char c)
{
	char	*p;

	p = (char *)s;
	while (*p)
	{
		if (*p == (char)c)
			return (p);
		p++;
	}
	if ((char)c == 0)
		return (p);
	else
		return (NULL);
}

char	*ft_strchr2(const char *s, char c)
{
	char	*p;

	p = (char *)s;
	while (*p)
	{
		if (*p == (char)c)
			return (p);
		p++;
	}
	return (NULL);
}
