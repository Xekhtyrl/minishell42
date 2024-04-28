/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:20:36 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/28 16:25:54 by gfinet           ###   ########.fr       */
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
		if (tmp->var
			&& ft_strncmp(tmp->var, "PATH",ft_strlen(tmp->var)))
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

int exec_cmd_ve(t_input *cmd, char *path)
{
	(void)cmd;
	printf("%s\n", path);

	return (1);
}

int exec_builtin(t_input *cmd, int *pipe[2])
{
	size_t size;
	char **built;

	built = ft_split("echo cd pwd export unset env exit", ' ');
	size = ft_strlen(cmd->token);
	
	if (ft_strlen("echo") != size || ft_strncmp(cmd->token, "echo", size))
		return (strarray_free(built), 0);
	if (pipe[0])
		printf("%d", pipe[0][0]);
	return (1);
}

int	in_list(char *str,char **lst)
{
	int		i;
	size_t	size;

	i = 0;
	size = ft_strlen(str);
	if (ft_strlen(lst[i]) < ft_strlen(str))
		size = ft_strlen(lst[i]);
	while (lst[i] && ft_strncmp(str, lst[i], size))
	{
		size = ft_strlen(str);
		if (ft_strlen(lst[i]) < ft_strlen(str))
			size = ft_strlen(lst[i]);
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

	built = ft_split("echo cd pwd export unset env exit", ' ');
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

int	execute_command(t_env *envp, t_input *cmd, int *pipe[2])
{
	char	*path = 0;
	t_input *tmp;
	
	(void)envp;
	(void)pipe;
	tmp = cmd;
	if (!trad_input(cmd))
		return (close_pipes(pipe, ft_lstsize((t_list *)cmd)),
			send_error(-1), 0);
	while (tmp)
	{
		if (tmp->type == WORD_TK)
		{
			path = get_cmd_path(envp, tmp);
			if (path == 0)
				return (close_pipes(pipe, ft_lstsize((t_list *)cmd)), -1); //error path
			exec_cmd_ve(tmp, path);
		}
		else if (tmp->type == BUILT_TK)
			exec_builtin(cmd, pipe);
		tmp = tmp->next;
	}
	close_pipes(pipe, ft_lstsize((t_list *)cmd));
	return (0);
}



