/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:04:58 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/28 15:15:37 by lboulang         ###   ########.fr       */
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

void ctrlchere_doc(int sig)
{
	t_all *all;

	all = init_data();
	if (sig == SIGINT)
	{
		safeclose(all->here_doc_fd[1]);
		safeclose(all->here_doc_fd[0]);
		safeclose(all->link_fd[0]);
		safeclose(all->link_fd[1]);
		safeclose(all->default_out);
		if (all->here_doc_limiter)
			free(all->here_doc_limiter);
		free_t_env(&all->env);
		ft_free_tab((void **)all->all_lines);
		ft_free_tab((void **)all->tokens);
		ft_putchar('\n');
		exit(130);
	}
}
