/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_env_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 23:20:57 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/13 23:21:19 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_shell_lvl(t_env	*envp)
{
	int	n;

	n = 0;
	while (envp)
	{
		if (!ft_strncmp((envp)->var, "SHLVL", 5))
		{
			n = ft_atoi((envp)->content);
			free(envp->content);
			if (n == 999)
				(envp)->content = ft_strdup("");
			else if (n > 999)
				(envp)->content = ft_strdup("1");
			else if (n < 0)
				(envp)->content = ft_strdup("0");
			else
				(envp)->content = ft_itoa(n + 1);
			break ;
		}
		envp = envp->next;
	}
}
