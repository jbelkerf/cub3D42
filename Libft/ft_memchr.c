/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:08:59 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/09/05 14:35:56 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * the memchr func look up the n byte of  memory pointed by s for the first
 * match with the int c then it return a pinter to that match in s
 */
void	*ft_memchr(const void *s, int c, int n)
{
	unsigned char	*p;
	int				i;

	i = 0;
	p = (unsigned char *)s;
	while (i < n)
	{
		if (*p == (unsigned char)c)
			return ((void *)p);
		p++;
		i++;
	}
	return (0);
}
