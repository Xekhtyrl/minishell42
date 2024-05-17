/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:47:48 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/17 19:21:25 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_good_pipe(int **pi, int i)
{
	return (pi[i][0] != -1 && pi[i][1] != -1);
}

int	open_outfile(t_arg_lst *tmp, int fd)
{
	int	type;

	if (tmp && tmp->next && fd != -1)
	{
		if (tmp->type == WRITE_TK || tmp->type == APPEN_TK)
		{
			type = tmp->type;
			if (fd != 1 && fd != -1)
				close(fd);
			if (tmp->next && tmp->next->type == SPACE_TK)
				tmp = tmp->next;
			if (type == WRITE_TK)
				fd = open(tmp->next->token, O_WRONLY | O_CREAT | O_TRUNC,
						S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			else
				fd = open(tmp->next->token, O_WRONLY | O_CREAT | O_APPEND,
						S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		}
	}
	return (fd);
}

int	open_infile(t_arg_lst *tmp, int fd)
{
	if (tmp && tmp->next && fd != -1)
	{
		if (tmp->type == READ_TK)
		{
			if (tmp->next && tmp->next->type == SPACE_TK)
				tmp = tmp->next;
			if (fd != 0 && fd != -1)
				close(fd);
			if (tmp->next->type == WORD_TK)
				fd = open(tmp->next->token, O_RDONLY);
		}
		if (tmp->type == HEREDOC_TK && fd > 0)
		{
			close(fd);
			fd = 0;
		}
	}
	return (fd);
}

void	choose_in_out(t_arg_lst **tmp, int ***pipe_fd, int i)
{
	if (in_int_array((*tmp)->type,
			(int []){READ_TK, WRITE_TK, APPEN_TK, HEREDOC_TK}, 4)
		&& (*pipe_fd)[i][1] != -1 && (*pipe_fd)[i][0] != -1)
	{
		if ((*tmp)->type == WRITE_TK || (*tmp)->type == APPEN_TK)
		{
			(*pipe_fd)[i][1] = open_outfile((*tmp), (*pipe_fd)[i][1]);
			if ((*pipe_fd)[i][1] == -1)
				send_error(-1);
		}
		if ((*tmp)->type == READ_TK || (*tmp)->type == HEREDOC_TK)
		{
			(*pipe_fd)[i][0] = open_infile((*tmp), (*pipe_fd)[i][0]);
			if ((*pipe_fd)[i][0] == -1)
				send_error(-1);
		}
	}
	if ((*tmp))
		(*tmp) = (*tmp)->next;
}

int	fill_fd(t_input *input, int size, int ***pipe_fd)
{
	int			i;
	t_arg_lst	*tmp;

	i = 0;
	*pipe_fd = malloc(sizeof(int *) * size);
	if (!*pipe_fd)
		return (0);
	while (i < size)
	{
		(*pipe_fd)[i] = malloc(sizeof(int) * 2);
		(*pipe_fd)[i][0] = 0;
		(*pipe_fd)[i][1] = 1;
		if (!(*pipe_fd)[i])
			return (0);
		tmp = input->arg;
		while (tmp)
			choose_in_out(&tmp, pipe_fd, i);
		i++;
		input = input->next;
	}
	return (1);
}
