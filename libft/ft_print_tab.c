/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:10:25 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/30 17:40:36 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

//kick ce bail
void ft_print_tab_leo(char **tab, char *iterate_name)
{
	int i;

	i = -1;
	if (!iterate_name)
		while (tab[++i])
			ft_printf("%s\n", tab[i]);
	else
		while (tab[++i])
			ft_printf("%s[%i] : %s\n", iterate_name, i, tab[i]);
}