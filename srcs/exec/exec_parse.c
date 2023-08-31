/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 02:09:39 by gcozigon          #+#    #+#             */
/*   Updated: 2023/08/31 16:08:03 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isredir(char *str)
{
	if (!ft_strcmp(str, ">"))
		return (1);
	if (!ft_strcmp(str, ">>"))
		return (2);
	if (!ft_strcmp(str, "<"))
		return (3);
	if (!ft_strcmp(str, "<<"))
		return (4);
	return (0);
}

int	mallocparse(t_all *all, char **tab)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	all->args_size = 0;
	while (tab[i])
	{
		if (isredir(tab[i]))
		{
			k++;
			if (!tab[++i])
				continue ;
		}
		else
			all->args_size++;
		i++;
	}
	all->arg = ft_calloc(sizeof(char *), all->args_size + 1);
	return (1);
}

int	parse(t_all *all, char **tab)
{
	int	i;
	int	t;

	i = 0;
	t = 0;
	mallocparse(all, tab);
	while (tab[i])
	{
		if (isredir(tab[i]))
		{
			if (tab[i + 1])
				i++;
			i++;
		}
		else
		{
			all->arg[t++] = ft_strdup(tab[i]);
			i++;
		}
	}
	all->cmd = all->arg[0];
	inverse_all(all->cmd, 0);
	if (!all->cmd && all->nbr_redir == 0)
		ft_printf("%s: :%s\n", MINI, ERR_CMD);
	return (1);
}
