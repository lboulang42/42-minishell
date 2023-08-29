/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:25:53 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/29 21:12:36 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_export(t_all *all)
{
	t_env	*tmp;

	tmp = all->env;
	if (!tmp)
		return (EXIT_SUCCESS);
	while (tmp)
	{
		if (tmp->display == 1)
			printf("export %s=\"%s\"\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

void	do_export(t_all *all, char *key, char *value)
{
	t_env	*tmp;
	t_env	*tmp_before;
	char	*temp_val;

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

int	export(t_all *all)
{
	char	*name;
	char	*value;
	int		status;
	int		i;

	status = 0;
	i = -1;
	if (!all->tokens[1])
		return (fprintf(stderr, "%s: %s: %s\n", MINI, "export", ERR_NVALID));
	while (all->tokens[++i])
	{
		if (!parse_export(all->tokens[i]))
		{
			fprintf(stderr, "%s: export: '%s': %s", MINI, all->tokens[i], ERR_NVALID);
			status = 1;
			continue ;
		}
		if (!ft_strchr(all->tokens[i], '='))
			continue ;
		name = get_env_name(all->tokens[i]);
		if (!name)
		{
			status = 1;
			continue ;
		}
		value = get_env_value(all->tokens[i], name);
		if (!value)
		{
			free(name);
			status = 1;
			continue ;
		}
		do_export(all, name, value);
		free(name);
		free(value);
	}
	return (status);
}
