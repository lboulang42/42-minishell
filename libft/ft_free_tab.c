/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:29:27 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/28 21:45:47 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_free_tab_size(void **tab, int size)
{
	int i;

	i = -1;
	if (tab)
		while (++i < size)
			if (tab[i])
				free(tab[i]);
	if (tab)
		free(tab);
}


void	ft_free_tab(void **tab)
{
	int	i;

	i = -1;
	if (tab)
	{
		while (tab[++i])
			free(tab[i]);
	}
	if (tab)
		free(tab);
}
