/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:41:58 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/23 13:54:39 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cd(t_env **envp, char *path, char **erf)
{
	char *new_path;
	char *pwd;

	pwd = getcwd(NULL, 0);
	chdir(path);
	new_path = getcwd(NULL, 0);
	if (!ft_strncmp(path, "..", ft_strlen(path)) && !ft_strncmp(path, new_path, ft_strlen(path)))
		chdir(ft_getenv("HOME", *envp));
	ft_update_env("PWD", new_path, envp);
	ft_update_env("OLD_PWD", pwd, envp);
}

// int main(int argc, char **argv, char **envp)
// {
// 	ft_cd(NULL, argv[1], &argv[2]);
// }