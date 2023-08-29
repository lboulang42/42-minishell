/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:44:56 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/29 19:32:49 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	handle_outfile_trunc(t_all *all, int index_name)
{
	int	fd;
	char *value;
	char *name;
	char *tmp;
	name = NULL;

	// fprintf(stderr, "file in redir_list :%s\n", all->redir_list[all->index_redir_tamere].file);
	tmp = ft_strdup(all->redir_list[all->index_redir_tamere + all->redir_before].file);
	// fprintf(stderr, "file after delquotes :%s\n", tmp);
	if (tmp[0] == '$')
	{
		// fprintf(stderr, "file start with $\n");
		name = extract_key_name(tmp, 1);
		// fprintf(stderr, "file name after extract_name :%s\n", name);
		value = get_value_by_key(all->env, name);
		// fprintf(stderr, "value after get_value by key :%s\n", value);
	}
	else
	{
		// fprintf(stderr, "file don't start with $\n");
		value = ft_strdup(tmp);
		// fprintf(stderr, "value after dup :%s\n", value);
	}
	// fprintf(stderr, "value to open :%s\n", value);
	if (!value)
		return (fprintf(stderr, "%s : %s : %s\n", MINI, tmp, ERR_AMBIGUS), free(tmp), free(name), -2);
	fd = open(value, O_RDWR | O_CREAT | O_TRUNC, 0666);
	free(tmp);
	free(name);
	free(value);
	return (fd);
}

int	handle_outfile_append(t_all *all, int index_name)
{
	int	fd;
	char *value;
	char *name;
	char *tmp;
	name = NULL;

	// fprintf(stderr, "file in redir_list :%s\n", all->redir_list[all->index_redir_tamere].file);
	tmp = ft_strdup(all->redir_list[all->index_redir_tamere + all->redir_before].file);
	// fprintf(stderr, "file after delquotes :%s\n", tmp);
	if (tmp[0] == '$')
	{
		// fprintf(stderr, "file start with $\n");
		name = extract_key_name(tmp, 1);
		// fprintf(stderr, "file name after extract_name :%s\n", name);
		value = get_value_by_key(all->env, name);
		// fprintf(stderr, "value after get_value by key :%s\n", value);
	}
	else
	{
		// fprintf(stderr, "file don't start with $\n");
		value = ft_strdup(tmp);
		// fprintf(stderr, "value after dup :%s\n", value);
	}
	// fprintf(stderr, "value to open :%s\n", value);
	if (!value)
		return (fprintf(stderr, "%s : %s : %s\n", MINI, tmp, ERR_AMBIGUS), free(tmp), free(name), -2);
	fd = open(value,  O_RDWR | O_CREAT | O_APPEND, 0666);
	free(tmp);
	free(name);
	free(value);
	return (fd);
}

int	handle_infile(t_all *all, int index_name)
{
	int	fd;
	char *value;
	char *name;
	char *tmp;
	name = NULL;

	// fprintf(stderr, "file in redir_list :%s\n", all->redir_list[all->index_redir_tamere].file);
	tmp = ft_strdup(all->redir_list[all->index_redir_tamere + all->redir_before].file);
	// fprintf(stderr, "file after delquotes :%s\n", tmp);
	if (tmp[0] == '$')
	{
		// fprintf(stderr, "file start with $\n");
		name = extract_key_name(tmp, 1);
		// fprintf(stderr, "file name after extract_name :%s\n", name);
		value = get_value_by_key(all->env, name);
		// fprintf(stderr, "value after get_value by key :%s\n", value);
	}
	else
	{
		// fprintf(stderr, "file don't start with $\n");
		value = ft_strdup(tmp);
		// fprintf(stderr, "value after dup :%s\n", value);
	}
	// fprintf(stderr, "value to open :%s\n", value);
	if (!value)
		return (fprintf(stderr, "%s : %s : %s\n", MINI, tmp, ERR_AMBIGUS), free(tmp), free(name), -2);
	fd = open(value, O_RDONLY);
	free(tmp);
	if (name)
		free(name);
	free(value);
	return (fd);
}
