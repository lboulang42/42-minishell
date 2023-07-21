/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:48:27 by lboulang          #+#    #+#             */
/*   Updated: 2023/07/21 15:54:25 by gcozigon         ###   ########.fr       */
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

char	*expand_input(char *input)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = malloc((ft_strlen(input)) + ((count_meta(input)) * 2) + 1);
	while (input[i])
	{
		if (is_meta(input[i]) == 1 && is_meta(input[i + 1]) == 1)
		{
			j = append_double_char_and_spaces(tmp, input[i], input[i + 1], j);
			i += 2;
		}
		else if (is_meta(input[i]) == 1)
		{
			j = append_char_and_spaces(tmp, input[i], j);
			i++;
		}
		else
			tmp[j++] = input[i++];
	}
	tmp[j] = '\0';
	return (tmp);
}

void	run_easyshell(t_all *all, char **env)
{
	char	*input;
	char	*tmp;

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
		tmp = expand_input(input);
		printf("%s\n", tmp);
		syntax_error(all, tmp);
		init_token(all, tmp);
		add_history(tmp);
		// token_recognition(all, tmp);
		all->tab = ft_split(tmp, '|');
		all->nbcmd = counter(tmp, '|');
		pipex(all, all->tab);
		close_pipes(all);
		free_resources(all);
		free(input);
		free(tmp);
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
	save_str_quote(all, input);
}
