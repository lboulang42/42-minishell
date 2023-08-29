/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:42:31 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/29 19:46:03 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Return 1 si le fichier est un dossier; Return 0;
int     file_is_directory(char *cmd_path, char *cmd_name)
{
    struct stat tmp;
    
    stat(cmd_path, &tmp);
	if (!S_ISREG(tmp.st_mode))
	{
		fprintf(stderr, "5%s : %s : %s", MINI, cmd_name, ERR_ISDIR);
        return (1);
	}
    return (0);
}

void safeclose(int fd)
{
	if (fd > 0)
		close(fd);
}

void update_status_int(t_all *all, int status)
{
	char *itoa_status;
	itoa_status = ft_itoa(all->status);
	do_export(all, "?", itoa_status);
	free(itoa_status);
}

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
