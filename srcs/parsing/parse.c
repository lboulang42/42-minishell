/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:11:58 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/13 14:12:24 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int		is_same_string(char *str1, char *str2)
{
	int i;
	
	i = -1;
	if (ft_strlen(str1) != ft_strlen(str2))
		return (0);
	while (str1[++i] && str2[++i])
	{
		if (str1[i] != str2[i])
			return (0);		
	}
	return (1);
}
