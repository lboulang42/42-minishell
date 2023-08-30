/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 13:28:34 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/30 18:38:16 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* flag = squote ; dquote ; squote +dquote */
void	inverse_string(char *str, int flag)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == DQUOTE)
			while (str[++i] && str[i] != DQUOTE)
				if (flag == DQUOTE || flag == DQUOTE + SQUOTE)
					str[i] *= -1;
		if (str[i] == SQUOTE)
			while (str[++i] && str[i] != SQUOTE)
				if (flag == SQUOTE || flag == SQUOTE + DQUOTE)
					str[i] *= -1;
	}
}

char	*delete_quote(char *input)
{
	int		i;
	int		j;
	char	*tmp;
	int		countquote;

	i = 0;
	j = 0;
	countquote = count_quote(input);
	tmp = malloc(sizeof(char) * (ft_strlen(input) - countquote + 1));
	if (!tmp)
		return (NULL);
	while (input[i])
	{
		if (input[i] != SQUOTE && input[i] != DQUOTE)
			tmp[j++] = input[i];
		i++;
	}
	tmp[j] = '\0';
	free(input);
	return (tmp);
}
