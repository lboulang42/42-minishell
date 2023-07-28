/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 22:34:12 by gcozigon          #+#    #+#             */
/*   Updated: 2023/07/28 19:48:57 by gcozigon         ###   ########.fr       */
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
int	check_invalid_combinations_full(char *input)
{
	int	i;

	i = -1;
	if (input[0] == '>' && input[1] == '>')
	{
		while (input[++i] && input[i] == '>')
		{
			if (input[i + 1] == '|' || input[i + 1] == '<')
				return (0);
		}
	}
	return (1);
}

int	check_invalid_combinations(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '>' || input[i] == '<' || input[i] == '|')
		{
			if (input[i + 1] == '>' || input[i + 1] == '<' || input[i
				+ 1] == '|')
				return (0);
		}
	}
	return (1);
}

void	checkChevronSyntax(const char *command)
{
	int		i;
	char	currentChar;
	char	nextChar;

	i = 0;
	int countInput = 0;  // Compte le nombre de redirections d'entrée
	int countOutput = 0; // Compte le nombre de redirections de sortie
	while (command[i] != '\0')
	{
		currentChar = command[i];
		nextChar = command[i + 1];
		if (currentChar == '<')
		{
			countInput++;
			if (nextChar == '<' || nextChar == '>' || nextChar == '\0'
				|| nextChar == ' ')
			{
				printf("Erreur de syntaxe : chevron d'entrée incorrect\n");
				return ;
			}
			// Gérer les cas de double chevron d'entrée
			if (nextChar == '<')
			{
				printf("Erreur de syntaxe : double chevron d'entrée non autorisé\n");
				return ;
			}
		}
		else if (currentChar == '>')
		{
			countOutput++;
			if (nextChar == '<' || nextChar == '>' || nextChar == '\0'
				|| nextChar == ' ')
			{
				printf("Erreur de syntaxe : chevron de sortie incorrect\n");
				return ;
			}
			// Gérer les cas de double chevron de sortie
			if (nextChar == '>')
			{
				printf("Erreur de syntaxe : double chevron de sortie non autorisé\n");
				return ;
			}
		}
		i++;
	}
	if (countInput > 1 || countOutput > 1)
	{
		printf("Erreur de syntaxe : trop de redirections d'entrée/sortie\n");
		return ;
	}
	printf("Syntaxe correcte\n");
}

void	syntax_error(t_all *all, char *input)
{
	if (check_alone_quote(all, input) == 0)
	{
		ft_printf("Minishell : close quote\n");
	}
	if (check_pipes(all, input) == 0)
	{
		ft_printf("Minishell : syntax error near unexpected token `|'\n");
	}
	checkChevronSyntax(input);
}
