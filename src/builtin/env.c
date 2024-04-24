/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:21:14 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/23 21:26:08 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*create_env_node(char *var, char *content, int flag, t_env *prev)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->var = var;
	new->content = content;
	new->flag = flag;
	new->next = NULL;
	new->prev = prev;
	return (new);
}

t_env	*env_lst(char **envp)
{
	t_env	*start;
	t_env	*new;
	t_env	*prev;
	char	*var;
	int		len;

	prev = NULL;
	len = 0;
	while (*envp)
	{
		var = ft_substr(*envp, 0, ft_strlen(*envp) -
				ft_strlen(ft_strchr(*envp, '=')));
		new = create_env_node(var, ft_strchr(*envp, '=') + 1, 0, prev);
		ft_lstadd_back((t_list **)&start, (t_list *)new);
		prev = new;
		if (ft_strlen(var) > (size_t)len)
			len = ft_strlen(var);
	}
	sort_LSD_recursive(&start, NULL, len);
	return (start);
}

void	ft_env(t_env *envp)
{
	if (!envp)
		return ;
	while (envp)
	{
		printf("%s=%s\n", envp->var, envp->content);
		envp = envp->next;
	}
}