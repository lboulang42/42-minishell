/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 13:39:07 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/16 18:50:53 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokens_positif(char **tokens)
{
	int i;
	i = -1;
	while (tokens[++i])
		inverse_string(tokens[i], SQUOTE+DQUOTE);
}

static int tab_len(char **tab)
{
    int i;
    int len;

    len = 0;
    i = -1;
    while (tab[++i])
        if (tab[i][0] != '\0')
            len++;
    return (len);
}

char **kick_empty_tokens(char **tab) 
{
    char **result;
    int num_elements;
    int i;
    int j;

    i = -1;
    j = 0;
    if (!tab)
        return (NULL);
    num_elements = tab_len(tab);
    result = malloc(sizeof(char *) * (num_elements+1));
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
    result[j] = NULL; // Add NULL as the last element to terminate the array
    return (result);
}
