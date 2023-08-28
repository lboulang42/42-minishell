/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:48:27 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/28 12:21:19 by lboulang         ###   ########.fr       */
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
		input = expand_string(input, all->env);
		inverse_string(input, DQUOTE);
		input = delete_quote(input);
		inverse_string(input, DQUOTE);
		exec_init(all, input);
	}
}
