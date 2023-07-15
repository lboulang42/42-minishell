/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:48:27 by lboulang          #+#    #+#             */
/*   Updated: 2023/07/15 17:26:28 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	static t_all	all = {0};
    (void)argc;
    (void)argv;
	all.env = env;
    while (1)
    {
        char *str = readline("easyshell> ");
        if (!str)
            break ;
        if (!*str)
        {
            free(str);
            continue ;
        }
        printf("[%s]\n", str);
        add_history(str);
        
        
        all.tab = ft_split(str, '|');
    	all.nbcmd = counter(str, '|');
        //
        pipex(&all, all.tab);
        close_pipes(& all);
	    free_resources(& all);
    }
    return (0);
}