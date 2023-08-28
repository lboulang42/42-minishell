/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:48:27 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/28 21:37:10 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int argc, char **argv, char **env)
{
	t_all	*all;
	char *stat;
	int status;
	
	(void)argv;
	if (argc != 1)
		return (1);//EXIT)FAILURE
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, & ctrlc);
	all = init_data();
	init_env(all, env);
	run_easyshell(all);
	stat = get_key(all->env, "?");
	
	status = ft_atoi(stat);
	if (stat)
		free(stat);
	free_t_env(&all->env);
	return (status); // return last status code
}

void index_redir(t_all *all, char *input)
{
	

	char **lines_split;
	char **tokens;
	int count_redir = 0;
	lines_split = ft_split(input , '|');
	if (!lines_split)
		return ;

	int i = -1;
	int index_tokens;
	int redir_type;
	

	while (lines_split[++i])
	{
		index_tokens = -1;
		tokens = ft_split(lines_split[i], ' ');
		if (!tokens)
			continue;
		while (tokens[++index_tokens +1])
		{
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
		index_tokens = -1;
		tokens = ft_split(lines_split[i], ' ');
		if (!tokens)
			continue;
		while (tokens[++index_tokens +1])
		{
			redir_type = isredir(tokens[index_tokens]);
			if (redir_type)
			{
				all->redir_list[all->nbr_redir].type = redir_type;
				all->redir_list[all->nbr_redir].file = ft_strdup(tokens[index_tokens + 1]);
				count_redir++;
			}
		}
		ft_free_tab((void **)tokens);
	}
	ft_free_tab((void **)lines_split);
}

void free_redir_list(t_all *all)
{
	int i;

	i = -1;
	while (++i < all->nbr_redir)
	{
		if (all->redir_list[i].file)
			free(all->redir_list[i].file);
	}
	free(all->redir_list);
}


void	run_easyshell(t_all *all)
{
	char	*input;

	while (1)
	{
		input = readline("easy-shell> ");
		// signal(SIGINT, & ctrlc);
		if (!input)
			break ;
		if (!*input)
		{
			free(input);
			continue ;
		}
		add_history(input);
		inverse_string(input, SQUOTE);
		inverse_string(input, DQUOTE);
		input = add_spaces_input(input);
		if (syntax_error(all, input) == 1)
		{
			free(input);
			do_export(all, "?", "1");
			continue ;
		}
		inverse_string(input, DQUOTE);
		index_redir(all, input);
		
		// parse(all, input);
		//open les here_doc;
		input = expand_string(input, all->env);
		inverse_string(input, DQUOTE);
		input = delete_quote(input);
		inverse_string(input, DQUOTE);
		exec_init(all, input);
	}
}
