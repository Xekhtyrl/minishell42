/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:52:28 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/29 22:34:14 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(t_env	*envp, t_arg_lst *arg)
{
	t_env	*prev;

	prev = NULL;
	if (arg->next)
		ft_unset(envp, arg->next);
	while (envp)
	{
		if (ft_strncmp(arg->token, (envp)->var, ft_strlen(arg->token)))
			break ;
		prev = envp;
		envp = (envp)->next;
	}
	if (envp)
	{
		if (prev)
			prev->next = (envp)->next;
		if (envp->flag == 3)
			free(envp->content);
		prev = envp;
		envp = (envp)->next;
		free(prev);
	}
}
