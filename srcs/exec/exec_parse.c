/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 02:09:39 by gcozigon          #+#    #+#             */
/*   Updated: 2023/08/29 19:43:20 by lboulang         ###   ########.fr       */
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
	all->args_size = 0;
	while (tab[i])
	{
		if (isredir(tab[i])) // > file
		{
			k++;
			if (!tab[++i])
				continue;
		}
		else // le reste
			all->args_size++;
		i++;
	}
	
	// all->arg = ft_calloc(sizeof(char *), t + 1);
	all->arg = ft_calloc(sizeof(char *), all->args_size +1);
	return (1);
}

/*ca vire ca ?*/
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

//grep hi <./test_files/infile_big <./test_files/infile
int	parse(t_all *all, char **tab)//pq c'etait un void *
{
	int	i;
	int k;//changer le name
	int	t;//changer le name
	
	i = 0;
	k = 0;
	t = 0;
	mallocparse(all, tab);
	while (tab[i])
	{
		if (isredir(tab[i]) && tab[i +1])
			i++;
		else
		{
			// fprintf(stderr, "add dans parse : %s\n", tab[i]);
			all->arg[t++] = ft_strdup(tab[i]);
		}
		i++;
	}
	all->cmd = all->arg[0];
	return (1);
}
