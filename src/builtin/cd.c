/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:41:58 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/26 19:46:20 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*replace_home_path(t_arg_lst *arg, t_env *envp)
{
	if (!arg)
		return (ft_strdup(get_env_var(envp, ft_strdup("HOME"))));
	return (ft_strjoin(get_env_var(envp, ft_strdup("HOME")), arg->token + 1));
}
// gerer cd -

char	*oldpath_condition(t_env *envp)
{
	char	*path;

	if (get_env_var(envp, ft_strdup("OLDPWD")))
	{
		path = ft_strdup(get_env_var(envp, ft_strdup("OLDPWD")));
		printf("%s\n", path);
	}
	else
	{
		path = ft_strdup("-");
		printf("cd: OLDPWD not set\n");
	}
	return (path);
}

void	ft_cd(t_env *envp, t_arg_lst *arg)
{
	char	*new_path;
	char	*pwd;
	char	*path;

	if (arg && arg->type == SPACE_TK && arg->next)
		arg = arg->next;
	if (!arg || (arg->token && arg->token[0] == '~'))
		path = replace_home_path(arg, envp);
	else if ((arg->token && arg->token[0] == '-' && !arg->token[1]))
		path = oldpath_condition(envp);
	else
		path = ft_strdup(arg->token);
	pwd = getcwd(NULL, 0);
	g_ret_val = chdir(path) * -1;
	if (g_ret_val)
		printf("cd: %s: No such file or directory\n", path);
	new_path = getcwd(NULL, 0);
	replace_or_append(ft_strdup("PWD"), new_path, 0, envp);
	if (ft_strncmp(pwd, new_path, ft_strlen(pwd)))
		replace_or_append(ft_strdup("OLDPWD"), pwd, 0, envp);
	else
		free(pwd);
	free(path);
}
