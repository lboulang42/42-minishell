/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:25:53 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/24 13:52:22 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(const char c)
{
	return (c == ' ' || c == '\t' || c == '\v'
		|| c == '\n' || c == '\r' || c == '\f');
}

long long	ft_atoilonglong(const char *str)
{
	int			neg;
	long long	res;

	res = 0;
	neg = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg *= -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		res = (res * 10) + (*str - '0');
		str++;
	}
	return (res * neg);
}

void    ft_exit_free(t_all *all, char **tokens, char **all_lines)
{
    if (ft_tab_len(all_lines) == 1)
    {
        close(all->link_fd[0]);
        close(all->link_fd[1]);
    }
    free_t_env(&all->env);
	ft_free_tab((void **)tokens);
	ft_free_tab((void **)all_lines);
}

/*
sans argument exit renvoie l'exit code de la derniere commande;
too many argument n'exit pas le process
*/
void ft_exit(t_all *all, char **tokens, char **all_lines)
{
    int i;
    long long int   exit_code;
    char *tmp;
    i = 0;
    if (ft_tab_len(tokens) == 1)//ajouter l'exit code par défaut comme fait exit(); besoin des PID;
    {
        printf("exit\n");
        ft_exit_free(all, tokens, all_lines);
        exit(0);//last exitcode here
    }
    while (tokens[++i])
	{
		tmp = tokens[i];
		exit_code = ft_atoilonglong(tmp);
		if (*tmp == '+' || *tmp == '-')
			tmp ++;
		while (ft_isdigit(*tmp))
			tmp++;
		if (i > 1)
		{
			printf("exit\n");
			fprintf(stderr, "Minishell: exit: too many arguments\n");
            ft_exit_free(all, tokens, all_lines);
            exit(1);
		}
		if (*tmp != '\0' || exit_code > LLONG_MAX || exit_code < LLONG_MIN)
        {
            fprintf(stderr, "minishell: exit: %s: numeric argument required\n", tmp);
            ft_exit_free(all, tokens, all_lines);
            exit(2);
        }
	}
    exit_code = 1;
    if (tokens[1])
        exit_code = ft_atoilonglong(tokens[1]) % 256;
    ft_exit_free(all, tokens, all_lines);
    exit(exit_code);
}