/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:34:41 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/09/06 11:34:43 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

void	*free_p(char **p);
char	*get_next_line(int fd);
char	*ft_strjoin1(char *s1, char *s2);
int		ft_strlen1(const char *str);
char	*ft_strdup1(const char *s);
char	*ft_substr1(char *s, int start, int len);

#endif
