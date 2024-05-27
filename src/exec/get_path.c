/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:50:34 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/27 21:28:40 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_our_path(t_env *envp)
{
	char	**path;
	t_env	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (tmp->var && !ft_strncmp(tmp->var, "PATH", ft_strlen(tmp->var)))
		{
			path = ft_split(tmp->content, ':');
			if (!path)
				return (send_error(MALLOC_ERR), NULL);
			return (path);
			strarray_free(path);
		}
		tmp = tmp->next;
	}
	return (0);
}

char	*get_cmd_path(t_env *envp, t_input *input)
{
	char	**path;
	char	*cmd;
	char	*cm_path;
	int		i;

	i = -1;
	path = get_our_path(envp);
	if (!path && access(input->token, F_OK | X_OK) == 0)
		return (ft_strdup(input->token));
	else if (!path)
		return (send_error(-1), NULL);
	cmd = ft_strjoin("/", input->token);
	while (path && path[++i])
	{
		cm_path = ft_strjoin(path[i], cmd);
		if (access(cm_path, F_OK | R_OK) == 0)
			return (strarray_free(path), free(cmd), cm_path);
		free(cm_path);
	}
	if (access(input->token, F_OK | X_OK) == 0)
		return (strarray_free(path), free(cmd), ft_strdup(input->token));
	return (strarray_free(path), free(cmd), NULL);
}
