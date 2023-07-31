/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:48:27 by lboulang          #+#    #+#             */
/*   Updated: 2023/07/31 17:41:32 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	static t_all	all;

	(void)argv;
	if (argc != 1)
		return (0);
	init_env(&all, env);
	init_shell(&all, env);
	run_easyshell(&all, env);
	free_t_env(&all.env);
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
	int	res;

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
	int		i;
	char	*key;
	int		l;

	i = -1;
	// malloc(sizeof(char *) count_exp)
	save_str_quote(str, 1);
	l = count_expand(str);
	// ft_printf("NB DOLLARDS = %d", l);
	return (key);
}

int ismeta(char c)
{
	if (c == ' ')
		return 1;
	if (c == 39)
		return 1;
	if (c == '"')
		return 1;
	if (c == '\t')
		return 1;
	return 0;
}

char *expndstring(char *source, int start, int stop, char *to_add)
{
	char *new_str;
	int i = 0;
	int j = 0;
	printf("src = %s\n", source);
	new_str = malloc(sizeof(char ) * (ft_strlen(source) + ft_strlen(to_add) - (stop-start)));
	while (i != start)
	{
		new_str[i] = source[i];
		i++;
	}
	while (to_add[j])
	{
		new_str[i+j] = to_add[j];
		j++;
	}
	i += stop;
	while (source[i])
	{
		new_str[i+j] = source[i];
		i++;
	}
	// free(source);
	printf("newstr = *%s*\n", new_str);
	return (new_str);
}

void	expand_input(char *input, t_all *data, char **env)
{
	int		i;
	char	*dollar_value;
	int		j;
	char	*value;

	// print_t_env(data->env);
	keep_key(input);
	printf("inp = %s\n", input);
	i = -1;
	while (input[++i])
	{
		if (input[i] == '$')
		{
			j = 0;
			while (input[i + j] && !ismeta(input[i+j]))
				j++;
			if (ismeta(input[i+j]))
				j--;
			dollar_value = ft_substr(input, i + 1, j);
			value = get_value_by_key(data->env, dollar_value);
			//si pas de value
			// printf("detected $\nKey = %s\nVAlue = %s\n", dollar_value, value);
			input = expndstring(input, i, j, value);
			printf("new input = %s\n", input);
			// i = 0;
			printf("newinput = %s\n", input);
		}
		
	}
	//
}

void	run_easyshell(t_all *all, char **env)
{
	char	*input;
	char	*tmp;

	// t_data	data;
	// all->env = env;
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
		save_str_quote(input, 3);
		tmp = add_spaces_input(input);
		// printf("add_spaces str = %s\n\n", tmp);
		if (syntax_error(all, tmp) == 1)
		{
			// des bqils a free IMO
			printf("continue !");
			continue ;
		}
		// printf("save str = %s\n\n", tmp);
		expand_input(tmp, all, env);
		tmp = delete_quote(tmp);
		// printf("delete quote = %s\n\n", tmp);
		// token_recognition(all, tmp);
		// all->tab = ft_split(tmp, '|');
		// all->nbcmd = counter(tmp, '|');
		// pipex(all, all->tab);
		// close_pipes(all);
		// free_resources(all);
		// ft_free_split(all->tab);
		free(tmp);
	}
}

void	save_str_quote(char *input, int flag)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (flag == 1 || flag == 3)
		{
			if (input[i] == DQUOTE)
			{
				while (input[++i] != DQUOTE && input[i])
					input[i] = input[i] * -1;
			}
		}
		if (flag == 2 || flag == 3)
		{
			if (input[i] == SQUOTE)
			{
				while (input[++i] != SQUOTE && input[i])
					input[i] = input[i] * -1;
			}
		}
	}
}
