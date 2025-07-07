/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:05:38 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/07/07 11:23:21 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * this fun search if the string lil is in the big if yes it return a pointer
 * to the first ocu of lil in big
 * #hard cases
 * 1- if lil is '\0' then we return the whole big
 * 2- if lil is nt apearing in big we return null
 */
char	*ft_strnstr(const char *big, const char *lil, int len)
{
	int	j;
	int	i;

	if (*lil == '\0')
		return ((char *)big);
	if (len == 0)
		return (NULL);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (lil[j] && (i + j < len) && big[i + j] == lil[j] && big[i + j])
			j++;
		if (lil[j] == '\0')
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
