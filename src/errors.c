/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:25:06 by JbelkerfIse       #+#    #+#             */
/*   Updated: 2025/07/09 13:29:07 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define ORANGE  "\033[0;33m"
#define RESET   "\033[0m"

void	put_error(char *err)
{
	printf(RED "Error\n\t");
	printf(RED "%s\n" RESET, err);
	exit(1);
}
