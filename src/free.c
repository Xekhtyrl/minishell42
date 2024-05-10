/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:14:05 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/10 20:14:29 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_pipes(int **pipe, int size)
{
	int	i;

	i = 0;
	while (i < size && pipe[i])
	{
		printf("%d %d\n", pipe[i][0], pipe[i][1]);
		if (pipe[i][0] > 0)
			close(pipe[i][0]);
		if (pipe[i][1] > 1)
			close(pipe[i][1]);
		free(pipe[i]);
		i++;
	}
	free(pipe);
}

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
		errno = 5;
		perror("bad argument");
	}
	return (1);
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
		send_error2(flag);
	return (errno);
}

void	mini_cls_fd(int fd1, int fd2)
{
	printf("fd1 = %d\n", fd1);
	printf("fd2 = %d\n", fd2);
	if (fd1 > 1 && printf("close 1 = %d\n", fd1) && close(fd1) == -1)
		perror("close1");
	if (fd2 > 2 && printf("close 2 = %d\n", fd2) && close(fd2) == -1)
		perror("close2");
}

void	multi_array_free(char **str1, char *str2)
{
	if (str1)
		strarray_free(str1);
	if (str2)
		free(str2);
}
