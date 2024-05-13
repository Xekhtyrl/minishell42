/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:41:58 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/12 19:09:49 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*replace_home_path(t_arg_lst *arg, t_env *envp)
{
	if (!arg)
		return (get_env_var(envp, ft_strdup("HOME")));
	return (ft_strjoin(get_env_var(envp, ft_strdup("HOME")), arg->token + 1));
}

void	ft_cd(t_env *envp, t_arg_lst *arg)
{
	char	*new_path;
	char	*pwd;
	char	*path;

	if (!arg || (arg->token && arg->token[0] == '~'))
		path = replace_home_path(arg, envp);
	else
		path = arg->token;
	pwd = getcwd(NULL, 0);
	chdir(path);
	new_path = getcwd(NULL, 0);
	replace_or_append("PWD", new_path, 0, envp);
	if (ft_strncmp(pwd, new_path, ft_strlen(pwd)))
		replace_or_append("OLDPWD", pwd, 0, envp);
	if (arg && ft_strncmp(path, arg->token, ft_strlen(path)))
		free(path);
}
