/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:47:23 by gcozigon          #+#    #+#             */
/*   Updated: 2023/08/30 18:38:01 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (input[i] == SQUOTE || input[i] == DQUOTE)
			res++;
	}
	return (res);
}

int	valid_rafters(char *str, int len)
{
	while (str[len] && str[len] == ' ')
		len++;
	if (str[len] == '<' || str[len] == '>' || str[len] == '\0')
		return (1);
	return (0);
}

int	check_empty(char *str)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (str[++i])
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\v')
			return (1);
	return (0);
}

int	is_same_string(char *str1, char *str2)
{
	if (ft_strlen(str1) != ft_strlen(str2))
		return (0);
	if (ft_strncmp(str1, str2, ft_strlen(str2)))
		return (0);
	return (1);
}
