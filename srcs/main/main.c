/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:48:27 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/25 18:43:03 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_all *init_data(void)
{
	static t_all data = {0};
	
	return (&data);
}

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
	init_shell(all, env);
	run_easyshell(all, env);
	stat = get_key(all->env, "?");
	// fprintf(stderr, "stat = %s\n", stat);
	
	status = ft_atoi(stat);
	if (stat)
		free(stat);
	free_t_env(&all->env);
	// fprintf(stderr, "last status return : %d\n", status);
	return (status); // return last status code
}

void	run_easyshell(t_all *all, char **env)
{
	char	*input;

	while (1)
	{
		// print_t_env(all->env);
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
		// print_t_env(all->env);
	}
}
