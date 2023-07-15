/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:22:51 by lboulang          #+#    #+#             */
/*   Updated: 2023/07/15 18:01:28 by lboulang         ###   ########.fr       */
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
    // (void)ac;
    // (void)av;
    // t_cmd cmd;
    // cmd.name = "ls";
    // cmd.path = "/usr/bin/ls";
    // cmd.args = malloc(sizeof(char *) * 3);
    // cmd.args[0] = "ls";
    // cmd.args[1] = "-la";
    // cmd.args[2] = NULL;
    // ft_exec(&cmd, env);
    // exit(0);

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
        // printf("[%s]\n", str);
        // add_history(str);
        // all.tab = ft_split(str, '|');
    	// all.nbcmd = counter(str, '|');
        // pipex(&all, all.tab);
        // close_pipes(& all);
	    // free_resources(& all);

/*
https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html#tag_02_07_04
    token recognition :
     heredoc :
      // trigger par "<<" et "<<-" (char de redirection)
      // next param est limiter 
      // If any character in limiter is quoted, the delimiter shall be formed by performing quote removal on limiter, and the here-document lines shall not be expanded. Otherwise, the delimiter shall be the word itself.
      // lmiter est traite comme un char mm si c'est un $qqchose
      // Si aucun char entre "", toutes les lignes du here-document vont au parameter expansion, substitution, et arithmetic expansion.
      // dams ce cas, le \ dans les prompt se comporte comme entre "" (pas interprete)
      // Les " ne sont pas traite specifiquement dans le heredoc sauf pour les doubles quotes dans "${}", "$()" et "$``"
      // Si la redirection se fait avec un <<- toutes les tabs (\t) sont delete tous les prompt.
      // Si plus de un << ou <<- dans la line, on les execute dans l'ordre (1er puis 2e etc);
     tokenisation (break les inputs en token):
        En appllicant la premiere rule au next character de l'input, jusqua ce que le token soit delimite par une des rules
        Les char qui forment le token sont exactement ceux de l'input meme les quoting characters (\ et simple et double quotes)
        Si un token est delimite et qu'il est vide le process continue jusqua ce qu'un vrai token soit delimite.
        Rules :
            - Si la fin de l'input est trouvee (\0 ou \n), le token est delimite, si token vide le token est '\0'.
            - Si le char precedent fait partie d'un operateur et que le char actuel n'est pas quoted et 
    

If the previous character was used as part of an operator and the current character is not quoted and can be used with the current characters to form an operator, it shall be used as part of that (operator) token.


If the previous character was used as part of an operator and the current character cannot be used with the current characters to form an operator, the operator containing the previous character shall be delimited.

If the current character is backslash, single-quote, or double-quote ( '\', '", or ' )' and it is not quoted, it shall affect quoting for subsequent characters up to the end of the quoted text. The rules for quoting are as described in Quoting. During token recognition no substitutions shall be actually performed, and the result token shall contain exactly the characters that appear in the input (except for <newline> joining), unmodified, including any embedded or enclosing quotes or substitution operators, between the quote mark and the end of the quoted text. The token shall not be delimited by the end of the quoted field.

If the current character is an unquoted '$' or '`', the shell shall identify the start of any candidates for parameter expansion ( Parameter Expansion), command substitution ( Command Substitution), or arithmetic expansion ( Arithmetic Expansion) from their introductory unquoted character sequences: '$' or "${", "$(" or '`', and "$((", respectively. The shell shall read sufficient input to determine the end of the unit to be expanded (as explained in the cited sections). While processing the characters, if instances of expansions or quoting are found nested within the substitution, the shell shall recursively process them in the manner specified for the construct that is found. The characters found from the beginning of the substitution to its end, allowing for any recursion necessary to recognize embedded constructs, shall be included unmodified in the result token, including any embedded or enclosing substitution operators or quotes. The token shall not be delimited by the end of the substitution.

If the current character is not quoted and can be used as the first character of a new operator, the current token (if any) shall be delimited. The current character shall be used as the beginning of the next (operator) token.

If the current character is an unquoted <newline>, the current token shall be delimited.

If the current character is an unquoted <blank>, any token containing the previous character is delimited and the current character shall be discarded.

If the previous character was part of a word, the current character shall be appended to that word.

If the current character is a '#', it and all subsequent characters up to, but excluding, the next <newline> shall be discarded as a comment. The <newline> that ends the line is not considered part of the comment.

The current character is used as the start of a new word.


    parsing input en commandes: 
    
    expansions :
    
    redirections :
    
    execution des fonctions, built-in:
    
    wait les commandes, recuperer les exit status:
    
*/


        // here_document
        //ft_heredoc
        // token recognition
    }
    
}

void ft_heredoc()
{
   
    
}