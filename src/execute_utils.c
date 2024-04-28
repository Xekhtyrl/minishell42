/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:47:24 by gfinet            #+#    #+#             */
/*   Updated: 2024/04/28 22:07:15 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	in_list(char *str,char **lst)
{
	int		i;
	size_t	size;

	i = 0;
	size = ft_strlen(str);
	while (lst[i] && ft_strncmp(str, lst[i], size))
	{
		size = ft_strlen(str);
		i++;
	}
	if (!lst[i])
		return (0);
	return (1);
}

int trad_input(t_input *cmd)
{
	t_input *tmp;
	char **built;

	built = ft_split("cd pwd env echo exit unset export", ' ');
	if (!built)
		return (0);
	tmp = cmd;
	while (tmp)
	{
		if (in_list(tmp->token, built))
			tmp->type = BUILT_TK;
		tmp = tmp->next;
	}
	return (strarray_free(built), 1);
}

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

char *get_cmd_path(t_env *envp, t_input *input)
{
	char	**path;
	char	*cmd;
	char	*cm_path;
	int		i;
	
	i = -1;
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

void	mini_cls_fd(int fd1, int fd2, int fd3)
{
	if (close(fd1) == -1)
		perror("close1");
	if (close(fd2) == -1)
		perror("close2");
	if (close(fd3) == -1)
		perror("close3");
}
