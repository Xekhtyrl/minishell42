/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:13:14 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/18 17:24:22 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	free_arg_lst(t_arg_lst **arg, int flag)
{
	t_arg_lst	*next;

	if (flag != -1)
		return (flag);
	while ((*arg))
	{
		next = (*arg)->next;
		free((*arg)->token);
		free((*arg));
		*arg = next;
	}
	*arg = NULL;
	return (flag);
}

int	free_input(t_input **input)
{
	t_input	*next;

	while (*input)
	{
		next = (*input)->next;
		if ((*input)->token)
			free((*input)->token);
		if ((*input)->arg)
			free_arg_lst(&(*input)->arg, -1);
		free((*input));
		*input = next;
	}
	*input = NULL;
	return (0);
}

void	free_env(t_env **envp)
{
	t_env	*next;

	while (*envp)
	{
		next = (*envp)->next;
		if ((*envp)->var)
			free((*envp)->var);
		if ((*envp)->var)
			free((*envp)->content);
		free((*envp));
		*envp = next;
	}
	*envp = NULL;
}

void	free_tab(char **tabl)
{
	int	i;

	i = -1;
	while (tabl[++i])
		free(tabl[i]);
	free(tabl);
}

void	close_pipes(int **pipe, int size)
{
	int	i;

	i = 0;
	while (i < size && pipe[i])
	{
		if (pipe[i][0] > 0)
			close(pipe[i][0]);
		if (pipe[i][1] > 1)
			close(pipe[i][1]);
		free(pipe[i]);
		i++;
	}
	free(pipe);
}
