/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:17:28 by gcozigon          #+#    #+#             */
/*   Updated: 2023/07/13 18:45:20 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_error(t_all *all, char **cmd_args)
{
	close_pipes(all);
	free_resources(all);
	free_split(cmd_args);
	exit(1);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '\n')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
	dest[++i] = '\0';
	return (dest);
}

char	*ft_strjoingnl(char *s1, char *s2)
{
	int		i;
	char	*str;
	int		len;
	int		j;

	j = 0;
	i = 0;
	if (!s1)
		return (free(s1), ft_strdup(s2));
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	str = (char *)malloc(sizeof(char) * ((len) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (free(s1), str);
}
