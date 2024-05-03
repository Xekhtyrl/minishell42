/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:50:34 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/03 15:45:27 by Gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_our_path(t_env *envp)
{
	char	**path;
	t_env	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (tmp->var && !ft_strncmp(tmp->var, "PATH",ft_strlen(tmp->var)))
		{
			path = ft_split(tmp->content, ':');
			if (!path)
				return (send_error(-1), NULL);
			return (path);
			strarray_free(path);
		}
		tmp=tmp->next;
	}
	return (0);
}

char *get_cmd_path(t_input *input, t_env *envp)
{
	char	**path;
	char	*cmd;
	char	*cm_path;
	int		i;
	
	i = -1;
	if (access(input->token, F_OK | R_OK) == 0)
		return (ft_strdup(input->token));
	path = get_our_path(envp);
	if (!path)
		return (send_error(-1), NULL);
	cmd = ft_strjoin("/", input->token);
	while (path && path[++i])
	{
		cm_path = ft_strjoin(path[i], cmd);
		if (access(cm_path, F_OK | R_OK) == 0)
			return (strarray_free(path), free(cmd), cm_path);
		free(cm_path);
	}
	return (strarray_free(path), free(cmd), NULL);
}