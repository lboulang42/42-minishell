/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:25:53 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/21 18:18:55 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int print_export(t_all *all)
{
	t_env *tmp;

	tmp = all->env;
	if (!tmp)
		return (EXIT_SUCCESS);
	/*
	remet l'env dans l'ordre alpha des name avant;
	
	*/
	while (tmp)
	{
		printf("export %s=\"%s\"\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

void do_export(t_all *all, char *key, char *value)
{
	t_env *tmp;
	t_env  *tmp_before;
	char *temp_val;
	
	tmp = all->env;
	
	while (tmp)
	{
		if (is_same_string(tmp->name, key))
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	add_t_env(&all->env, key, value);
}

int indexof(char *str, char c)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}

int is_already_in_env(t_env *env, char *name)
{
	t_env *tmp;
	tmp = env;
	while (tmp)
	{
		if (is_same_string(tmp->name, name))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

/*
si export call
	- deja in, edit;
	- pas in, add;
si export pas call
	- deja in, edit;
*/

int parse_name(char *name)
{
	int i;
	i = -1;
	while (name[++i])
	{
		if (i == 0 && (name[i] == '=' || ft_isdigit(name[i])))
			return (0);
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
	}
	return (1);
}

void    export(t_all *all, char **tokens, int parse_flag)//must be cleaned
{
	int i;
	int index_egal;
	char *name;
	char *value;
	
	i = 0;
	if (!tokens[1])
		return ((void)print_export(all));
	while (tokens[++i])
	{
		if (ft_strchr(tokens[i], '=') && tokens[i][0] != '=')
		{
			name = get_env_name(tokens[i]);
			value = get_env_value(tokens[i], name);
			if (!parse_flag)
				do_export(all, name, value);
			else
			{
				if (parse_name(name))
					do_export(all, name, value);
				else
					printf("minishell: export: '%s': not a valid identifier\n", tokens[i]);
			}
			if (name)
				free(name);
			if (value)
				free(value);
		}
		else if (!parse_name(tokens[i]))
			printf("minishell: export: '%s': not a valid identifier\n", tokens[i]);
	}
}