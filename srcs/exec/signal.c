/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:04:58 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/18 19:09:10 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrlc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar('\n');
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}   
}

void	ctrld(int sig)
{
	fprintf(stderr, "ctrl D sa mere");
	if (sig == SIGQUIT)
	{
		fprintf(stderr, "ctrl D sa mere");
		exit(131);
	}
}