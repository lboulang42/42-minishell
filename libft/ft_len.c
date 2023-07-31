/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:13:05 by lboulang          #+#    #+#             */
/*   Updated: 2023/07/30 21:11:32 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Return The Lenght Of The String S*/
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s || !*s)
		return (i);
	while (s[i])
		i++;
	return (i);
}
