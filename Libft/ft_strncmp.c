/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:05:49 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/07/07 11:23:21 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * the strncmp compare n byte of two strings s1 and s2 if all the n byte equal
 * then we return 0
 * if there's a defrence we return that defrence 
 *
 * ### hard cases if n == 0 we return 0
 */
int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int			i;
	unsigned char	c1;
	unsigned char	c2;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		c1 = s1[i];
		c2 = s2[i];
		if (c1 != c2)
			return (c1 - c2);
		i++;
	}
	c1 = s1[i];
	c2 = s2[i];
	if (i < n)
		return (c1 - c2);
	return (0);
}
