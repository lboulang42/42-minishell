/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:48:27 by lboulang          #+#    #+#             */
/*   Updated: 2023/07/18 17:25:56 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	static t_all	all;

	(void)argv;
	if (argc != 1)
		return (0);
	init_shell(&all, env);
	run_easyshell(&all, env);
	return (0);
}

void	init_shell(t_all *all, char **env)
{
	// add sinal later;
}

void	run_easyshell(t_all *all, char **env)
{
	char	*input;

	all->env = env;
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
		syntax_error(all, input);
		init_token(all, input);
		add_history(input);
		// token_recognition(all, input);
		all->tab = ft_split(input, '|');
		all->nbcmd = counter(input, '|');
		pipex(all, all->tab);
		close_pipes(all);
		free_resources(all);
		free(input);
	}
}

// void	token_recognition(t_all *all, char *input)
// {
// 	int i;

// 	i = 0;
// 	while (1)
// 	{
// 		/* code */
// 	}
	
// }

void	save_str_quote(t_all *all, char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == DQUOTE)
		{
			while (input[++i] != DQUOTE && input[i])
				input[i] = input[i] * -1;
		}
		if (input[i] == SQUOTE)
		{
			while (input[++i] != SQUOTE && input[i])
				input[i] = input[i] * -1;
		}
	}
}

void	init_token(t_all *all, char *input)
{
	int	i;

	i = 0;
	save_str_quote(all, input);

}
// quote open ferme , error,
// syntqx error error,
// change quote garder la string,
// double quote garder la string et expension pour $,
// tokenistation atribution de types pour chqaue case du tableau,
// ajouter des types pour les files en fonction des chevrons
// ajouter les rules par mots et regarder si l'input est correcte
// cree les differentes cmd grace au pipe et envoyer a leo.

// files
// pipe
// double pipe >> APPEND ; << delimiteur heredoc
// word
// chevron
// quote
// double quote -> expend
// flag
