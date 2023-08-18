/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 13:33:35 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/18 19:50:27 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_infile(t_all *all, char **tokens_array, int index_name)
{
	int fd;
	
	fd = open(tokens_array[index_name], O_RDONLY);
	return (fd);
}

int handle_heredoc(t_all *all, char **tokens_array, int index_name)
{
	
	int fd[2];
	static char *buffer;
	char *line;
	pipe(fd);
	while (1)
	{
		ft_printf("Minishell here_doc >>");
		buffer = ft_get_file(buffer, 0);
		line = ft_get_line(buffer);
		buffer = ft_update_buffer(buffer);
		if (ft_is_same_line(line, tokens_array[index_name]))
			break;
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
	free(line);
	free(buffer);
	close(fd[1]);
	return (fd[0]);
}

int handle_outfile_trunc(t_all *all, char **tokens_array, int index_name)
{
	int fd;

	fd = open(tokens_array[index_name], O_RDWR | O_CREAT| O_TRUNC, 0666);

	return (fd);
}
int handle_outfile_append(t_all *all, char **tokens_array, int index_name)
{
	int fd;
	
	fd = open(tokens_array[index_name], O_RDWR | O_CREAT| O_APPEND, 0666);
	return (fd);
}

void	get_outfile_infile(t_all *all, char **tokens)
{
	int	i;

	i = -1;
	int fd = -1;
	while (tokens[++i +1])
	{
		if (is_this_meta(tokens[i], "<"))
			fd = handle_infile(all, tokens, i+1);//infile name = i+1
		else if (is_this_meta(tokens[i], "<<"))
			fd = handle_heredoc(all, tokens, i+1);//i+1 = limiter du here_doc
		else if (is_this_meta(tokens[i], ">"))
			fd = handle_outfile_trunc(all, tokens, i+1);
		else if (is_this_meta(tokens[i], ">>"))
			fd = handle_outfile_append(all, tokens, i+1);
		if (is_this_meta(tokens[i], "<") || is_this_meta(tokens[i], "<<") || is_this_meta(tokens[i], ">") || is_this_meta(tokens[i], ">>"))
		{
			if (fd == -1)
			{
				fprintf(stderr, "%s: ERRORRRRR\n", tokens[i + 1]);
				exit(1);
			}
			if ((is_this_meta(tokens[i], "<") || is_this_meta(tokens[i], "<<")))
				dup2(fd, 0);
			else
				dup2(fd, 1);
			close(fd);
			tokens[i][0] = '\0';
			tokens[i + 1][0] = '\0';
		}
	}
}
