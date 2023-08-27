/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:44:56 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/27 17:45:23 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_outfile_trunc(t_all *all, int index_name)
{
	int	fd;

	fd = open(all->tokens[index_name], O_RDWR | O_CREAT | O_TRUNC, 0666);
	return (fd);
}

int	handle_outfile_append(t_all *all, int index_name)
{
	int	fd;

	fd = open(all->tokens[index_name], O_RDWR | O_CREAT | O_APPEND, 0666);
	return (fd);
}

int	handle_infile(t_all *all, int index_name)
{
	int	fd;

	fd = open(all->tokens[index_name], O_RDONLY);
	return (fd);
}
