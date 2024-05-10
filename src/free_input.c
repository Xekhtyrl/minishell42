/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:13:14 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/10 20:26:57 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_arg_lst(t_arg_lst **arg, int flag)
{
	t_arg_lst	*next;
	
	if (flag == -1)
		return (flag);
	while ((*arg))
	{
		next = (*arg)->next;
		if ((*arg)->type != SPACE_TK)
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
		if ((*envp)->content)
			free((*envp)->content);
		free((*envp));
		*envp = next;
	}
	*envp = NULL;
}
