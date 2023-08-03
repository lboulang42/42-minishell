#include <fcntl.h>


#include "minishell.h"


// Structure pour stocker les arguments


// // Fonction pour exécuter une commande
void	execute_command(t_all *all, t_arguments *args)
{
	char *path = find_cmd_2(all, args->args[0]);
	//si path null ?
	execve(path, args->args, NULL);
	perror("execve"); // En cas d'erreur
	exit(EXIT_FAILURE);
}

void	parse_arguments(char *input, t_arguments *args)
{
	char	**tokens;
	int		i;

	i = -1;
	args->count = 0;
	tokens = ft_split(input, ' ');
	if (tokens == NULL)
	{
		fprintf(stderr, "Error: Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	while (tokens[++i] && i < MAX_ARGS -1)
	{
		args->args[i] = tokens[i];
		args->count++;
	}
	args->args[args->count] = NULL;// Ajout d'un pointeur NULL à la fin pour execve
}

// // Fonction pour rediriger la sortie
void	redirect_output(char *output_file, int mode)
{
	int	fd;

	if (mode == 1)
	{
		// Mode append
		fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		// Mode normal
		fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

// Fonction pour rediriger l'entrée
void	redirect_input(char *input_file)
{
	int	fd;

	fd = open(input_file, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

// // Fonction pour gérer les pipes et exécuter les commandes
// void	execute_piped_commands(t_all *all, char **commands)
// {
// 	// int		prev_pipe;
// 	// int		saved_stdout;
// 	// int		i;
// 	// int pipe_fd[2];
// 	// int		has_output_redirection;
// 	// int		has_input_redirection;
// 	// int		has_redirection;
// 	// char	**output_tokens;
// 	// char	**input_tokens;
// 	// t_arguments args;


// 	// prev_pipe = STDIN_FILENO;
// 	// saved_stdout = dup(STDOUT_FILENO);
// 	i = -1;
// 	while (commands[++i])
// 	{
// 		// pipe(pipe_fd);
// 		// dup2(prev_pipe, STDIN_FILENO);
// 		// close(prev_pipe);
// 		// dup2(pipe_fd[1], STDOUT_FILENO);
// 		// close(pipe_fd[1]);
// 		has_output_redirection = (ft_strnstr(commands[i], ">>", ft_strlen(commands[i])) != NULL);
// 		has_input_redirection = (ft_strnstr(commands[i], "<<", ft_strlen(commands[i])) != NULL);
// 		has_redirection = (ft_strnstr(commands[i], ">", ft_strlen(commands[i])) != NULL && !has_output_redirection);
// 		if (has_output_redirection)
// 		{
// 			// Redirection en mode append
// 			output_tokens = ft_split(commands[i], '>');
// 			redirect_output(output_tokens[1], 1);
// 			ft_free_tab((void **)output_tokens);// Free allocated memory
// 		}
// 		else if (has_redirection)
// 		{
// 			// Redirection de la sortie
// 			output_tokens = ft_split(commands[i], '>');
// 			redirect_output(output_tokens[1], 0);
// 			ft_free_tab((void **)output_tokens);// Free allocated memory
// 		}
// 		else if (has_input_redirection)// Redirection de l'entrée
// 		{
// 			input_tokens = ft_split(commands[i], '<');
// 			redirect_input(input_tokens[1]);
// 			ft_free_tab((void **)input_tokens); // Free allocated memory
// 		}
// 		parse_arguments(commands[i], &args);
// 		int index_args = -1;
// 		while (args.args[++i])
// 			inverse_string(args.args[i], SQUOTE+DQUOTE);
// 		execute_command(all, &args);
// 		prev_pipe = pipe_fd[0];
// 	}
// 	// Restauration de la sortie standard
// 	dup2(saved_stdout, STDOUT_FILENO);
// 	close(saved_stdout);
// 	// Free allocated memory for the commands array
	
// 	ft_free_tab((void **)commands);
// }




// int	main(void)
// {
// 	char	input[] = "cat /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin | grep usr >> outfile";

// 	exec(input);
// 	return (0);
// }
