/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:58:48 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/07/07 11:24:18 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*free_p(char **p)
{
	if (*p != NULL)
	{
		free(*p);
		*p = NULL;
	}
	return (NULL);
}

int	ft_strlen1(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strdup1(const char *s)
{
	char	*re;
	int		i;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	re = (char *)malloc((i + 1) * sizeof(char));
	if (re == NULL)
		return (NULL);
	while (s[i])
	{
		re[i] = s[i];
		i++;
	}
	re[i] = 0;
	return (re);
}

char	*ft_substr1(char *s, int start, int len)
{
	int	len_s;
	int	i;
	char			*sub;

	i = 0;
	if (s == NULL)
		return (NULL);
	len_s = ft_strlen1(s);
	if (len_s < start)
		return (ft_strdup1(""));
	if (len_s - start < len)
		len = len_s - start;
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = 0;
	return (sub);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	char	*re;
	int		i;
	int		j;

	j = -1;
	i = -1;
	if (s1 == NULL)
		s1 = ft_strdup1("");
	if (s1 == NULL)
		return (NULL);
	re = (char *)malloc((ft_strlen1(s1) + ft_strlen1(s2) + 1) * sizeof(char));
	if (re == NULL)
		return (free(s1), NULL);
	while (s1[++j])
		re[j] = s1[j];
	while (s2[++i])
		re[j + i] = s2[i];
	return (re[j + i] = 0, free(s1), s1 = NULL, re);
}
