/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:11:58 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/28 12:12:42 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_same_string(char *str1, char *str2)
{
	if (ft_strlen(str1) != ft_strlen(str2))
		return (0);
	if (ft_strncmp(str1, str2, ft_strlen(str2)))
		return (0);	
	return (1);
}
