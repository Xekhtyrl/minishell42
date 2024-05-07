/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:52:28 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/07 15:04:13 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset_arg_bis(t_env *prev, t_env *envp)
{
	if (prev)
		prev->next = (envp)->next;
	if ((envp)->flag == 3)
	{
		free((envp)->content);
		(envp)->content = NULL;
	}
	prev = envp;
	envp = (envp)->next;
	(envp)->prev = prev->prev;
	free(prev);
	prev = NULL;
}

void	unset_each_arg(t_env **envp, t_arg_lst *arg)
{
	t_env	*prev;
	t_env	*start;

	prev = NULL;
	start = (*envp)->next;
	while (*envp)
	{
		if (!ft_strncmp(arg->token, (*envp)->var, ft_strlen(arg->token)))
			break ;
		prev = *envp;
		*envp = (*envp)->next;
	}
	if (*envp)
		unset_arg_bis(prev, *envp);
	if (start->prev)
		*envp = start->prev;
	else
		*envp = start;
}

void	ft_unset(t_env **envp, t_arg_lst *arg)
{
	if (!arg)
		return ((void)printf("unset: not enough arguments"));
	while (arg)
	{
		if (!ft_strncmp(arg->token, "_", ft_strlen(arg->token)))
			arg = arg->next;
		if (arg)
		{
			unset_each_arg(envp, arg);
			arg = arg->next;
		}
	}
}
