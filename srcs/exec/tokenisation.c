/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 13:39:07 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/31 12:35:35 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inverse_all(char *str, int flag)
{
	int	i;

	i = -1;
	if (flag == 1)
	{
		while (str && str[++i])
			if (str[i] < 0 && str[i] != -62 && str[i] != -60)
				str[i] *= -1;
	}
	else if (flag == 0)
	{
		while (str && str[++i])
			if (str[i] < 0 && str[i])
				str[i] *= -1;
	}
}

void	tokens_positif(char **tokens, int flag)
{
	int	i;

	i = -1;
	while (tokens[++i])
		inverse_all(tokens[i], flag);
}

static int	tab_len(char **tab)
{
	int	i;
	int	len;

	len = 0;
	i = -1;
	while (tab[++i])
		if (tab[i][0] != '\0')
			len++;
	return (len);
}

char	**kick_empty_tokens(char **tab)
{
	char	**result;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!tab)
		return (NULL);
	result = malloc(sizeof(char *) * (tab_len(tab) + 1));
	if (!result)
		return (err_msg(ERR_MALL, "kick_empty_tokens() 1"), NULL);
	while (tab[++i])
	{
		if (tab[i][0] != '\0')
		{
			result[j] = ft_strdup(tab[i]);
			if (!result[j])
				return (err_msg(ERR_MALL, "kick_empty_tokens() 2"), NULL);
			j++;
		}
	}
	result[j] = NULL;
	ft_free_tab((void **)tab);
	return (result);
}
