/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:58:33 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/07/07 11:23:21 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 *the bzero func take a void pointer to an memeory and fail it with '\0' aka 0
 *the char pointer p created because we cant change or asigne to
 *									a void pointer nor derefrence
 */
void	ft_bzero(void *s, int n)
{
	int	i;
	char	*p;

	p = (char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
}
