/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:48:27 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/17 18:25:44 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_all	all;

	(void)argv;
	if (argc != 1)
		return (0);
	init_env(&all, env);
	init_shell(&all, env);
	run_easyshell(&all, env);
	free_t_env(&all.env);
	return (0); // return last status code
}

void	run_easyshell(t_all *all, char **env)
{
	char	*input;

	while (1)
	{
		input = readline("easy-shell> ");
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
			// des bqils a free IMO
			printf("continue !\n");
			continue ;
		}
		inverse_string(input, DQUOTE);
		input = expand_string(input, all->env);
		inverse_string(input, DQUOTE);
		input = delete_quote(input);
		inverse_string(input, DQUOTE);
		exec_init(all, input);
		free(input);
	}
}
