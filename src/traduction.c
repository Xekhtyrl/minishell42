/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traduction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:07:29 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/09 15:14:57 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_path(t_input *cmd, t_env **envp)
{
	char *path;

	path = 0;
	path = get_cmd_path(*envp, cmd);
	if (!path)
		return (0);
	if (path || !access(cmd->token, X_OK))
		cmd->type = CMD_TK;
	if (path)
		free(path);
	return (1);
}

int	trad_input(t_input *cmd, t_env **envp)
{
	t_input	*tmp;
	char	**built;
	char	**env;

	env = (char *[]){"cd", "unset", "export", 0};
	built = (char *[]){"pwd", "env", "echo", "exit", "exporto_patronum", 0};
	tmp = cmd;
	while (tmp && tmp->token)
	{
		if (in_str_array(tmp->token, built) && !tmp->arg)
			tmp->type = BUILT_TK;
		else if (in_str_array(tmp->token, env))
			tmp->type = ENV_TK;
		else
			if (!check_path(tmp, envp))
				return (0);
		tmp = tmp->next;
	}
	return (1);
}
