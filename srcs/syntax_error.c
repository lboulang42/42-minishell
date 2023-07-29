/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 22:34:12 by gcozigon          #+#    #+#             */
/*   Updated: 2023/07/29 14:46:37 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_alone_quote(t_all *all, char *str)
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

int	check_pipes(t_all *all, char *input)
{
	int	i;
	int j;

	i = -1;
	while (input[++i] && input[i] == ' ')
		if (input[i + 1] == '|')
			return (1);
	while (input[++i])
	{
		if (input[i] == '|')
		{
			if (input[i + 1] == '|' || input[i + 1] == '\0')
				return (1);
			j = i;
			while (input[--j] && input[j] == ' ')
				if (input[j - 1] == '<' || input[j - 1] == '>')
					return (1);
			while (input[++i] && input[i] == ' ')
				if (input[i + 1] == '|')
					return (1);
		}
	}
	i = strlen(input);
	while (input[--i] == ' ' && input[i])
		if (input[i - 1] == '|')
			return (1);
	return (0);
}


void	syntax_error(t_all *all, char *input)
{
	if (check_alone_quote(all, input))
		ft_printf("Minishell : close quote\n");
	if (check_pipes(all, input))
		ft_printf("Minishell : syntax error near unexpected token `|'\n");
}
