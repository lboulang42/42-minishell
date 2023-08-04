/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 19:22:45 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/04 19:22:54 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait_pid(t_all *all, int limit)
{
	int	i;
	int	wstatus;

	i = -1;
	while (++i < limit)
	{
		waitpid(all->pid[i], &wstatus, 0);
		if (WIFEXITED(wstatus))
			all->exit_code = WEXITSTATUS(wstatus);
	}
}
