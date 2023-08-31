/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:16:57 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/31 13:17:20 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_alone_pipes_start(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] == ' ')
		if (str[i + 1] == '|')
			return (-2);
	return (i);
}

int	check_alone_pipes_end(char *str)
{
	int	i;

	i = ft_strlen(str);
	while (str[--i] == ' ' && str[i])
		if (str[i - 1] == '|')
			return (1);
	return (0);
}

int	check_pipes(char *str)
{
	int	i;
	int	j;

	i = check_alone_pipes_start(str);
	if (i == -2)
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
	i = check_alone_pipes_end(str);
	return (i);
}
