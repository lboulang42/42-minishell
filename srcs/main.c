/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:48:27 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/01 18:11:58 by lboulang         ###   ########.fr       */
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

/*
return 1 if char is in charset
*/
int char_in_charset(char c, char *charset)
{
	int i;

	i = -1;
	while (charset[++i])
		if (charset[i] == c)
			return (1);
	return (0);
}

/*
return number of char in str specified in charset;
*/
int count_charset_in_str(char *str, char *charset)
{
	int i;
	int count;
	
	i = -1;
	count = 0;
	while (str[++i])
		count += char_in_charset(str[i], charset);
	return (count);
}

char	*add_spaces_input(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = malloc((ft_strlen(str)) + ((count_meta(str)) * 2) + 1);
	while (str[i])
	{
		if (is_meta(str[i]) == 1 && is_meta(str[i + 1]) == 1)
		{
			j = append_double_char_and_spaces(new_str, str[i], str[i + 1], j);
			i += 2;
		}
		else if (is_meta(str[i]) == 1)
		{
			j = append_char_and_spaces(new_str, str[i], j);
			i++;
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (free(str), new_str);
}

/* flag = squote ; dquote ; squote +dquote */
void	inverse_string(char *str, int flag)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == DQUOTE)
			while (str[++i] && str[i] != DQUOTE)
				if (flag == DQUOTE || flag == DQUOTE+SQUOTE)
					str[i] *= -1;
		if (str[i] == SQUOTE)
			while (str[++i] && str[i] != SQUOTE)
				if (flag == SQUOTE || flag == SQUOTE+DQUOTE)
					str[i] *= -1;
	}
}

char *extract_key_name(char *str, int start)
{
	int name_len = 0;
	char *res;
	if (ft_isalpha(str[start]))
	{
		while (str[start+name_len] && ft_isalpha(str[start+name_len]))
			name_len++;
		// printf("name_len = %d\n", name_len);
		res = ft_substr(str, start, name_len);
		// printf("res = %s\n", res);
		return (res);
	}
	if (ft_isdigit(str[start]))
	{
		while (str[start+name_len] && ft_isdigit(str[start+name_len]))
			name_len++;
		// printf("name_len = %d\n", name_len);
		res = ft_substr(str, start, name_len);
		// printf("res = %s\n", res);
		return (res);
	}
	// if (str[start] == '?')
	// 	return (ft_strdup("?\0"));
	return (NULL);
}

char *insert_expansion(char *str, char *key_name, char *key_value, int index_variable)
{
	int i;
	int index_value;
	int len_variable;
	char *new_str;
	
	i = -1;
	len_variable =  ft_strlen(key_name) + 1;
	if (!key_value)
	{
		new_str = malloc(sizeof(char) * (ft_strlen(str) - len_variable+1));
		while (++i < index_variable)
			new_str[i] = str[i];
		while (str[i+len_variable])
		{
			new_str[i] = str[i+len_variable];
			i++;
		}
		new_str[i] = '\0';
		return (free(str), new_str);
	}


	//$PATH|$USER|hello|$sah|$PWD|oui
	
	new_str = malloc(sizeof(char *) * (ft_strlen(str) - len_variable + ft_strlen(key_value) + 1));
	while (++i < index_variable)
		new_str[i] = str[i];
	index_value = -1;
	while (key_value[++index_value])
		new_str[i + index_value] = key_value[index_value];
	while (str[i + len_variable])
	{
		new_str[i+index_value] = str[i + len_variable];
		i++;
	}
	
	return (free(str), new_str);
	return (str);
}

char *expand_string(char *str, t_env *env)
{
	int i;
	char *key_value;
	char *key_name;
	
	i = -1;

	while (str[++i])
	{
		if (str[i] == '$'  && str[i+1])
		{
			key_name = extract_key_name(str, i+1);
			key_value = get_value_by_key(env, key_name);
			// printf("KEYNAME = %s\n", key_name);
			// printf("KEYVALUE = %s\n", key_value	);
			
			str = insert_expansion(str, key_name, key_value, i);
			
			i += ft_strlen(key_value)-1;
			if (key_name)
				free(key_name);
			if (key_value)
				free(key_value);
		}
	}
	return (str);
}


void	run_easyshell(t_all *all, char **env)
{
	char	*input;

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
		// printf("base input = %s\n", input);
		
		inverse_string(input, SQUOTE);
		// printf("inversed input = %s\n", input);


		input = add_spaces_input(input);//gab function
		// printf("space added input= %s\n", input);
		input = expand_string(input, all->env);
		printf("expanded string = %s\n", input);

		free(input);
		// inverse_string(input, SQUOTE);
		// printf("re-inversed input3 = %s\n", input);

		//remet only les sngle
		//inverse all here
	}
}


/*
GAB CODE





in run esay_shell
{
	
		//delete quote here
		
		// save_str_quote(input, 3);*
		// tmp = add_spaces_input(input);
		// if (syntax_error(all, tmp) == 1)
		// {
		// 	// des bqils a free IMO
		// 	printf("continue !");
		// 	continue ;
		// }
		// printf("input =#%s#\n", input);
		// printf("tmp =#%s#\n", tmp);
xx

		// printf("save str = %s\n\n", tmp);
		// expand_input(tmp, all, env);
		// tmp = delete_quote(tmp);
		// printf("delete quote = %s\n\n", tmp);
		// token_recognition(all, tmp);
		// all->tab = ft_split(tmp, '|');
		// all->nbcmd = counter(tmp, '|');
		// pipex(all, all->tab);
		// close_pipes(all);
		// free_resources(all);
		// ft_free_split(all->tab);

		// free(tmp);

		
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
}

*/


