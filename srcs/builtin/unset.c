/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:25:53 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/27 18:27:19 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	do_unset(t_all *all, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = all->env;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, key))
		{
			if (prev)
				prev->next = tmp->next;
			else
				all->env = tmp->next;
			if (tmp->name)
				free(tmp->name);
			if (tmp->value)
				free(tmp->value);
			tmp->name = NULL;
			tmp->value = NULL;
			tmp->display = 0;
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	unset(t_all *all, char **tokens)
{
	int	i;

	i = 0;
	if (!tokens[1])
		return (0);
	while (tokens[++i])
	{
		if (!is_same_string(tokens[i], "?"))
			do_unset(all, tokens[i]);
	}
	return (0);
}