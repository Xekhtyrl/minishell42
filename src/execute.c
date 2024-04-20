/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:20:36 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/20 18:34:57 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_path(char **envp)
{
	char	*temp;
	char	**path;

	while (*envp)
	{
		temp = ft_strnstr(*envp, "PATH=", ft_strlen(*envp));
		if (temp)
		{
			path = ft_split(temp + 5, ':');
			return (path);
		}
		envp++;
	}
	return (0);
}

int exec_cmd_ve(t_input *cmd, char *path)
{

}

int	execute_command(char **envp, t_input *cmd)
{
	char **built;
	char *path;

	built = ft_split("echo cd pwd export unset env exit", ' ');
	if (!built)
		return (0);
	if (in_list(cmd->token, built))
		cmd->type = BUILT_TK;
	if (cmd->type == WORD_TK)
	{
		path = get_cmd_path(envp, cmd);
		if (path == 0)
			return (strarray_free(built), -1); //error path
		exec_cmd_ve(cmd, path);
	}
	else
		exec_builtin(cmd);
	return (strarray_free(built), 0);
}
