/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:47:48 by gfinet            #+#    #+#             */
/*   Updated: 2024/04/29 18:21:42 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



int open_outfile(t_arg_lst *tmp)
{
	int fd;

	fd = 1;
	while (tmp && tmp->next && fd != -1)
	{
		if (tmp->type == 15 && tmp->next)
		{
			if (fd != 1 && fd != -1)
				close(fd);
			if (tmp->next && tmp->next->type == SPACE_TK)
				tmp = tmp->next;
			fd = open(tmp->next->token, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		}
		tmp = tmp->next;
	}
	if (fd == -1)
		ft_printf("\"%s\" ", tmp->next->token);
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
			fd = open(tmp->next->token, O_RDONLY);
		}
		tmp = tmp->next;
	}
	if (fd == -1)
		ft_printf("\"%s\" ", tmp->next->token);
	return (fd);
}

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

int fill_fd(int *pipe[2], t_input *input)
{
	int size;

	size = ft_lstsize((t_list *)input);
	//printf("size = %d\n", size);
	pipe[1] = get_fd_outfiles(input, size);
	if (!pipe[1])
		return (0);
	pipe[0] = get_fd_infiles(input, size);
	if (!pipe[0])
		return (0);
	return (1);
}
