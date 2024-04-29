/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 23:43:00 by Gfinet            #+#    #+#             */
/*   Updated: 2024/04/29 18:20:31 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int uni_dup(int fd_in, int fd_out)
{
	if (fd_in > 0)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			mini_cls_fd(fd_in, 0, 0);
			return (-1);
		}
	}
	if (fd_out > 1)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
		{
			mini_cls_fd(fd_out, 0, 0);
			return (-1);
		}
	}
	return (1);
}

int	mini_dup(int *fd_in_out[2], int cur)
{
	int prev = cur - 1;

	if (cur == 0)
		uni_dup(fd_in_out[0][0], fd_in_out[1][0]);
	else
	{
		if (fd_in_out[prev][1] == 1 && fd_in_out[cur][0] == 0)
		{
			if (uni_dup(fd_in_out[1][prev], fd_in_out[1][cur]) == -1)
				return (-1);
			else
				mini_cls_fd(fd_in_out[1][prev], fd_in_out[0][cur],
					fd_in_out[cur][1]);
		}
		else if (fd_in_out[0][cur] > 1 && fd_in_out[1][cur] > 1)
		{
			if (uni_dup(fd_in_out[0][cur], fd_in_out[1][0]) == -1)
				return (-1);
			else
				mini_cls_fd(fd_in_out[0][cur], fd_in_out[1][cur], 0);
		}
	}
	return (1);
}
