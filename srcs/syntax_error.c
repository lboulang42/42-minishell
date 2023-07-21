/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 22:34:12 by gcozigon          #+#    #+#             */
/*   Updated: 2023/07/21 15:46:36 by gcozigon         ###   ########.fr       */
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
			{
				ft_printf("Minishell : Error close quote.\n");
				exit(1);
			}
		}
	}
	return (1);
}

int	check_pipes(t_all *all, char *input)
{
	int	i;

	i = -1;
	while (input[++i] && input[i] == ' ')
		if (input[i + 1] == '|')
			return (0);
	while (input[++i])
	{
		if (input[i] == '|')
		{
			if (input[i + 1] == '|' || input[i + 1] == '\0')
				return (0);
			while (input[++i] && input[i] == ' ')
				if (input[i + 1] == '|')
					return (0);
		}
	}
	i = strlen(input);
	while (input[--i] == ' ' && input[i])
	{
		if (input[i - 1] == '|')
			return (0);
	}
	return (1);
}


// int	check_rafters(t_all *all, char *input)
// {

// }

void	syntax_error(t_all *all, char *input)
{
	if (check_alone_quote(all, input) == 0)
	{
		ft_printf("Minishell : close quote\n");
		exit(1);
	}
	if (check_pipes(all, input) == 0)
	{
		ft_printf("Minishell : syntax error near unexpected token `|'\n");
		exit(1);
	}
	// if (check_rafters(all, input) == 0)
	// {
	// 	ft_printf("here syntx\n\n");
	// }
}
