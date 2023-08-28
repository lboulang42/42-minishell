/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:25:53 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/28 12:16:14 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



unsigned long long	do_atoi(const char *str, int neg, const char *str_safe)
{
	unsigned long long	res;
	t_all				*all;

	res = 0;
	all = init_data();
	while (ft_isdigit(*str))
	{
		res = (res * 10) + (*str - '0');
		str++;
	}
	if (neg == -1)
	{
		if (res -1 > LLONG_MAX)
		{
			fprintf(stderr, "minishell : exit: %s: numeric argument required", str_safe);
			ft_exit_free(all);
			exit(2);
		}
	}
	else
	{
		if (res > LLONG_MAX)
		{
			fprintf(stderr, "minishell : exit: %s: numeric argument required", str_safe);
			ft_exit_free(all);
			exit(2);
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

void	ft_exit_free(t_all *all)
{
	if (ft_tab_len(all->all_lines) == 1)
	{
		close (all ->default_out);
		close(all->link_fd[0]);
		close(all->link_fd[1]);
	}
	free_t_env(&all->env);
	ft_free_tab((void **)all->tokens);
	ft_free_tab((void **)all->all_lines);
}

/*
sans argument exit renvoie l'exit code de la derniere commande;
too many argument n'exit pas le process
*/
void	ft_exit(t_all *all)
{
	long long int	exit_code;
	int				i;

	i = 0;
	if (ft_tab_len(all->tokens) == 1) //ajouter l'exit code par défaut comme fait exit();
	{
		printf("exit\n");
		ft_exit_free(all);
		exit(0);
	}
	if (ft_tab_len(all->tokens) > 2)
	{
		printf("exit\n");
		fprintf(stderr, "%s: exit: %s\n", MINI, ERR_TOOMARGS);
		ft_exit_free(all);
		exit(1);
	}
	if (all->tokens[1][i] == '-' || all->tokens[1][i] == '+')
		i++;
	while (ft_isdigit(all->tokens[1][i]))
		i++;
	if (all->tokens[1][i] != '\0')
	{
		fprintf(stderr, "%s: exit: %s: %s", MINI, all->tokens[1], ERR_NARGS);
		ft_exit_free(all);
		exit(2);
	}
	exit_code = ft_atoilonglong(all->tokens[1], all->tokens[1]);
	ft_exit_free(all);
	exit((unsigned char) exit_code);
}
