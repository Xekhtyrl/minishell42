/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:20:36 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/24 20:54:31 by gfinet           ###   ########.fr       */
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
	(void)cmd;
	(void)path;
	return 1;
}

int in_list(char *str,char **lst)
{
	int i;

	i = 0;
	while (ft_strncmp(str, lst[i], ft_strlen(lst[i] + 1)))
		i++;
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

int	execute_command(char **envp, t_input *cmd, int pipe[2])
{
	char	*path = 0;
	t_input *tmp;
	
	(void)envp;
	(void)pipe;
	tmp = cmd;
	while (tmp)
	{
		if (tmp->type == WORD_TK)
		{
			//path = get_cmd_path(envp, tmp);
			if (path == 0)
				return (-1); //error path
			exec_cmd_ve(tmp, path);
		}
		else if (tmp->type == BUILT_TK)
			//exec_builtin(cmd);
		tmp = tmp->next;
	}
	return (0);
}



