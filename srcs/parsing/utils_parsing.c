/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:00:03 by gcozigon          #+#    #+#             */
/*   Updated: 2023/08/31 16:11:22 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Return 0 if s1==s2 else return an integer less than, equal to, 
or greater than zero if s1 (or the first n bytes thereof) is found, 
respectively, to be less than, to match, or be greater than s2
*/
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

int	valid_name(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_' || c == '?')
		return (1);
	return (0);
}

int	iswhitespace(const char c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\n' || c == '\r'
		|| c == '\f');
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
