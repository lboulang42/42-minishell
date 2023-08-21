/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:28:12 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/21 17:26:07 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd_name)
{
	static char	*bltnnames[7] = {"cd", "echo", "exit", "export", "pwd", "unset", "env"};
	int			i;

	i = -1;
	while (++i < 7)
		if (is_same_string(cmd_name, bltnnames[i]))
			return (i);
	return (-1);
}

// fprintf(stderr, "in BUILTIN\n");
// fprintf(stderr, "link_fd[0] = %d\n", all->link_fd[0]);
// fprintf(stderr, "link_fd[1] = %d\n", all->link_fd[1]);
// fprintf(stderr, "prev = %d\n", all->prev);
// signal(SIGINT, & ctrlc);
// signal(SIGQUIT, & ctrld);

// get_outfile_infile(all, tokens);//redirige les infiles/outfiles de la line;
// tokens = kick_empty_tokens(tokens);//vire les bails vide
// tokens_positif(tokens);//repasse tout en positif

//	fprintf(stderr, "pas la last cmd qui est builtin\n");

void ping_close(char *name, int fd)
{
	fprintf(stderr, "now closing %s as fd : %d\n", name, fd);
	close(fd);
}
	// if (index_pipe != 0) {
    //     dup2(all->prev, 0);
    //     ping_close("all->prev", all->prev);
	// 	// close(all->prev);
    // }
    // if (index_pipe != ft_tab_len(all_lines) - 1) {
    //     dup2(all->link_fd[1], 1);
    // }
    // close(all->link_fd[0]);
    // ping_close("all->link_fd[1]", all->link_fd[1]);
    // Execute the built-in command



/*
execute le bon builtin
*/
void	execute_builtin(char **tokens, t_all *all, int i, char **all_lines, int index_pipe)
{
    if (i == 0)
        cd();
    else if (i == 1)
        echo(tokens);
    else if (i == 2)
        ft_exit(all, tokens, all_lines);
    else if (i == 3)
        export(all, tokens);
    else if (i == 4)
        pwd();
    else if (i == 5)
        unset();
    else if (i == 6)
        env(all);
}