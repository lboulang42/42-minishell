/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:46:23 by gcozigon          #+#    #+#             */
/*   Updated: 2023/07/28 15:28:05 by gcozigon         ###   ########.fr       */
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

int	append_char_and_spaces(char *tmp, char c, int j)
{
	tmp[j++] = ' ';
	tmp[j++] = c;
	tmp[j++] = ' ';
	return (j);
}

int	append_double_char_and_spaces(char *tmp, char c1, char c2, int j)
{
	tmp[j++] = ' ';
	tmp[j++] = c1;
	tmp[j++] = c2;
	tmp[j++] = ' ';
	return (j);
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
