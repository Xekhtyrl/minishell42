/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:21:14 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/15 18:17:11 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_env *envp)
{
	// replace_or_append("_", "/usr/bin/env", 0, envp);
	if (!envp)
		return ;
	while (envp)
	{
		if (envp->content)
			printf("%s=%s\n", envp->var, envp->content);
		envp = envp->next;
	}
}
