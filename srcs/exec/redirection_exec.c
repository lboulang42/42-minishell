/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:21:28 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/31 12:54:05 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_redir(char **tokens)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (tokens[++i])
	{
		if (isredir(tokens[i]))
			res++;
	}
	return (res);
}

void	free_redir(t_all *all)
{
	free_t_env(&all->env);
	ft_free_tab((void **)all->all_lines);
	ft_free_tab((void **)all->tokens);
	free_redir_list(all);
	ft_free_tab_size((void **)all->arg, all->args_size + 1);
}

void	exit_fd(t_all *all, char **tokens, int i, int fd)
{
	if (fd == -1)
		ft_printf("%s: %s: %s\n", MINI, tokens[i + 1], strerror(errno));
	free_redir(all);
	all->index_redir++;
	exit(1);
}

void	get_outfile_infile(t_all *all, char **tokens)
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
				exit_fd(all, tokens, i, fd);
			if (is_this_meta(tokens[i], "<") || is_this_meta(tokens[i], "<<"))
				dup2(fd, 0);
			else
				dup2(fd, 1);
			safeclose(fd);
			tokens[i][0] = '\0';
			if (tokens[i + 1])
				tokens[i + 1][0] = '\0';
			all->index_redir++;
		}
	}
}
