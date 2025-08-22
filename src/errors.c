/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:25:06 by JbelkerfIse       #+#    #+#             */
/*   Updated: 2025/08/22 19:32:16 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"


void	put_error(char *err)
{
	printf(RED "Error\n\t");
	printf(RED "%s\n" RESET, err);
	exit(1);
}
