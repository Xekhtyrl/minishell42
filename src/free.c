/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:14:05 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/13 18:59:36 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	strarray_free(char **built)
{
	int	i;

	i = 0;
	while (built[i])
	{
		free(built[i]);
		i++;
	}
	free(built);
}

int	send_error2(int flag)
{
	if (flag == ARG_ERR)
	{
		g_ret_val = 5;
		perror("bad argument");
	}
	return (g_ret_val);
}

int	send_error(int flag)
{
	if (flag == OPEN_ERR)
		perror("open error");
	else if (flag == READ_ERR)
		perror("read error");
	else if (flag == WRITE_ERR)
		perror("write error");
	else if (flag == FORK_ERR)
		perror("fork error");
	else if (flag == MALLOC_ERR)
		perror("malloc error");
	else if (flag == PIPE_ERR)
		perror("pipe error");
	else if (flag == ACCESS_ERR)
		perror("access error");
	else if (flag == PERM_ERR)
		perror("permission error");
	else if (flag == PATH_ERR)
		perror("PATH not found");
	else if (flag == CMD_ERR)
		perror("command not found");
	else
		return (send_error2(flag));
	return (g_ret_val);
}

void	mini_cls_fd(int fd1, int fd2)
{
	if (fd1 > 1 && close(fd1) == -1)
		perror("close1");
	if (fd2 > 2 && close(fd2) == -1)
		perror("close2");
}

void	multi_array_free(char **str1, char *str2)
{
	if (str1)
		strarray_free(str1);
	if (str2)
		free(str2);
}
