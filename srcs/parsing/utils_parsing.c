/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:00:03 by gcozigon          #+#    #+#             */
/*   Updated: 2023/08/29 16:03:22 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*copy;
	unsigned char	*copy2;

	copy = (unsigned char *)s1;
	copy2 = (unsigned char *)s2;
	while (*copy || *copy2)
	{
		if (*copy != *copy2)
			return (*copy - *copy2);
		copy++;
		copy2++;
	}
	return (0);
}

/*
Return 1 si c est un whitespace; Sinon 0
*/
int	iswhitespace(const char c)
{
	return (c == ' ' || c == '\t' || c == '\v' \
	|| c == '\n' || c == '\r' || c == '\f');
}

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
	if (!input[0])
		return (res);
	while (input[++i])
	{
		if (input[i] == SQUOTE || input[i] == DQUOTE )
			res++;
	}
	return (res);
}
