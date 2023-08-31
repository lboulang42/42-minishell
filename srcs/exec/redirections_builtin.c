/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_builtin.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:17:06 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/31 16:05:38 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_fd(t_all *all, char **tokens, int i)
{
	int	fd;

	if (is_this_meta(tokens[i], "<"))
		fd = handle_infile(all);
	if (is_this_meta(tokens[i], "<<"))
		fd = handle_heredocbooste(all);
	if (is_this_meta(tokens[i], ">"))
		fd = handle_outfile_trunc(all);
	if (is_this_meta(tokens[i], ">>"))
		fd = handle_outfile_append(all);
	return (fd);
}

/*Printf on error output the error message and return the error code to be
handled correctly*/
int	invalid_fd(t_all *all, int fd, char **tokens, int i)
{
	if (fd == -1)
	{
		if (errno == 13)
			ft_printf("%s: %s: %s\n", MINI, tokens[i + 1], ERR_PERM);
		else
			ft_printf("%s :%s: %s\n", MINI, tokens[i + 1], ERR_NOSUCHF);
		return (all->index_redir++, -3);
	}
	return (all->index_redir++, -2);
}

int	get_outfile_infile_builtin2(t_all *all, char **tokens)
{
	int	i;
	int	fd;

	i = -1;
	fd = -1;
	while (tokens[++i])
	{
		if (isredir(tokens[i]))
		{
			fd = open_fd(all, tokens, i);
			if (fd == -1 || fd == -2)
				return (invalid_fd(all, fd, tokens, i));
			if (is_this_meta(tokens[i], ">") || is_this_meta(tokens[i], ">>"))
				dup2(fd, 1);
			if (all->prev_fd > 0)
				safeclose(all->prev_fd);
			safeclose(fd);
			tokens[i][0] = '\0';
			tokens[i + 1][0] = '\0';
			all->index_redir++;
		}
	}
	return (fd);
}
