/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 22:20:11 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/31 17:18:16 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_redirlist(char **lines_split)
{
	int		count_redir;
	int		index_tokens;
	char	**tokens;
	int		i;

	i = -1;
	count_redir = 0;
	while (lines_split[++i])
	{
		index_tokens = -1;
		tokens = ft_split(lines_split[i], ' ');
		if (!tokens)
			continue ;
		while (tokens[++index_tokens + 1])
		{
			tokens[index_tokens] = delete_quote(tokens[index_tokens]);
			inverse_all(tokens[index_tokens], 0);
			if (isredir(tokens[index_tokens]))
				count_redir++;
		}
		ft_free_tab((void **)tokens);
	}
	return (count_redir);
}

void	assign(t_all *all, int redir_type, int index_tokens, char **tokens)
{
	all->redir_list[all->nbr_redir].type = redir_type;
	all->redir_list[all->nbr_redir].file = ft_strdup(tokens[index_tokens + 1]);
	all->nbr_redir++;
}

void	fill_redirlist(t_all *all, char **lines_split, int index_tokens,
		int redir_type)
{
	char	**tokens;
	int		idn;
	int		i;

	i = -1;
	while (lines_split[++i])
	{
		index_tokens = -1;
		tokens = ft_split(lines_split[i], ' ');
		if (!tokens)
			continue ;
		idn = -1;
		while (tokens[++idn])
		{
			tokens[idn] = delete_quote(tokens[idn]);
			inverse_all(tokens[idn], 0);
		}
		while (tokens[++index_tokens + 1])
		{
			redir_type = isredir(tokens[index_tokens]);
			if (redir_type && tokens[index_tokens + 1])
				assign(all, redir_type, index_tokens, tokens);
		}
		ft_free_tab((void **)tokens);
	}
}

void	init_redirlist(t_all *all, char *input)
{
	char	**lines_split;
	int		count_redir;
	int		i;
	int		index_tokens;
	int		redir_type;

	index_tokens = 0;
	redir_type = 0;
	lines_split = ft_split(input, '|');
	if (!lines_split)
		return ;
	count_redir = size_redirlist(lines_split);
	all->redir_list = calloc((count_redir + 1), sizeof(t_redir));
	all->nbr_redir = 0;
	i = -1;
	fill_redirlist(all, lines_split, index_tokens, redir_type);
	ft_free_tab((void **)lines_split);
}

void	free_redir_list(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->nbr_redir)
	{
		free(all->redir_list[i].file);
		if (all->redir_list[i].type == 4)
			safeclose(all->redir_list[i].here_doc_fd);
	}
	free(all->redir_list);
}
