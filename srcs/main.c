/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:48:27 by lboulang          #+#    #+#             */
/*   Updated: 2023/07/31 00:50:02 by gcozigon         ###   ########.fr       */
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

char	*add_spaces_input(char *input)
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
	return (free(input), tmp);
}

char	*delete_quote(char *input)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = malloc(ft_strlen(input) - count_quote(input) + 1);
	if (!tmp)
		return (NULL);
	while (input[i])
	{
		if (input[i] != SQUOTE && input[i] != DQUOTE)
			tmp[j++] = input[i];
		i++;
	}
	tmp[j] = '\0';
	free(input);
	return (tmp);
}

void	ft_free_split(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

int	count_expand(char *str)
{
	int	i;
	int res;

	i = -1;
	res = 0;
	while (str[++i])
	{
		if (str[i] == '"')
			while (str[i] && str[++i] != '"')
			{
				if (str[i] == '$')
					res++;
			}
	}
	return (res);
}

char	*keep_key(char *str)
{
	int	i;

	i = -1;
	char *key;
	// malloc(sizeof(char *) count_exp)
	int l;
	save_str_quote(str);
	l =  count_expand(str);
	
	ft_printf("NB DOLLARDS = %d", l); 
	return (key);
}

void	expand_input(char *input, t_data *data, char **env)
{
	init_env(data, env);
	print_t_env(data->env);
	keep_key(input);
	free_t_env(&data->env);
	// get_value_by_key(t_env *full_env, char *key)
}

void	run_easyshell(t_all *all, char **env)
{
	char	*input;
	char	*tmp;
	t_data	data;

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
		add_history(input);
		save_str_quote(input);
		tmp = add_spaces_input(input);
		printf("add_spaces str = %s\n\n", tmp);
		syntax_error(all, tmp);
		printf("save str = %s\n\n", tmp);
		expand_input(tmp, &data, env);
		tmp = delete_quote(tmp);
		printf("delete quote = %s\n\n", tmp);
		// token_recognition(all, tmp);
		all->tab = ft_split(tmp, '|');
		all->nbcmd = counter(tmp, '|');
		pipex(all, all->tab);
		close_pipes(all);
		free_resources(all);
		ft_free_split(all->tab);
		free(tmp);
	}
}

void	save_str_quote(char *input)
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
