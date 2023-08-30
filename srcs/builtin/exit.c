/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:25:53 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/30 17:40:27 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned long long	do_atoi(const char *str, int neg, const char *str_safe)
{
	unsigned long long	res;
	int					count;
	t_all				*all;

	res = 0;
	all = init_data();
	count = 0;
	while (ft_isdigit(*str))
	{
		res = (res * 10) + (*str - '0');
		str++;
		count++;
	}
	if (count > 19)
	{
		ft_printf("%s : exit: %s: %s", MINI, str_safe, ERR_NARGS);
		ft_exit_free(all, 2);
		exit(2);
	}
	if (neg == -1)
	{
		if (res -1 > LLONG_MAX)
		{
			ft_printf("%s : exit: %s: %s", MINI, str_safe, ERR_NARGS);
			ft_exit_free(all, 2);
		}
	}
	else
	{
		if (res > LLONG_MAX)
		{
			ft_printf("%s : exit: %s: %s", MINI, str_safe, ERR_NARGS);
			ft_exit_free(all, 2);
		}
	}
	return (res);
}

unsigned long long	ft_atoilonglong(const char *str, const char *str_safe)
{
	long long	res;
	int			neg;

	neg = 1;
	while (iswhitespace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg *= -1;
		str++;
	}
	res = (long long)do_atoi(str, neg, str_safe);
	res *= neg;
	return (res);
}



/*
sans argument exit renvoie l'exit code de la derniere commande;
too many argument n'exit pas le process
 //ajouter l'exit code par défaut comme fait exit();
*/

void	ft_exit_free(t_all *all, int exit_code)
{
	if (ft_tab_len(all->all_lines) == 1)
	{
		safeclose (all ->default_out);
		safeclose(all->link_fd[0]);
		safeclose(all->link_fd[1]);
	}
	free_t_env(&all->env);
	ft_free_tab((void **)all->tokens);
	ft_free_tab((void **)all->all_lines);
	ft_free_tab_size((void **)all->arg, all->args_size +1);
	free_redir_list(all);
	exit(exit_code);
}


void	ft_exit(t_all *all)
{
	long long int	exit_code;
	int				i;
	char			*tmp;

	i = 0;
	if (ft_tab_len(all->tokens) == 1)
	{
		printf("exit\n");
		tmp = get_key(all->env, "?");
		exit_code = ft_atoi(tmp);
		free(tmp);
		ft_exit_free(all, exit_code);
	}
	if (ft_tab_len(all->tokens) > 2)
	{
		printf("exit\n");
		ft_printf("%s: exit: %s\n", MINI, ERR_TOOMARGS);
		ft_exit_free(all, 1);
	}
	if (all->tokens[1][i] == '-' || all->tokens[1][i] == '+')
		i++;
	while (ft_isdigit(all->tokens[1][i]))
		i++;
	if (all->tokens[1][i] != '\0')
	{
		ft_printf("%s: exit: %s: %s", MINI, all->tokens[1], ERR_NARGS);
		ft_exit_free(all, 2);
	}
	exit_code = ft_atoilonglong(all->tokens[1], all->tokens[1]);
	ft_exit_free(all, (unsigned char)exit_code);
}
