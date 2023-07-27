/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanmain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:29:10 by lboulang          #+#    #+#             */
/*   Updated: 2023/07/22 16:02:34 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;
	(void)av;
	
	if (ac != 1)
		return (ft_err(AV_ERR), 1);
	init_env(&data, env);
    print_t_env(data.env);
    free_t_env(&data.env);
}