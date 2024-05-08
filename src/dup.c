/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 23:43:00 by Gfinet            #+#    #+#             */
/*   Updated: 2024/05/07 18:48:09 by gfinet           ###   ########.fr       */
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

int check_next_pipe(int *fd_in_out[2], int cur, t_cmd_info *inf)
{
	if (cur == inf->size - 1)
		return (0);
	if (fd_in_out[cur + 1][0] == 0 && fd_in_out[cur][1] == 1)
		return (1);
	return (1);
}

int pipe_heredoc(int *fd_in_out[2], int cur, t_arg_lst *arg)
{
	int p[2];
	t_arg_lst *tmp;

	if (pipe(p) < 0)
		return (send_error(-6), 0);
	tmp = arg;
	while (tmp && tmp->type != HEREDOC_TK)
		tmp = tmp->next;
		printf("pipe = %d %d\n", p[0], p[1]);
	ft_putstr_fd(tmp->token, p[1]);
	close(p[1]);
	// if (fd_in_out[cur][0] > 2)
	// 	close(fd_in_out[cur][0]);
	fd_in_out[cur][0] = p[0];
	return (1);
}

int	mini_dup(int *fd_in_out[2], int cur, t_cmd_info *inf, t_arg_lst *arg)
{
	if (detect_token(arg, HEREDOC_TK))
	{
		printf("HERE\n");
		if ((cur == 0 && fd_in_out[cur][0] == 0) || (cur > 0 && fd_in_out[cur][0]))
			pipe_heredoc(fd_in_out, cur, arg); // pipe et heredoc
	}
	printf("pipe in  : %d\n", fd_in_out[cur][0]);
	printf("pipe out : %d\n", fd_in_out[cur][1]);
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
	close(inf->pipe[0]);
	close(inf->pipe[1]);
	return (1);
}
