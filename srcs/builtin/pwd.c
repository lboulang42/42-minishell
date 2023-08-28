/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:02:37 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/28 11:35:17 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	static char	path[PATH_MAX] = {0};

	getcwd(path, PATH_MAX);
	if (path[0])
	{
		printf("%s\n", path);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
