/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 22:02:20 by gcozigon          #+#    #+#             */
/*   Updated: 2023/07/15 17:51:57 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir(t_all *all, int nb)
{
	if (nb != 0)
	{
		dup2(all->prev, STDIN_FILENO);
		close(all->prev);
	}
	if (nb != all->nbcmd - 1)
		dup2(all->pipe_fd[1], STDOUT_FILENO);
	close(all->pipe_fd[0]);
	close(all->pipe_fd[1]);
}

char	*find_cmd(t_all *all, char **cmd_split)
{
	char	*result;

	if (!*cmd_split)
		return (NULL);
	if (ft_strrchr(cmd_split[0], '/'))
	{
		if (!access(cmd_split[0], F_OK | X_OK))
			return (cmd_split[0]);
		return (ft_check_acces(cmd_split[0], cmd_split[0]), NULL);
	}
	all->path = keep_path(all);
	result = check_relative_paths(all, cmd_split);
	free_split(all->path);
	return (result);
}

token **list[0]=ls [1] = -r


struct *token 
{
	char *name = ls
	char *type = str;
}	s_token;

token **list_token;


malloc();
list_token[1]

// ls
// -R 
// > 
// outfile 
// -a 
// -l
listtoken[0] 
name="ls -R";
type="cmd";

listtoken[2]
name=">"
type="redirection"

listtoken[2]
name="|"
type="redirection"

listtoken[2]
name="a"
type="word"

listtoken[2]
name="-R"
type="flage"

.....




| wc -l | < Makefile | > out >> app1 >> app2 > out2 echo lol
// [ls -R > outfile -a -l]|[ wc -l ]|[ < Makefile ]|[ > out >> app1 >> app2 > out2 echo lol]
// {ls}{-R}{>}{outfile}{-a -l}{|}{wc -l}{< Makefile}...
[0][ls -R > outfile -a -l]
"|"
// {wc}{-l}
// {<}{Makefile}
// {>}{out}{>>}{app1}{>>}{app2}{>}{out2}{echo}{lol}





int	execute_child_process(t_all *all, char **av, char **cmd_args, int i)
{
	
	ft_redir(all, i);
	// parse(cmd_args);
	// openfiles(all, cmd_args);
	all->path_cmd1 = find_cmd(all, cmd_args);
	if (all->path_cmd1 && cmd_args)
		ft_exec(all, i, cmd_args);
	close_pipes(all);
	free_resources(all);
	free_split(cmd_args);
	exit(127);
}

int	pipex(t_all *all, char **av)
{
	int		i;
	char	**cmd_args;

	i = -1;
	all->prev = -1;
	while (++i < all->nbcmd)
	{
		pipe(all->pipe_fd);
		all->pid[i] = fork();
		if (all->pid[i] == 0)
		{
			cmd_args = ft_split(av[i], ' ');
			if (!cmd_args)
				return (exit(1), 1);
			execute_child_process(all, av, cmd_args, i);
		}
		close(all->pipe_fd[1]);
		if (all->prev != -1)
			close(all->prev);
		all->prev = all->pipe_fd[0];
	}
	ft_wait(all);
	return (0);
}
