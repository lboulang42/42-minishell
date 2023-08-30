/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 13:29:20 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/30 18:52:03 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*insert_expansion(char *str, char *key_name, char *key_value,
		int index_variable)
{
	char	*new_str;
	int		i;
	int		len_variable;
	int		index_value;

	i = -1;
	len_variable = ft_strlen(key_name) + 1;
	if (!key_value)
	{
		new_str = malloc(sizeof(char) * (ft_strlen(str) - len_variable + 1));
		if (new_str)
		{
			while (++i < index_variable)
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
	new_str = malloc(sizeof(char) * (ft_strlen(str) - len_variable
				+ ft_strlen(key_value) + 1));
	if (new_str)
	{
		while (++i < index_variable)
			new_str[i] = str[i];
		index_value = -1;
		while (key_value[++index_value])
			new_str[i + index_value] = key_value[index_value];
		while (str[i + len_variable])
		{
			new_str[i + index_value] = str[i + len_variable];
			i++;
		}
		new_str[i + index_value] = '\0';
	}
	free(str);
	return (new_str);
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
	while (str[start + name_len] && (ft_isalpha(str[start + name_len])
			|| ft_isdigit(str[start + name_len]) || str[start + name_len] == '_'
			|| str[start + name_len] == '?'))
		name_len++;
	key_name = ft_substr(str, start, name_len);
	return (key_name);
}

char	*get_value_by_key(t_env *full_env, char *key)
{
	t_env	*tmp;

	tmp = full_env;
	if (!key)
		return (NULL);
	while (tmp)
	{
		if (is_same_string(tmp->name, key))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

char	*toneg(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		str[i++] *= -1;
	return (str);
}

char	*expand_string(char *str, t_env *env)
{
	char	*key_value;
	char	*key_name;
	int		i;

	i = -1;
	if (!str)
		return (NULL);
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ' && str[i
				+ 1] != '"')
		{
			if (ft_isdigit(str[i + 1]))
			{
				key_name = ft_strdup(" ");
				key_value = ft_strdup("");
			}
			else
			{
				key_name = extract_key_name(str, i + 1);
				key_value = get_value_by_key(env, key_name);
			}
			str = insert_expansion(str, key_name, toneg(key_value), i);
			i += ft_strlen(key_value) - 1;
			if (key_name)
				free(key_name);
			if (key_value)
				free(key_value);
		}
	}
	return (str);
}
