/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 13:31:02 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/28 12:52:36 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




void	exec_init(t_all *all, char *input)
{
	char	**lines;//lines = inputs splités aux |
	int     lines_number;
	int		i;
	char *tmp;
	int j;
	i = -1;
	all->status = 0;
	all->all_lines = ft_split(input, '|');//gerer si cmd vide plus tard
	if (!all->all_lines)
		return ((void)free(input));
	free(input);
	lines_number = ft_tab_len(all->all_lines);
	all->prev = -1;
	all->btn_fd = -1;
	all->link_fd[0] = -1;
	all->link_fd[1] = -1;
	while (all->all_lines[++i])
		handle_line(all, i);
	
	j = 0;
	while (j < lines_number)
	{
		waitpid(all->pid[j], &all->status, 0);
		if (WIFEXITED(all->status))
		{
			all->status = WEXITSTATUS(all->status);
			update_status_int(all, all->status);
		}
		j++;
	}
	if (all->prev > 0)
		close(all->prev);
	signal(SIGINT, & ctrlc);
	ft_free_tab((void **)all->all_lines);
}

void ft_kill_dir(char **PATHvar, char *cmd_path, char *cmd_name)
{
	t_all *all;

	all = init_data();

	if (cmd_path)
		free(cmd_path);

	ft_free_tab((void **)all->tokens);
	free_t_env(&all->env);
	ft_free_tab((void **)PATHvar);
	ft_free_tab((void **)all->all_lines);
	exit(126);
}

char **get_env(t_env *env)
{
	t_env *tmp;
	char **res = NULL;
	char *temp2;
	
	int counter = 0;
	tmp = env;
	while (tmp)
	{
		counter++;
		tmp = tmp->next;
	}
	res = malloc(sizeof(char *) * (counter+1));
	tmp = env;
	counter = 0;
	while (tmp)
	{
		temp2 = ft_strjoin(tmp->name, (char *)"=");
		res[counter] = ft_strjoin(temp2, tmp->value);
		free(temp2);
		tmp = tmp->next;
		counter++;
	}
	res[counter] = NULL;
	return (res);
}

/*
premier token peut etre une redir
*/

void parent(t_all *all)
{
	close(all->link_fd[1]);
	if (all->prev > 0)
		close(all->prev);
	all->prev = all->link_fd[0];
	signal(SIGQUIT, SIG_IGN);
	if (all->link_fd[1] > 0)
		close(all->link_fd[1]);
	ft_free_tab((void **)all->tokens);
	free(all->type);
	ft_free_tab((void **)all->arg);
	ft_free_tab((void **)all->files);
	
}

void ft_free_only_builtin(t_all *all, int status)
{
	ft_free_tab((void **)all->tokens);
	free(all->type);
	ft_free_tab((void **)all->arg);
	ft_free_tab((void **)all->files);
	dup2(all->default_out, 1);
	close(all->default_out);
	update_status_int(all, all->status);
}

/*
if btn_fd == -2 : redir se passe mal
set all->pid[index_pipe] a -1 pour ne pas wait un pid (car pas de fork);
set all->default_out pour reset la sortie standard pour le prochain input (pas nécessaire d'utiliser un infile car aucun de nos builtin n'utilise d'infile)
*/
void only_builtin(t_all *all, int index_pipe, int builtin_code)
{
	int btn_fd;
	int status;
	
	all->pid[index_pipe] = -1;
	all->default_out = dup(1);
	tokens_positif(all->tokens, 1);
	btn_fd = get_outfile_infile_builtin(all, all->tokens, all->all_lines);
	if (btn_fd == -2)
	{
		all->status = 1;
		return ((void)ft_free_only_builtin(all, 1));
	}
	all->tokens = kick_empty_tokens(all->tokens);
	tokens_positif(all->tokens, 0);
	all->status = execute_builtin(all, builtin_code);
	ft_free_only_builtin(all, all->status);
}
void    handle_line(t_all *all, int index_pipe)
{
	char    **tokens;
	char	*cmd_path;
	int		builtin_code;
	int		wstatus;
	all->default_out = -1;
	signal(SIGINT, SIG_IGN);
	all->tokens = ft_split(all->all_lines[index_pipe], ' ');
	if (!all->tokens)
		return;
	parse(all, all->tokens);
	builtin_code = is_builtin(all->cmd);
	if (builtin_code >= 0 && ft_tab_len(all->all_lines) == 1)
		return ((void)only_builtin(all, index_pipe, builtin_code));
	pipe(all->link_fd);
	all->pid[index_pipe] = fork();
	if (all->pid[index_pipe] == 0)
		child(all, index_pipe, builtin_code);
	else
		parent(all);
}
