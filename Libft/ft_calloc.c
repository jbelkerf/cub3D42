/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:58:43 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/07/07 11:23:21 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * the ft_calloc take number of memberes and the size of each member then it 
 * allocate the total memory neeeded using malloc then it send the memory to
 * the bzero func to set it to 0
 */
void	*ft_calloc(int nmemb, int size)
{
	void	*p;
	int	t;

	t = nmemb * size;
	if (!t)
		return (malloc(0));
	if (size != (t / nmemb))
		return (NULL);
	p = (void *)malloc(nmemb * size);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, nmemb * size);
	return (p);
}
