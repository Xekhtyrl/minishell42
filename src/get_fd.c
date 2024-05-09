/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:47:48 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/09 15:39:51 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_pipes(int **pipe, int size)
{
	int	i;

	i = 0;
	while (i < size && pipe[i])
	{
		printf("%d %d\n", pipe[i][0], pipe[i][1]);
		if (pipe[i][0] > 0)
			close(pipe[i][0]);
		if (pipe[i][1] > 1)
			close(pipe[i][1]);
		free(pipe[i]);
		i++;
	}
	free(pipe);
}

int	open_outfile(t_arg_lst *tmp)
{
	int	fd;
	int	type;

	fd = 1;
	while (tmp && tmp->next && fd != -1)
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
		tmp = tmp->next;
	}
	return (fd);
}

int	open_infile(t_arg_lst *tmp)
{
	int	fd;

	fd = 0;
	while (tmp && tmp->next && fd != -1)
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
		tmp = tmp->next;
	}
	return (fd);
}

int	**fill_fd(t_input *input, int size)
{
	int	i;
	int	**pipe_fd;

	i = 0;
	pipe_fd = malloc(sizeof(int *) * size);
	if (!pipe_fd)
		return (0);
	while (i < size)
	{
		pipe_fd[i] = malloc(sizeof(int) * 2);
		if (!pipe_fd[i])
			return (0);
		pipe_fd[i][1] = open_outfile(input->arg);
		if (pipe_fd[i][1] == -1)
			return (0);
		pipe_fd[i][0] = open_infile(input->arg);
		if (pipe_fd[i][0] == -1)
			return (0);
		i++;
		input = input->next;
	}
	return (pipe_fd);
}
