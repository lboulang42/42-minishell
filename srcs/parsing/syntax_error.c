/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:56:49 by gcozigon          #+#    #+#             */
/*   Updated: 2023/08/28 11:01:48 by lboulang         ###   ########.fr       */
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

int	check_pipes(char *str)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i] && str[i] == ' ')
		if (str[i + 1] == '|')
			return (1);
	while (str[i++])
	{
		if (str[i] == '|')
		{
			if (str[i + 1] == '|' || str[i + 1] == '\0')
				return (1);
			j = i;
			while (str[--j] && str[j] == ' ')
				if (str[j - 1] == '<' || str[j - 1] == '>')
					return (1);
			while (str[++i] && str[i] == ' ')
				if (str[i + 1] == '|')
					return (1);
		}
	}
	i = strlen(str);
	while (str[--i] == ' ' && str[i])
		if (str[i - 1] == '|')
			return (1);
	return (0);
}

int valid_rafters(char *str, int len)
{

	while (str[len] && str[len] == ' ')
		len++;
 	if (str[len] == '<' || str[len] == '>' || str[len] == '\0')
		return (1);
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
	i = strlen(str);
	while (str[--i] == ' ' && str[i])
		if (str[i - 1] == '|')
			return (1);
	return (0);
}

int check_empty(char *str)
{
	int i = -1;
	int res = 0;//is empty

	while (str[++i])
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\v')
			return (1);
	return (0);
}

int	syntax_error(t_all *all, char *input)
{
	if (!check_empty(input))
	{
		return (1);
	}
	if (check_alone_quote(input))
	{
		fprintf(stderr, "%s : %s : %s\n", MINI, ERR_SYNTX, ERR_CLQUOTES);
		return (1);
	}
	if (check_pipes(input))
	{
		fprintf(stderr, "%s : %s `|'\n", MINI, ERR_SYNTX);
		return (1);
	}
	if (check_rafters(input))
	{
		fprintf(stderr, "%s : %s `newline'\n", MINI, ERR_SYNTX);
		return (1);
	}
	return (0);
}

