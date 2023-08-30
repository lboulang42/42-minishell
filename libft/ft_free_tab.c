/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:29:27 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/30 19:05:05 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_tab_size(void **tab, int size)
{
	int	i;

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
