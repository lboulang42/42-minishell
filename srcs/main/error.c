/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:23:50 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/16 18:55:58 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_msg(char *err_msg, char *function_name)
{
	if (!function_name)
		return ((void)printf("%s\n", err_msg));
	return ((void)printf("%s : function : %s\n", err_msg, function_name));
}
