/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:47:48 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/05 18:34:27 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int *get_fd_infiles(t_input *input, int size)
{
	t_input		*tmp;
	int			*fd;
	int			i;

	i = 0;
	fd = malloc(sizeof(int) * size);
	if (!fd)
		return (0);
	tmp = input;
	while (i < size)
	{
		fd[i] = 0;
		if (tmp)
		{
			fd[i] = open_infile(tmp->arg);
			// printf("fdin[%d] = %d\n",i,  fd[i]);
			if (fd[i] == -1)
				send_error(-2);
			tmp = tmp->next;
		}
		i++;
	}
	return (fd);
}

int *get_fd_outfiles(t_input *input, int size)
{
	t_input		*tmp2;
	int			*fd;
	int			i;

	i = 0;
	fd = malloc(sizeof(int) * size);
	if (!fd)
		return (0);
	tmp2 = input;
	while (i < size)
	{
		fd[i] = 1;
		if (tmp2)
		{
			fd[i] = open_outfile(tmp2->arg);
			// printf("fdout[%d] = %d\n", i, fd[i]);
			if (fd[i] == -1)
				send_error(-3);
			tmp2 = tmp2->next;
		}
		i++;
	}
	return (fd);
}

int open_outfile(t_arg_lst *tmp)
{
	int fd;

	fd = 1;
	while (tmp && tmp->next && fd != -1)
	{
		if (tmp->type == 15)
		{
			if (fd != 1 && fd != -1)
				close(fd);
			if (tmp->next && tmp->next->type == SPACE_TK)
				tmp = tmp->next;
			// printf("tok out%s\n", tmp->next->token);
			fd = open(tmp->next->token, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		}
		tmp = tmp->next;
	}
	if (fd == -1)
		ft_printf("\"%s\" ", tmp->next->token);
	return (fd);
}

int open_infile(t_arg_lst *tmp)
{
	int fd;

	fd = 0;
	while (tmp && tmp->next && fd != -1)
	{
		if (tmp->type == READ_TK)
		{
			if (tmp->next && tmp->next->type == SPACE_TK)
				tmp = tmp->next;
			if (fd != 0 && fd != -1)
				close(fd);
			// printf("tok in %s\n", tmp->next->token);
			fd = open(tmp->next->token, O_RDONLY);
		}
		tmp = tmp->next;
	}
	if (fd == -1)
		ft_printf("\"%s\" ", tmp->next->token);
	return (fd);
}

int **fill_fd(t_input *input, int size)
{
	int i;
	int **pipe_fd;

	i = 0;
	pipe_fd = malloc(sizeof(int*) * size);
	if (!pipe_fd)
		return (0);
	while (i < size)
	{
		pipe_fd[i] = malloc(sizeof(int) * 2);
		if (!pipe_fd[i])
			return (0);
		pipe_fd[i][1] = open_outfile(input->arg);
		if (pipe_fd[i][1]== -1)
			return (0);
		pipe_fd[i][0] = open_infile(input->arg);
		if (pipe_fd[i][0] == -1)
			return (0);
		i++;
		input = input->next;
	}
	return (pipe_fd);
}
