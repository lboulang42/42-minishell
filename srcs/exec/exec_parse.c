/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 02:09:39 by gcozigon          #+#    #+#             */
/*   Updated: 2023/08/28 15:12:13 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//c'est quoi ce fichier de golmon
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

int	mallocparse(t_all *all, char **tab)//pq c'etait un void *
{
	int	i;
	int	k;
	int	t;
	
	i = 0;
	k = 0;
	t = 0;
	while (tab[i])
	{
		if (isredir(tab[i])) // > file
		{
			k++;
			if (!tab[++i])
				return (0);
		}
		else // le reste
			t++;
		i++;
	}
	all->arg = ft_calloc(sizeof(char *), t + 1);
	all->files = ft_calloc(sizeof(char *), k + 1);
	all->type = ft_calloc(sizeof(int), k);
	return (1);
}

void	printparse(char *cmd, char **arg, int *type, char **files)
{
	if (cmd)
		fprintf(stderr,"COMMAND = [%s]\n", cmd);
	if (arg && arg[0] && arg[1])
		fprintf(stderr,"ARGS = ");
	for (int i = 1; arg[i]; i++)
		fprintf(stderr,"[%s]", arg[i]);
	if (arg && arg[0] && arg[1])
		fprintf(stderr,"\n");
	if (files && files[0])
		fprintf(stderr,"TYPE|FILE\n");
	for (int i = 0; files[i]; i++)
		fprintf(stderr,"[%i]|{%s}\n", type[i], files[i]);
}

void	parse(t_all *all, char **tab)//pq c'etait un void *
{
	int	i;
	int k;//changer le name
	int	t;//changer le name
	
	i = 0;
	k = 0;
	t = 0;
	if (!mallocparse(all, tab))
	{
		ft_printf("ambigous redirect\n");
		ft_free_tab((void **)tab);
		ft_free_tab((void **)all->all_lines);
		free_t_env(&all->env);
		close(all->link_fd[0]);
		close(all->link_fd[1]);
		exit(1);
	}
	while (tab[i])
	{
		if (isredir(tab[i])) // > file
		{
			all->type[k] = isredir(tab[i]);
			all->files[k++] = ft_strdup(tab[++i]);
		}
		else
			all->arg[t++] = ft_strdup(tab[i]);
		i++;
	}
	all->cmd = all->arg[0];
	// printparse(all->cmd, all->arg, all->type, all->files);
}
