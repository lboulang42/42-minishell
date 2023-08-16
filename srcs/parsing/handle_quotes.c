/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 13:28:34 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/13 13:28:57 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* flag = squote ; dquote ; squote +dquote */
void	inverse_string(char *str, int flag)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == DQUOTE)
			while (str[++i] && str[i] != DQUOTE)
				if (flag == DQUOTE || flag == DQUOTE+SQUOTE)
					str[i] *= -1;
		if (str[i] == SQUOTE)
			while (str[++i] && str[i] != SQUOTE)
				if (flag == SQUOTE || flag == SQUOTE+DQUOTE)
					str[i] *= -1;
	}
}
