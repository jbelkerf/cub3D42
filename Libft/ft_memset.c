/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:09:31 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/09/05 14:36:18 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * this func take a pointer to an memory and set every byte of it to the 
 * unsigned c 
 */
void	*ft_memset(void *s, int c, int n)
{
	int				i;
	char			*p;
	unsigned char	x;

	x = (unsigned char)c;
	p = (char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = x;
		i++;
	}
	return (s);
}
