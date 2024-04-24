/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:47:48 by gfinet            #+#    #+#             */
/*   Updated: 2024/04/24 22:18:44 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



int open_outfile(t_arg_lst *tmp)
{
	int fd;

	fd = 0;
	while (tmp && tmp->next && fd != -1)
	{
		tmp = tmp->next;
		if (tmp->type == 15 && tmp->next)
		{
			if (fd != 0)
				close(fd);
			if (tmp->next && tmp->next->type == 20)
				tmp = tmp->next;
			fd = open(tmp->next->token, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		}
	}
	if (fd == -1)
		ft_printf("\"%s\" ", tmp->next->token);
	return (fd);
}

int *get_fd_outfiles(t_input *input, int size)
{
	t_arg_lst	*tmp;
	t_input		*tmp2;
	int			*fd;
	int			i;

	i = 0;
	if (input->arg)
		tmp = input->arg;
	else
		return (0);
	fd = malloc(sizeof(int) * size);
	if (!fd)
		return (0);
	tmp2 = input;
	while (tmp2 && i < size)
	{
		fd[i] = open_outfile(tmp2->arg);
		if (fd[i] == -1)
			send_error(-3);
		i++;
		tmp2 = tmp2->next;
	}
	return (fd);
}

int open_infile(t_arg_lst *tmp)
{
	int fd;

	fd = 0;
	while (tmp && tmp->next && fd != -1)
	{
		tmp = tmp->next;
		if (tmp->type == READ_TK)
		{
			if (tmp->next && tmp->next->type == 20)
				tmp = tmp->next;
			if (fd != 0 && fd)
				close(fd);
			fd = open(tmp->next->token, O_RDONLY);
		}
	}
	if (fd == -1)
		ft_printf("\"%s\" ", tmp->next->token);
	return (fd);
}

int *get_fd_infiles(t_input *input, int size)
{
	t_arg_lst	*tmp;
	t_input		*tmp2;
	int			*fd;
	int			i;

	i = 0;
	if (input->arg)
		tmp = input->arg;
	else
		return (0);
	fd = malloc(sizeof(int) * size);
	if (!fd)
		return (0);
	tmp2 = input;
	while (tmp2 && i < size)
	{
		fd[i] = open_infile(tmp2->arg);
		if (fd[i] == -1)
			send_error(-2);
		i++;
		tmp2 = tmp2->next;
	}
	return (fd);
}

int fill_fd(int *pipe[2], t_input *input)
{
	int i;
	int size;

	i = 0;
	size = ft_lstsize((t_list *)input);
	pipe[1] = get_fd_outfiles(input, size);
	if (!pipe[1])
		return (0);
	pipe[0] = get_fd_infiles(input, size);
	if (!pipe[0])
		return (0);
	return (1);
}
