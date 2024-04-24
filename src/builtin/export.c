/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:37:04 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/23 18:25:20 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_export(char *var, char *content, t_env **envp)
{
	int	i;

	i = -1;
	while (var[++i])
		if (ft_isdigit(var[i]))
			return (ft_putstr_fd("Unvalid variable name\n", 2));
	if (content)
		ft_lstadd_back((t_list **)envp, (t_list *)create_env_node(var, content));
	else
	{
		while (*envp)
		{
			printf("declare -x %s=%s\n");
		}
	}
}
