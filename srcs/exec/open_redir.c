/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:44:56 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/31 16:04:54 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_outfile_trunc(t_all *all)
{
	int		fd;
	char	*value;
	char	*name;
	char	*tmp;

	name = NULL;
	tmp = ft_strdup(all->redir_list[all->index_redir + all->redir_before].file);
	if (tmp[0] == '$')
	{
		name = extract_key_name(tmp, 1);
		value = get_value_by_key(all->env, name);
	}
	else
		value = ft_strdup(tmp);
	if (!value)
		return (ft_printf("%s : %s : %s\n", MINI, tmp, ERR_AMBIGUS), free(tmp),
			free(name), -2);
	fd = open(value, O_RDWR | O_CREAT | O_TRUNC, 0666);
	free(tmp);
	free(name);
	free(value);
	return (fd);
}

int	handle_outfile_append(t_all *all)
{
	int		fd;
	char	*value;
	char	*name;
	char	*tmp;

	name = NULL;
	tmp = ft_strdup(all->redir_list[all->index_redir + all->redir_before].file);
	if (tmp[0] == '$')
	{
		name = extract_key_name(tmp, 1);
		value = get_value_by_key(all->env, name);
	}
	else
	{
		value = ft_strdup(tmp);
	}
	if (!value)
		return (ft_printf("%s : %s : %s\n", MINI, tmp, ERR_AMBIGUS), free(tmp),
			free(name), -2);
	fd = open(value, O_RDWR | O_CREAT | O_APPEND, 0666);
	free(tmp);
	free(name);
	free(value);
	return (fd);
}

int	handle_infile(t_all *all)
{
	int		fd;
	char	*value;
	char	*name;
	char	*tmp;

	name = NULL;
	tmp = ft_strdup(all->redir_list[all->index_redir + all->redir_before].file);
	if (tmp[0] == '$')
	{
		name = extract_key_name(tmp, 1);
		value = get_value_by_key(all->env, name);
	}
	else
		value = ft_strdup(tmp);
	if (!value)
		return (ft_printf("%s : %s : %s\n", MINI, tmp, ERR_AMBIGUS), free(tmp),
			free(name), -2);
	fd = open(value, O_RDONLY);
	free(tmp);
	if (name)
		free(name);
	free(value);
	return (fd);
}
