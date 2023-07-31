/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tosendmain.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:29:10 by lboulang          #+#    #+#             */
/*   Updated: 2023/07/27 20:09:42 by gcozigon         ###   ########.fr       */
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
