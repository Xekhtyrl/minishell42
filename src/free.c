/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:14:05 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/07 19:51:49 by lvodak           ###   ########.fr       */
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

int	send_error(int flag)
{
	if (flag == -1)
		perror("open error");
	else if (flag == -2)
		perror("read error");
	else if (flag == -3)
		perror("write error");
	else if (flag == -4)
		perror("fork error");
	else if (flag == -5)
		perror("malloc error");
	else if (flag == -6)
		perror("pipe error");
	else if (flag == -7)
	{
		errno = 5;
		perror("bad argument");
	}
	else if (flag == -8)
		perror("access error");
	else if (flag == -9)
		perror("permission error");
	else if (flag == -10)
		perror("PATH not found");
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
