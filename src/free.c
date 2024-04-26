/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:14:05 by gfinet            #+#    #+#             */
/*   Updated: 2024/04/26 22:58:07 by Gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void close_pipes(int *pipe[2], int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (pipe[0] && pipe[0][i] > 0)
			close(pipe[0][i]);
		if (pipe[1] && pipe[1][i] > 0)
			close(pipe[1][i]);
		i++;
	}
}

void strarray_free(char **built)
{
	int i;

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
