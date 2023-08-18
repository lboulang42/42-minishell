/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:00:03 by gcozigon          #+#    #+#             */
/*   Updated: 2023/08/18 17:37:36 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	is_meta(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == DQUOTE || c == SQUOTE)
		return (1);
	return (0);
}

int	count_meta(char *input)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (input[++i])
	{
		if (is_meta(input[i]) == 1)
			res++;
	}
	return (res);
}

int	count_quote(char *input)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (input[++i])
	{
		if (input[i] == SQUOTE || input[i] == DQUOTE )
			res++;
	}
	return (res);
}
