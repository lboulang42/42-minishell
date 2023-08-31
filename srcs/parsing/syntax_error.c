/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:56:49 by gcozigon          #+#    #+#             */
/*   Updated: 2023/08/31 16:05:58 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_alone_quote(char *str)
{
	int		i;
	char	c;

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
				return (1);
		}
	}
	return (0);
}

int	check_rafters(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i
					+ 1] == '>'))
		{
			if (valid_rafters(str, i + 2))
				return (1);
		}
		else if ((str[i] == '<' || str[i] == '>'))
		{
			if (valid_rafters(str, i + 1))
				return (1);
		}
	}
	i = ft_strlen(str);
	while (str[--i] == ' ' && str[i])
		if (str[i - 1] == '|')
			return (1);
	return (0);
}

int	syntax_error(char *input)
{
	if (!check_empty(input))
	{
		return (1);
	}
	if (check_alone_quote(input))
	{
		ft_printf("%s : %s : %s\n", MINI, ERR_SYNTX, ERR_CLQUOTES);
		return (1);
	}
	if (check_pipes(input))
	{
		ft_printf("%s : %s `|'\n", MINI, ERR_SYNTX);
		return (1);
	}
	if (check_rafters(input))
	{
		ft_printf("%s : %s `newline'\n", MINI, ERR_SYNTX);
		return (1);
	}
	return (0);
}
