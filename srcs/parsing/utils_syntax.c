/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:46:02 by gcozigon          #+#    #+#             */
/*   Updated: 2023/08/31 16:16:59 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_status(t_all *all)
{
	char	*tmp;
	int		status;

	tmp = get_key(all->env, "?");
	status = ft_atoi(tmp);
	return (free(tmp), status);
}

int	append_char_and_spaces(char *tmp, char c, int j)
{
	tmp[j++] = ' ';
	tmp[j++] = c;
	tmp[j++] = ' ';
	return (j);
}

int	append_double_char_and_spaces(char *tmp, char c1, char c2, int j)
{
	tmp[j++] = ' ';
	tmp[j++] = c1;
	tmp[j++] = c2;
	tmp[j++] = ' ';
	return (j);
}

char	*add_spaces_input(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * ((ft_strlen(str)) + ((count_meta(str)) * 2)
				+ 1));
	while (str[i])
	{
		if (str[i] == '\t' || str[i] == '\n' || str[i] == '\r')
			str[i] = ' ';
		if (is_meta(str[i]) == 1 && is_meta(str[i + 1]) == 1)
		{
			j = append_double_char_and_spaces(new_str, str[i], str[i + 1], j);
			i += 2;
		}
		else if (is_meta(str[i]) == 1)
			j = append_char_and_spaces(new_str, str[i++], j);
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (free(str), new_str);
}
