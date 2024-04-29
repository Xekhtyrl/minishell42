/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 23:43:00 by Gfinet            #+#    #+#             */
/*   Updated: 2024/04/29 20:17:44 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	mini_cls_fd(int fd1, int fd2, int fd3)
{
	if (close(fd1) == -1)
		perror("close1");
	if (close(fd2) == -1)
		perror("close2");
	if (close(fd3) == -1)
		perror("close3");
}

int uni_dup(int fd_in, int fd_out)
{
	if (fd_in > 0)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			close(fd_in);
			return (-1);
		}
	}
	if (fd_out > 1)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
		{
			close(fd_out);
			return (-1);
		}
	}
	return (1);
}

int	mini_dup(int *fd_in_out[2], int cur)
{
	int prev = cur - 1;

	if (cur == 0)
		uni_dup(fd_in_out[0][0], fd_in_out[0][1]);
	else
	{
		if (fd_in_out[prev][1] == 1 && fd_in_out[cur][1] == 0)
		{
			if (uni_dup(fd_in_out[prev][1], fd_in_out[cur][1]) == -1)
				return (-1);
			else
				mini_cls_fd(fd_in_out[prev][1], fd_in_out[cur][0],
					fd_in_out[cur][1]);
		}
		else if (fd_in_out[cur][0] > 1 && fd_in_out[cur][1] > 1)
		{
			if (uni_dup(fd_in_out[cur][0], fd_in_out[cur][1]) == -1)
				return (-1);
			else
				mini_cls_fd(fd_in_out[cur][0], fd_in_out[cur][1], 0);
		}
	}
	return (1);
}
