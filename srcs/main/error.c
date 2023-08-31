/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:23:50 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/31 16:17:21 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_msg(char *err_msg, char *function_name)
{
	if (!function_name)
		return ((void)printf("%s\n", err_msg));
	return ((void)printf("%s : function : %s\n", err_msg, function_name));
}

char	*toneg(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		str[i++] *= -1;
	return (str);
}
