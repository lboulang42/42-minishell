/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 13:29:20 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/31 16:11:33 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expansion_no_val(char *str, int index_var, char *name)
{
	char	*new_str;
	int		len_variable;
	int		i;

	i = -1;
	len_variable = ft_strlen(name) + 1;
	new_str = malloc(sizeof(char) * (ft_strlen(str) - len_variable + 1));
	if (new_str)
	{
		while (++i < index_var)
			new_str[i] = str[i];
		while (str[i + len_variable])
		{
			new_str[i] = str[i + len_variable];
			i++;
		}
		new_str[i] = '\0';
	}
	free(str);
	return (new_str);
}

/*
malloc all len +2 (name_len  = ft_strlen(name)  + 1)
*/
char	*insert_expansion(char *str, char *name, char *value, int index_var)
{
	char	*new_str;
	int		i;
	int		index_value;

	i = -1;
	if (!value)
		return (expansion_no_val(str, index_var, name));
	new_str = malloc(sizeof(char) * (ft_strlen(str) - ft_strlen(name)
				+ ft_strlen(value) + 2));
	if (new_str)
	{
		while (++i < index_var)
			new_str[i] = str[i];
		index_value = -1;
		while (value[++index_value])
			new_str[i + index_value] = value[index_value];
		while (str[i + ft_strlen(name) + 1])
		{
			new_str[i + index_value] = str[i + ft_strlen(name) + 1];
			i++;
		}
		new_str[i + index_value] = '\0';
	}
	return (free(str), new_str);
}

char	*extract_key_name(char *str, int start)
{
	int		name_len;
	char	*key_name;

	name_len = 0;
	if (str[start + name_len] && str[start + name_len] == '?')
	{
		key_name = ft_substr(str, start, 1);
		return (key_name);
	}
	while (str[start + name_len] && valid_name(str[start + name_len]))
		name_len++;
	key_name = ft_substr(str, start, name_len);
	return (key_name);
}

void	free_name_val(char *name, char *value)
{
	if (name)
		free(name);
	if (value)
		free(value);
}

char	*expand_string(char *s, t_env *env)
{
	int		i;
	char	*key_value;
	char	*key_name;

	i = -1;
	while (s && s[++i])
	{
		if (s[i] == '$' && s[i + 1] && s[i + 1] != ' ' && s[i + 1] != '"')
		{
			if (ft_isdigit(s[i + 1]))
			{
				key_name = ft_strdup(" ");
				key_value = ft_strdup("");
			}
			else
			{
				key_name = extract_key_name(s, i + 1);
				key_value = get_value_by_key(env, key_name);
			}
			s = insert_expansion(s, key_name, toneg(key_value), i);
			i += ft_strlen(key_value) - 1;
			free_name_val(key_name, key_value);
		}
	}
	return (s);
}
