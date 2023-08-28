/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:44:56 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/28 21:38:55 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_outfile_trunc(t_all *all, int index_name)
{
	int	fd;
	char *value;
	char *name;
	
	if (all->redir_list[all->index_redir_tamere].file[0] == '$')
	{
		name = extract_key_name(all->redir_list[all->index_redir_tamere].file, 1);
		value = get_value_by_key(all->env, name);
	}
	else
		value = ft_strdup(all->redir_list[all->index_redir_tamere].file);
	if (!value)
		return (-2);
	fd = open(value, O_RDWR | O_CREAT | O_TRUNC, 0666);
	free(value);
	return (fd);
}

int	handle_outfile_append(t_all *all, int index_name)
{
	int	fd;
char *value;
	char *name;
	
	if (all->redir_list[all->index_redir_tamere].file[0] == '$')
	{
		name = extract_key_name(all->redir_list[all->index_redir_tamere].file, 1);
		value = get_value_by_key(all->env, name);
	}
	else
		value = ft_strdup(all->redir_list[all->index_redir_tamere].file);
	if (!value)
		return (-2);
	fd = open(value,  O_RDWR | O_CREAT | O_APPEND, 0666);
	free(value);
	return (fd);
}

int	handle_infile(t_all *all, int index_name)
{
	int	fd;
	char *value;
	char *name;
	
	if (all->redir_list[all->index_redir_tamere].file[0] == '$')
	{
		name = extract_key_name(all->redir_list[all->index_redir_tamere].file, 1);
		value = get_value_by_key(all->env, name);
	}
	else
		value = ft_strdup(all->redir_list[all->index_redir_tamere].file);
	fprintf(stderr, "value to open as infile = %s\n", value);
	if (!value)
		return (-2);
	fd = open(value, O_RDONLY);
	free(value);
	return (fd);
}
