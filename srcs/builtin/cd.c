/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:25:53 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/30 17:40:41 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_cd(t_all *all, char *path)
{
	char	*old_pwd;
	char	*pwd;
	int		res;

	res = chdir(path);
	if (res == -1)
	{
		ft_printf("%s : cd :%s: %s\n", MINI, path, strerror(errno));
		return (EXIT_FAILURE);
	}
	pwd = getcwd(0, 0);
	if (!pwd)
		return (EXIT_SUCCESS);
	do_export(all, "PWD", pwd);
	free(pwd);
	old_pwd = getcwd(0, 0);
	if (!old_pwd)
		return (EXIT_SUCCESS);
	do_export(all, "OLDPWD", old_pwd);
	free(old_pwd);
	return (EXIT_SUCCESS);
}

int	cd(t_all *all, char **tokens)
{
	char	*home_path;
	int		res;

	if (ft_tab_len(tokens) > 2)
	{
		ft_printf("%s: cd: %s\n", MINI, ERR_TOOMARGS);
		return (EXIT_FAILURE);
	}
	if (ft_tab_len(tokens) == 1 || is_same_string(tokens[1], "~") || \
		is_same_string(tokens[1], "~/"))
	{
		home_path = get_key(all->env, "HOME");
		res = do_cd(all, home_path);
		return (free(home_path), res);
	}
	return (do_cd(all, tokens[1]));
}
