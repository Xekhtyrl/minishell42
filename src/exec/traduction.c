/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traduction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:07:29 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/25 18:01:53 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_path(t_input *cmd, t_env **envp)
{
	char	*path;

	path = 0;
	path = get_cmd_path(*envp, cmd);
	if (!path && access(cmd->token, X_OK))
		return (0);
	if ((path || !access(path, X_OK)) || (!path && !access(cmd->token, X_OK)))
		cmd->type = CMD_TK;
	if (path)
		free(path);
	return (1);
}

static int	ft_export_no_arg(char **env, t_input *cmd)
{
	if ((!ft_strncmp(env[2], cmd->token, ft_strlen(env[2])) && !cmd->arg)
		|| (!ft_strncmp(env[3], cmd->token, ft_strlen(env[3])) && !cmd->arg))
		return (1);
	return (0);
}

int	trad_input(t_input *cmd, t_env **envp)
{
	t_input	*tmp;
	char	**built;
	char	**env;

	built = (char *[]){"pwd", "env", "echo", "exit", 0};
	env = (char *[]){"cd", "unset", "export", "exporto_patronum", 0};
	tmp = cmd;
	while (tmp && tmp->token)
	{
		if (in_str_array(tmp->token, built) || ft_export_no_arg(env, tmp))
			tmp->type = BUILT_TK;
		else if (in_str_array(tmp->token, env))
			tmp->type = ENV_TK;
		else
			if (!check_path(tmp, envp))
				tmp->type = ERROR_TK;
		tmp = tmp->next;
	}
	return (1);
}
