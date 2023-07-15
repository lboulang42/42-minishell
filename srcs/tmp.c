/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 22:34:12 by gcozigon          #+#    #+#             */
/*   Updated: 2023/07/15 22:41:10 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	check_alone_quote(t_all *all, char *str)
{
	int	i;
	char c;
	i = -1;
	while (str[++i])
	{
		if (str[i] == SQUOTE || str[i] == DQUOTE)
		{
			c = str[i];
			i++;
			while (str[i] != c && str[i])
				i++;
			if (str[i] != c)
			{
				ft_printf("Minishell : Error close quote.\n");
				exit (1);
			}
		}
	}
	return(1);
}
