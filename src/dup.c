/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 23:43:00 by Gfinet            #+#    #+#             */
/*   Updated: 2024/05/03 20:36:03 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	mini_cls_fd(int fd1, int fd2)
{
	printf("fd1 = %d\n", fd1);
	printf("fd2 = %d\n", fd2);
	if (fd1 > 1 && printf("close 1 = %d\n", fd1) && close(fd1) == -1)
		perror("close1");
	if (fd2 > 2 && printf("close 2 = %d\n", fd2) && close(fd2) == -1)
		perror("close2");
}

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

int check_next_pipe(int *fd_in_out[2], int cur, t_cmd_info *inf)
{
	if (cur == inf->size - 1)
		return (0);
	if (fd_in_out[cur + 1][0] == 0 && fd_in_out[cur][1] == 1)
		return (1);
	return (1);
}

int	mini_dup(int *fd_in_out[2], int cur, t_cmd_info *inf)
{
	if (fd_in_out[cur][0] > 1 && fd_in_out[cur][1] > 1) //infile + outfile
	{
		if (uni_dup(fd_in_out[cur][0], fd_in_out[cur][1]) == -1)
			return (-1);
	}
	else if (fd_in_out[cur][0] == 0 && fd_in_out[cur][1] > 1) // outfile
	{
		if (uni_dup(0, fd_in_out[cur][1]) == -1)
			return (-1);
	}
	else if (fd_in_out[cur][0] > 0 && fd_in_out[cur][1] == 1) // infile + stdout
	{
		if (uni_dup(fd_in_out[cur][0], 0) == -1)
			return (-1);
	}
	if (check_next_pipe(fd_in_out, cur, inf))
		return (mini_dup2(fd_in_out, cur, inf));
	return (1);
}

int mini_dup2(int *fd_in_out[2], int cur, t_cmd_info *inf)
{
	if (fd_in_out[cur][0] > 0 && fd_in_out[cur][1] == 1) // infile + pipe
	{
		if (uni_dup(fd_in_out[cur][0], inf->pipe[1]) == -1)
			return (-1);
	}
	else if (fd_in_out[cur][0] == 0 && fd_in_out[cur][1] == 1) //just pipe
	{
		if (uni_dup(fd_in_out[cur][0], inf->pipe[1]) == -1)
			return ( -1);
	}
	return (1);
}
