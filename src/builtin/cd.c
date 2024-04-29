/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:41:58 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/29 23:07:32 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cd(t_env *envp, char *path)
{
	char *new_path;
	char *pwd;

	pwd = getcwd(NULL, 0);
	chdir(path);
	new_path = getcwd(NULL, 0);
	if (!ft_strncmp(path, "..", ft_strlen(path)) && !ft_strncmp(path, new_path, ft_strlen(path)))
		chdir(get_env_var(envp, "HOME"));
	replace_or_append("PWD", new_path, 0, envp);
	replace_or_append("OLD_PWD", pwd, 0, envp);
}

// int main(int argc, char **argv, char **envp)
// {
// 	ft_cd(NULL, argv[1], &argv[2]);
// }