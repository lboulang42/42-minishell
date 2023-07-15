/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:22:51 by lboulang          #+#    #+#             */
/*   Updated: 2023/07/15 15:40:57 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


void ft_free_cmd(t_cmd *cmd)
{
    free(cmd->args);
    // if (cmd->args)
    //     ft_free_tab((void **)cmd->args);

}

void ft_exec(t_cmd *cmd, char **env)
{
    pid_t pid;
    
    pid = fork();
    if (pid == 0)
    {
        execve(cmd->path, cmd->args, env);
        printf("exec failed\n");
        ft_free_cmd(cmd);
        exit(1);
    }
    printf("out");
    ft_free_cmd(cmd);
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    t_cmd cmd;
    cmd.name = "ls";
    cmd.path = "/usr/bin/ls";
    cmd.args = malloc(sizeof(char *) * 3);
    cmd.args[0] = "ls";
    cmd.args[1] = "-la";
    cmd.args[2] = NULL;
    ft_exec(&cmd, env);
    exit(0);
}