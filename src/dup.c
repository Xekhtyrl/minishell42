/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 23:43:00 by Gfinet            #+#    #+#             */
/*   Updated: 2024/04/28 23:43:25 by Gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int uni_dup(int fd_in, int fd_out)
{
	if (fd_in > 0)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			return (-1);
	}
	if (fd_out > 1)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			return (-1);
	}
	return (1);
}

int	mini_dup(int *fd_in_out[2], int n_cmd, int size)
{
	int *prev = 0;
	int *next = 0;
	int pipe_fd[2];

	if (n_cmd == 0 && fd_in_out[0][1] != 1)
		return (uni_dup(fd_in_out[0][0], fd_in_out[0][1]));
	if (size > 1 && fd_in_out[n_cmd][1] == 1)

	if (fd_in_out[n_cmd - 1][1])
	pipe_fd[0] = fd_in_out[n_cmd - 1][1];
	pipe_fd[1] = fd_in_out[n_cmd][1];
	if (*prev == 0 && fd_in_out[n_cmd][0] == 0)
	{
		if (dup2(*prev, STDIN_FILENO) == -1)
			return (-1);
	}
	else if (fd_in_out[n_cmd][0] > 0)
	{
		if (dup2(fd_in_out[n_cmd][0], STDIN_FILENO) == -1)
			return (-1);
	}
	if (*next > 0)
	{
		if (dup2(*next, STDOUT_FILENO))
			return (-1);
	}
	mini_cls_fd(*prev, *next, fd_in_out[n_cmd][0]);
	return (1);
}