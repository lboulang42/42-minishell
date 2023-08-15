/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:10:25 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/03 14:11:45 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
void ft_print_tab_leo(char **tab, char *iterate_name)
{
	int i;

	i = -1;
	if (!iterate_name)
		while (tab[++i])
			fprintf(stderr, "%s\n", tab[i]);
	else
		while (tab[++i])
			fprintf(stderr, "%s[%i] : %s\n", iterate_name, i, tab[i]);
}