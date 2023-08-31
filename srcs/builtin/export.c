/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:25:53 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/31 16:06:58 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_export(t_all *all, char *key, char *value)
{
	t_env	*tmp;

	if (!key || !*key)
		return ;
	tmp = all->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, key))
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	add_t_env(&all->env, key, value, 1);
	return ;
}

int	parse_export(char *token)
{
	int	i;

	i = -1;
	while (token[++i])
	{
		if (i == 0)
		{
			if (!ft_isalpha(token[i]) && token[i] != '_')
				return (0);
		}
		if (token[i] == '=')
			return (1);
		if (!ft_isalnum(token[i]) && token[i] != '_')
			return (0);
	}
	return (1);
}

int	check_export(t_all *all, int i)
{
	char	*name;
	char	*value;

	if (!parse_export(all->tokens[i]))
	{
		ft_printf("%s: export: '%s': %s\n", MINI, all->tokens[i], ERR_NVALID);
		return (1);
	}
	if (!ft_strchr(all->tokens[i], '='))
		return (0);
	name = get_env_name(all->tokens[i]);
	if (!name)
		return (1);
	value = get_env_value(all->tokens[i], name);
	if (!value)
		return (free(name), 1);
	do_export(all, name, value);
	return (free(name), free(value), 0);
}

int	export(t_all *all)
{
	int		status;
	int		i;

	status = 0;
	i = -1;
	if (!all->tokens[1])
		return (ft_printf("%s: %s: %s\n", MINI, "export", ERR_NVALID));
	while (all->tokens[++i])
		status = check_export(all, i);
	return (status);
}
