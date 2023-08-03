/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:56:22 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/03 20:12:51 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	recevoir les inputs avec tout ce qui est entre squote ou dquote en négatif
*/

int     ft_tab_len(void **tab)
{
	int count = 0;
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


void handle_infile(t_all *all, char **tokens_array, int index_name)
{
	if (all->infile_fd != 0)
		close(all->infile_fd);
	all->infile_fd = open(tokens_array[index_name], O_RDONLY);
	if (all->infile_fd < 0)
		printf("Minishell : %s: %s\n", tokens_array[index_name], ERR_NOSUCHF);
	tokens_array[index_name-1][0] = '\0';
	tokens_array[index_name][0] = '\0';
}

void handle_heredoc(t_all *all, char **tokens_array, int index_name)
{
	// (void)limiter;
	printf("has an here_doc to handle\n");
}

void handle_outfile_trunc(t_all *all, char **tokens_array, int index_name)
{
	if (all->outfile_fd != 1)
		close(all->outfile_fd);
	all->outfile_fd = open(tokens_array[index_name], O_RDWR | O_CREAT| O_TRUNC, 0666);
	printf("has an outfile_trunc to handle\n");
	tokens_array[index_name-1][0] = '\0';
	tokens_array[index_name][0] = '\0';
}

void handle_outfile_append(t_all *all, char **tokens_array, int index_name)
{
	if (all->outfile_fd != 1)
		close(all->outfile_fd);
	all->outfile_fd = open(tokens_array[index_name], O_RDWR | O_CREAT| O_APPEND, 0666);
	tokens_array[index_name-1][0] = '\0';
	tokens_array[index_name][0] = '\0';
	printf("has an outfile_append to handle\n");
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
	while (tokens[++i +1])
	{
		if (is_this_meta(tokens[i], "<"))
			handle_infile(all, tokens, i+1);//infile name = i+1
		else if (is_this_meta(tokens[i], "<<"))
			handle_heredoc(all, tokens, i+1);//i+1 = limiter du here_doc
		else if (is_this_meta(tokens[i], ">"))
			handle_outfile_trunc(all, tokens, i+1);
		else if (is_this_meta(tokens[i], ">>"))
			handle_outfile_append(all, tokens, i+1);
	}
}

void	tokens_positif(char **tokens)
{
	int i;
	i = -1;
	while (tokens[++i])
		inverse_string(tokens[i], SQUOTE+DQUOTE);
}

void    handle_line(t_all *all, char *line, int total_pipes, int index_pipe)
{
	char    **tokens;
	char *cmd_path;

	pipe(all->link_fd);
	if (index_pipe == 0)
		all->infile_fd = 0;
	if (index_pipe < total_pipes)
		all->outfile_fd = all->link_fd[1];
	else if (index_pipe == total_pipes)
		all->outfile_fd = 1;
	
	tokens = ft_split(line, ' ');
	get_outfile_infile(all, tokens);//redirige les infiles/outfiles de la line;
	tokens = kick_empty(tokens);//vire les bails vide
	tokens_positif(tokens);//repasse tout en positif


	//ici bouffon	
	cmd_path = get_path_putain(tokens[0], all->env);
	
	ft_print_tab_leo(tokens, "oe token");
	
	
	//exec  + dup etc
	all->pid[index_pipe] = fork();
	if (all->pid[index_pipe] == 0)
	{
		//child
		if (all->infile_fd > -1)
		{
			dup2(all->infile_fd, 0);
			dup2(all->outfile_fd, 1);
			close(all->infile_fd);
			close(all->outfile_fd);
			close(all->link_fd[0]);
			close(all->link_fd[1]);
			if (cmd_path && tokens)
				execve(cmd_path, tokens, all->default_env);
		}
		else
			ft_close_link_fd(pipex, 2);
		//free le merdier
		exit(127);
	}
	if (all->infile_fd > 0)
		close(all->infile_fd);
	all->infile_fd = all->link_fd[0];
	if (all->link_fd[1] > 0)
		close(all->link_fd[1]);
		//parent
	ft_free_tab((void **)tokens);
}

void	exec_init(t_all *all, char *input)
{
	char	**lines;//lines = inputs splités aux |
	int     lines_number;
	int		i;

	i = -1;
	lines = ft_split(input, '|');//gerer si cmd vide plus tard
	lines_number = ft_tab_len((void **)lines);
	
	while (lines[++i])
		handle_line(all, lines[i], lines_number, i);
	printf("all lines readed");
	
	ft_free_tab((void **)lines);
}