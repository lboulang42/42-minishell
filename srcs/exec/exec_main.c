/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 13:31:02 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/30 18:44:18 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_init(t_all *all)
{
	int		lines_number;
	int		i;
	int		j;

	i = -1;
	all->status = 0;
	all->all_lines = ft_split(all->input, '|');
	if (!all->all_lines)
		return ((void)free(all->input));
	free(all->input);
	lines_number = ft_tab_len(all->all_lines);
	all->prev = -1;
	all->btn_fd = -1;
	all->link_fd[0] = -1;
	all->link_fd[1] = -1;
	all->redir_before = 0;
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
		safeclose(all->prev);
	signal(SIGINT, &ctrlc);
	ft_free_tab((void **)all->all_lines);
	free_redir_list(all);
}

void	ft_kill_dir(char **PATHvar, char *cmd_path, char *cmd_name)
{
	t_all	*all;

	all = init_data();
	if (cmd_path)
		free(cmd_path);
	ft_free_tab((void **)all->tokens);
	free_t_env(&all->env);
	ft_free_tab((void **)PATHvar);
	ft_free_tab((void **)all->all_lines);
	ft_free_tab_size((void **)all->arg, all->args_size + 1);
	free_redir_list(all);
	exit(126);
}

char	**get_env(t_env *env)
{
	t_env	*tmp;
	char	**res;
	char	*temp2;
	int		counter;

	res = NULL;
	counter = 0;
	tmp = env;
	while (tmp)
	{
		counter++;
		tmp = tmp->next;
	}
	res = malloc(sizeof(char *) * (counter + 1));
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

void	parent(t_all *all)
{
	safeclose(all->link_fd[1]);
	if (all->prev > 0)
		safeclose(all->prev);
	all->prev = all->link_fd[0];
	signal(SIGQUIT, SIG_IGN);
	if (all->link_fd[1] > 0)
		safeclose(all->link_fd[1]);
	ft_free_tab((void **)all->tokens);
	ft_free_tab_size((void **)all->arg, all->args_size + 1);
}

void	ft_free_only_builtin(t_all *all, int status)
{
	ft_free_tab((void **)all->tokens);
	ft_free_tab_size((void **)all->arg, all->args_size + 1);
	dup2(all->default_out, 1);
	safeclose(all->default_out);
	update_status_int(all, all->status);
}

/*only one builtin no pipe*/
void	only_builtin(t_all *all, int index_pipe, int builtin_code)
{
	int	btn_fd;
	int	status;

	all->pid[index_pipe] = -1;
	all->default_out = dup(1);
	tokens_positif(all->tokens, 1);
	btn_fd = get_outfile_infile_builtin(all, all->tokens, all->all_lines);
	if (btn_fd == -3)
	{
		all->status = 1;
		return ((void)ft_free_only_builtin(all, 1));
	}
	if (btn_fd == -2)
	{
		free_redir_list(all);
		all->status = 1;
		return ((void)ft_free_only_builtin(all, 1));
	}
	all->tokens = kick_empty_tokens(all->tokens);
	tokens_positif(all->tokens, 0);
	all->status = execute_builtin(all, builtin_code);
	ft_free_only_builtin(all, all->status);
}

int	count_redir(char **tokens)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (tokens[++i])
	{
		if (isredir(tokens[i]))
			res++;
	}
	return (res);
}

void	handle_line(t_all *all, int index_pipe)
{
	char	**tokens;
	char	*cmd_path;
	int		builtin_code;
	int		wstatus;

	all->pid[index_pipe] = -1;
	all->default_out = -1;
	signal(SIGINT, SIG_IGN);
	all->tokens = ft_split(all->all_lines[index_pipe], ' ');
	if (!all->tokens)
		return ;
	if (!parse(all, all->tokens))
		return ;
	builtin_code = is_builtin(all->cmd);
	if (builtin_code >= 0 && ft_tab_len(all->all_lines) == 1)
		return ((void)only_builtin(all, index_pipe, builtin_code));
	pipe(all->link_fd);
	all->pid[index_pipe] = fork();
	if (all->pid[index_pipe] == 0)
		child(all, index_pipe, builtin_code);
	else
	{
		all->redir_before += count_redir(all->tokens);
		parent(all);
	}
}
