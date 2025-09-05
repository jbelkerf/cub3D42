/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:09:06 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/09/05 14:36:03 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
 *
 */

int	ft_memcmp(const void *s1, const void *s2, int n)
{
	int					i;
	unsigned char		*p1;
	unsigned char		*p2;

	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (i < n)
	{
		if (p1[i] == p2[i])
			i++;
		else
			return (p1[i] - p2[i]);
	}
	return (0);
}
