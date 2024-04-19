/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipes_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 21:58:37 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/19 15:52:35 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_pipes(t_pipes *pipes)
{
	int	i;
	int	j;

	i = pipes->p_nb;
	while (--i >= 0)
	{
		j = 0;
		if (access(pipes->pipe[i].cmd[0], F_OK)
			|| !access(pipes->pipe[i].cmd[0], W_OK))
			free(pipes->pipe[i].path);
		while (pipes->pipe[i].cmd[j])
			free(pipes->pipe[i].cmd[j++]);
		free(pipes->pipe[i].cmd);
	}
	free(pipes->id);
	free(pipes->pipe);
}
