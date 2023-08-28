/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 13:33:35 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/28 11:02:25 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
redirection builtin
return -2 si error a l'ouverture d'un file descriptor
*/
int	get_outfile_infile_builtin(t_all *all, char **tokens, char **all_lines)
{
	int	i;
	int	fd;

	i = -1;
	fd = -1;
	while (tokens[++i])
	{
		if (is_this_meta(tokens[i], "<"))
			fd = handle_infile(all, i +1);
		else if (is_this_meta(tokens[i], "<<"))
			fd = handle_heredoc(all, i +1);
		else if (is_this_meta(tokens[i], ">"))
			fd = handle_outfile_trunc(all, i +1);
		else if (is_this_meta(tokens[i], ">>"))
			fd = handle_outfile_append(all, i +1);
		if (is_this_meta(tokens[i], "<") || is_this_meta(tokens[i], "<<") || is_this_meta(tokens[i], ">") || is_this_meta(tokens[i], ">>"))
		{
			if (fd == -1)
			{
				if (errno == 13)
					fprintf(stderr, "%s: %s: %s\n", MINI, tokens[i +1], ERR_PERM);
				else
					fprintf(stderr, "%s :%s: %s\n", MINI, tokens[i +1], ERR_NOSUCHF);
				return (-2);
			}
			if (is_this_meta(tokens[i], ">") || is_this_meta(tokens[i], ">>"))
			{
				dup2(fd, 1);
			}
			if (all->prev > 0)
				close(all->prev);
			close(fd);
			tokens[i][0] = '\0';
			tokens[i + 1][0] = '\0';
		}
	}
	return (fd);
}

//redirection command
void	get_outfile_infile(t_all *all, char **tokens, char **all_lines, int index_pipe)
{
	int	i;
	int	fd;

	i = -1;
	fd = -1;
	while (tokens[++i])
	{
		if (is_this_meta(tokens[i], "<"))
			fd = handle_infile(all, i +1);
		else if (is_this_meta(tokens[i], "<<"))
			fd = handle_heredoc(all, i +1);
		else if (is_this_meta(tokens[i], ">"))
			fd = handle_outfile_trunc(all, i +1);
		else if (is_this_meta(tokens[i], ">>"))
			fd = handle_outfile_append(all, i +1);
		if (is_this_meta(tokens[i], "<") || is_this_meta(tokens[i], "<<") || is_this_meta(tokens[i], ">") || is_this_meta(tokens[i], ">>"))
		{
			if (fd == -1)
			{
				fprintf(stderr, "Minishell: %s: %s\n", tokens[i+1], strerror(errno));
				free_t_env(&all->env);
				ft_free_tab((void **)all_lines);
				ft_free_tab((void **)tokens);
				exit (1);
			}
			if (is_this_meta(tokens[i], "<") || is_this_meta(tokens[i], "<<"))
				dup2(fd, 0);
			else
				dup2(fd, 1);
			close(fd);
			tokens[i][0] = '\0';
			tokens[i + 1][0] = '\0';
		}
	}
}
