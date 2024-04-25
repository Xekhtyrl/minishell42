/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:20:36 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/25 16:22:15 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_path(char **envp)
{
	char	*temp;
	char	**path;
	int		i;

	i = -1;
	while (envp && envp[++i])
	{
		temp = ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i]));
		if (temp)
		{
			path = ft_split(temp + 5, ':');
			if (!path)
				return (send_error(-1), NULL);
			return (path);
			strarray_free(path);
		}
	}
	return (0);
}

char *get_cmd_path(char **envp, t_input *input)
{
	char	**path;
	char	*cmd;
	char	*cm_path;
	int		i;
	
	i = -1;
	path = get_path(envp);
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

int	execute_command(char **envp, t_input *cmd, int *pipe[2])
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
			;//exec_builtin(cmd);
		tmp = tmp->next;
	}
	close_pipes(pipe, ft_lstsize((t_list *)cmd));
	return (0);
}



