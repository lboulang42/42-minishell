/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:02:37 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/19 16:33:52 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "limits.h"
#ifndef PATH_MAX
# define PATH_MAX 8192
#endif

int	pwd(void)
{
	static char		path[PATH_MAX] = {0};

	getcwd(path, PATH_MAX);
	if (path[0])
    {
		ft_putendl(path);
        return (EXIT_SUCCESS);
    }
    return (EXIT_FAILURE);
}

// char	*pwd_malloc(void)
// {
// 	return (getcwd(0, 0));
// }