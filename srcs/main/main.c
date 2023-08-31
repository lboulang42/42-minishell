/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:48:27 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/31 16:06:03 by lboulang         ###   ########.fr       */
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

void	get_input_ready(t_all *all)
{
	init_redirlist(all, all->input);
	open_heredoc(all);
	inverse_string(all->input, DQUOTE);
	all->input = expand_string(all->input, all->env);
	inverse_string(all->input, DQUOTE);
	all->input = delete_quote(all->input);
	inverse_string(all->input, DQUOTE);
}

void	run_easyshell(t_all *all)
{
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
		inverse_string(all->input, SQUOTE + DQUOTE);
		all->input = add_spaces_input(all->input);
		if (syntax_error(all->input) == 1)
		{
			free(all->input);
			do_export(all, "?", "1");
			continue ;
		}
		get_input_ready(all);
		start_exec(all);
	}
}
