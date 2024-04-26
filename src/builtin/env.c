/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:21:14 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/26 21:06:29 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_shell_lvl(t_env	**envp)
{
	int	n;

	n = 0;
	while (*envp)
	{
		if (!ft_strncmp((*envp)->var, "SHLVL", 5))
		{
			n = ft_atoi((*envp)->content);
			if (n >= 999)
				(*envp)->content = ft_strdup("");
			else if (n < 0)
				(*envp)->content = ft_strdup("0");
			else
				(*envp)->content = ft_itoa(n + 1);
			break ;
		}
	}
}

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
	start = NULL;
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
		envp++;
	}
	sort_lst(&start);
	return (start);
}

void	ft_env(t_env *envp)
{
	if (!envp)
		return ;
	while (envp)
	{
		if (envp->flag != 2)
			printf("%s=%s\n", envp->var, envp->content);
		envp = envp->next;
	}
}