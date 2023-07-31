/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 22:34:12 by gcozigon          #+#    #+#             */
/*   Updated: 2023/07/30 20:13:20 by gcozigon         ###   ########.fr       */
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
	while (str[++i])
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

int	syntax_error(t_all *all, char *input)
{
	if (check_alone_quote(input))
		ft_printf("Minishell : close quote\n");
		return (1);
	if (check_pipes(input))
		ft_printf("Minishell : syntax error near unexpected token `|'\n");
		return (1);
	if (check_rafters(input))
		ft_printf("Minishell : syntax error near unexpected token `newline'\n");
		return (1);
	return (0);
}

