/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:52:28 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/23 17:29:43 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(t_env	**envp, char *var)
{
	t_env	*prev;

	prev = NULL;
	while (*envp)
	{
		if (ft_strncmp(var, (*envp)->var, ft_strlen(var)))
			break ;
		prev = *envp;
		*envp = (*envp)->next;
	}
	if (*envp)
	{
		if (prev)
			prev->next = (*envp)->next;
		prev = *envp;
		*envp = (*envp)->next;
		free(prev);
	}
}
