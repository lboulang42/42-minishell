/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:56:22 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/15 14:43:56 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	recevoir les inputs avec tout ce qui est entre squote ou dquote en négatif
*/

int     ft_tab_len(char **tab)
{
	int count = 0;
	if (!tab)
		return (0);
	while (tab[count])
		count++;
	return (count);
}

typedef struct s_command 
{
	char    **args;
	char    *path;
}   t_command;

int is_this_meta(char *s, char *metachar)
{
	int i;

	i = -1;
	if (ft_strlen(s) != ft_strlen(metachar))
		return (0);
	while (s[++i])
		if (s[i] != metachar[i])
			return (0);
	return (1);
}


int handle_infile(t_all *all, char **tokens_array, int index_name)
{
	int fd;
	
	fd = open(tokens_array[index_name], O_RDONLY);
	return (fd);
}

int handle_heredoc(t_all *all, char **tokens_array, int index_name)
{
	// (void)limiter;
	return (0);
}

int handle_outfile_trunc(t_all *all, char **tokens_array, int index_name)
{
	int fd;

	fd = open(tokens_array[index_name], O_RDWR | O_CREAT| O_TRUNC, 0666);

	return (fd);
}
int handle_outfile_append(t_all *all, char **tokens_array, int index_name)
{
	int fd;
	
	fd = open(tokens_array[index_name], O_RDWR | O_CREAT| O_APPEND, 0666);
	return (fd);
}

void	ft_child(t_all *all, char *tokens)
{
	
}

char **kick_empty(char **tab) {
    if (tab == NULL)
        return NULL;

    int num_elements = 0;
    char **result = NULL;

    // Count the number of non-empty strings in tab
    int i = 0;
    while (tab[i] != NULL) {
        if (tab[i][0] != '\0')
            num_elements++;
        i++;
    }

    // Allocate memory for the result array
    result = (char **)malloc((num_elements + 1) * sizeof(char *));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Copy non-empty strings to the result array
    int j = 0;
    i = 0;
    while (tab[i] != NULL) {
        if (tab[i][0] != '\0') 
		{
            result[j] = strdup(tab[i]);
            if (result[j] == NULL) {
                fprintf(stderr, "Memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }
            j++;
        } 
		else {
            // Treat strings starting with '\0' as NULL strings
            result[j] = NULL;
        }
        i++;
    }
    result[j] = NULL; // Add NULL as the last element to terminate the array

    return result;
}


void	get_outfile_infile(t_all *all, char **tokens)
{
	int	i;

	i = -1;
	int fd = -1;
	while (tokens[++i +1])
	{
		if (is_this_meta(tokens[i], "<"))
			fd = handle_infile(all, tokens, i+1);//infile name = i+1
		else if (is_this_meta(tokens[i], "<<"))
			fd = handle_heredoc(all, tokens, i+1);//i+1 = limiter du here_doc
		else if (is_this_meta(tokens[i], ">"))
			fd = handle_outfile_trunc(all, tokens, i+1);
		else if (is_this_meta(tokens[i], ">>"))
			fd = handle_outfile_append(all, tokens, i+1);
		if (is_this_meta(tokens[i], "<") || is_this_meta(tokens[i], "<<") || is_this_meta(tokens[i], ">") || is_this_meta(tokens[i], ">>"))
		{
			if (fd == -1)
			{
				fprintf(stderr, "%s: ERRORRRRR\n", tokens[i + 1]);
				exit(1);
			}
			if ((is_this_meta(tokens[i], "<") || is_this_meta(tokens[i], "<<")))
				dup2(fd, 0);
			else
				dup2(fd, 1);
			close(fd);
			tokens[i][0] = '\0';
			tokens[i + 1][0] = '\0';
		}
	}
}

void inverse_all(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < 0)
			str[i] *= -1;
	}
}

void	tokens_positif(char **tokens)
{
	int i;
	i = -1;
	while (tokens[++i])
		inverse_all(tokens[i]);
}


/*
pipex de golmon
*/


/*
Split cmd to get cmd name and command arguments in pipex->cmd_args
Send to funct to check if the cmd is accessible and get the cmd_path from it.
*/

char	*ft_join_path(char *try_path, char *cmd_name)
{
	char	*tmp_path;
	char	*cmd_path;

	tmp_path = ft_strjoin(try_path, "/");
	if (!tmp_path)
		return (NULL);
	cmd_path = ft_strjoin(tmp_path, cmd_name);
	if (!cmd_path)
		return (free(tmp_path), NULL);
	free(tmp_path);
	return (cmd_path);
}


/*
Send the accurate error message.
*/
void	ft_access_fail(char *cmd_path, char *cmd_name)
{
	if (cmd_path[ft_strlen(cmd_path) - 1] == '/')
	{
		ft_printf("Pipex: %s: %s\n", cmd_path, ERR_NOTDIR);
		free(cmd_path);
		return ;
	}
	if (access(cmd_path, F_OK))
		ft_printf("Pipex: %s: '%s'\n", cmd_name, ERR_CMD);
	else if (access(cmd_path, X_OK))
		ft_printf("Pipex: %s: %s\n", cmd_path, ERR_PERM);
	free(cmd_path);
}


/*
separate way if cmd is global path / only name / only name without PATH in env
*/
char	*ft_check_acces(char **env_path, char *cmd_name, int i)
{
	char	*cmd_path;

	if (!ft_strncmp(cmd_name, "/", 1))
	{
		cmd_path = ft_strdup(cmd_name);
		if (!access(cmd_path, F_OK | X_OK))
			return (cmd_path);
		return (ft_access_fail(cmd_path, cmd_name), NULL);
	}
	if (!env_path)
	{
		cmd_path = ft_strdup(cmd_name);
		if (!access(cmd_name, F_OK | X_OK))
			return (cmd_path);
		return (ft_access_fail(cmd_path, cmd_name), NULL);
	}
	while (env_path[++i])
	{
		cmd_path = ft_join_path(env_path[i], cmd_name);
		if (!access(cmd_path, F_OK | X_OK))
			return (cmd_path);
		if (env_path[i + 1])
			free(cmd_path);
	}
	return (ft_access_fail(cmd_path, cmd_name), NULL);
}

/*

*/
char *get_path_putain(char *cmd, t_env *env)
{
	char *PATH;
	char **spl_path;
	char *cmd_path;
	PATH = get_value_by_key(env, "PATH");//ca ca merde
	spl_path = ft_split(PATH, ':');//ca ca merde
	cmd_path = ft_check_acces(spl_path, cmd, -1);
	
	return (cmd_path);
}



void    handle_line(t_all *all, char *line, int total_pipes, int index_pipe)
{
	char    **tokens;
	char *cmd_path;

	pipe(all->link_fd);
	// if (index_pipe == 0)
	// 	all->infile_fd = 0;
	// if (index_pipe < total_pipes)
	// 	all->outfile_fd = all->link_fd[1];
	// else if (index_pipe == total_pipes)
	// 	all->outfile_fd = 1;
	
	tokens = ft_split(line, ' ');
	


	//ici bouffon	
	
	
	
	//exec  + dup etc
	all->pid[index_pipe] = fork();
	if (all->pid[index_pipe] == 0)
	{
		get_outfile_infile(all, tokens);//redirige les infiles/outfiles de la line;
		tokens = kick_empty(tokens);//vire les bails vide
		tokens_positif(tokens);//repasse tout en positif
		cmd_path = get_path_putain(tokens[0], all->env);
		if (index_pipe != 0)
		{
			dup2(all->prev, 0);
			close(all->prev);
		}
		if (index_pipe != total_pipes - 1)
		{
			dup2(all->link_fd[1], 1);
		}	
		close(all->link_fd[0]);
		close(all->link_fd[1]);
		if (cmd_path && tokens)
			execve(cmd_path, tokens, all->default_env);
		exit(127);
	}
	else	{
		close(all->link_fd[1]);
		if (all->prev > 0)
			close(all->prev);
		all->prev = all->link_fd[0];
	}
	// if (all->infile_fd > 0)
	// 	close(all->infile_fd);
	// all->infile_fd = all->link_fd[0];
	// if (all->link_fd[1] > 0)
	// 	close(all->link_fd[1]);
	ft_free_tab((void **)tokens);
}



void	exec_init(t_all *all, char *input)
{
	char	**lines;//lines = inputs splités aux |
	int     lines_number;
	int		i;

	i = -1;
	lines = ft_split(input, '|');//gerer si cmd vide plus tard
	lines_number = ft_tab_len(lines);
	// printf("%i\n", lines_number);
	while (lines[++i])
		handle_line(all, lines[i], lines_number, i);
	for (int j = 0; j < lines_number; j++)
		waitpid(all->pid[j], NULL, 0);
	close(all->link_fd[0]);
	ft_free_tab((void **)lines);
}