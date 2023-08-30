/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:48:27 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/30 18:51:27 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_all	*all;
	char	*stat;
	int		status;

	(void)argv;
	if (argc != 1)
		return (1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrlc);
	all = init_data();
	init_env(all, env);
	run_easyshell(all);
	stat = get_key(all->env, "?");
	status = ft_atoi(stat);
	free(stat);
	free_t_env(&all->env);
	return (status);
}

void	index_redir(t_all *all, char *input)
{
	char	**lines_split;
	char	**tokens;
	int		count_redir;
	int		i;
	int		index_tokens;
	int		redir_type;
	int		idn;

	count_redir = 0;
	lines_split = ft_split(input, '|');
	if (!lines_split)
		return ;
	i = -1;
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
			redir_type = isredir(tokens[index_tokens]);
			if (redir_type)
				count_redir++;
		}
		ft_free_tab((void **)tokens);
	}
	all->redir_list = calloc((count_redir + 1), sizeof(t_redir));
	all->nbr_redir = 0;
	i = -1;
	while (lines_split[++i])
	{
		index_tokens = 0;
		tokens = ft_split(lines_split[i], ' ');
		if (!tokens)
			continue ;
		idn = -1;
		while (tokens[++idn])
		{
			tokens[idn] = delete_quote(tokens[idn]);
			inverse_all(tokens[idn], 0);
		}
		while (tokens[index_tokens + 1])
		{
			redir_type = isredir(tokens[index_tokens]);
			if (redir_type && tokens[index_tokens + 1])
			{
				all->redir_list[all->nbr_redir].type = redir_type;
				all->redir_list[all->nbr_redir].file = ft_strdup(tokens[index_tokens
						+ 1]);
				all->nbr_redir++;
			}
			index_tokens++;
		}
		ft_free_tab((void **)tokens);
	}
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

void	run_easyshell(t_all *all)
{
	char	*input;

	while (1)
	{
		all->input = readline("easy-shell> ");
		if (!all->input)
			break ;
		if (!*all->input)
		{
			free(all->input);
			continue ;
		}
		add_history(all->input);
		inverse_string(all->input, SQUOTE);
		inverse_string(all->input, DQUOTE);
		all->input = add_spaces_input(all->input);
		if (syntax_error(all, all->input) == 1)
		{
			free(all->input);
			do_export(all, "?", "1");
			continue ;
		}
		index_redir(all, all->input);
		open_heredoc(all, all->input);
		inverse_string(all->input, DQUOTE);
		all->input = expand_string(all->input, all->env);
		inverse_string(all->input, DQUOTE);
		all->input = delete_quote(all->input);
		inverse_string(all->input, DQUOTE);
		all->index_redir_tamere = 0;
		exec_init(all);
	}
}
