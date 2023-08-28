/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:25:53 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/28 11:20:06 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **tokens)
{
	int	start_echo;
	int	is_n;
	int	i;

	is_n = 0;
	i = 1;
	while (tokens[i] && is_same_string(tokens[i], "-n"))
	{
		is_n += 1;
		i++;
	}
	start_echo = i;
	while (tokens[i])
	{
		if (i == start_echo)
			printf("%s", tokens[i]);
		else
			printf(" %s", tokens[i]);
		i++;
	}
	if (is_n == 0)
		printf("\n");
	return (EXIT_SUCCESS);
}
