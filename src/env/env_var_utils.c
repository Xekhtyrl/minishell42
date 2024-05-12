/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:40:58 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/12 19:03:21 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	replace_or_append(char *var, char *content, int append, t_env *env)
{
	while (env)
	{
		if (!ft_strncmp(env->var, var, ft_strlen(var)))
		{
			if (append)
			{
				env->content = ft_stradd(env->content, content);
				env->flag = 3;
			}
			else
			{
				if (env->flag == 3)
					free(env->content);
				env->content = content;
			}
			return (1);
		}
		if (!env->next)
			break ;
		env = env->next;
	}
	return (0);
}

void	create_new_envar(char *var, char *content, int append, t_env *envp)
{
	t_env	*prev;

	if (replace_or_append(var, content, append, envp))
		return ;
	prev = (t_env *)ft_lstlast((t_list *)envp);
	ft_lstadd_back((t_list **)&envp, (t_list *)create_env_node(var, content,
			1 + !(content), prev));
}

char	*replace_str_env_var(char *str, t_env *envp)
{
	int		start;
	int		i;
	char	*new;
	char	*tmp;

	i = 0;
	start = 0;
	new = ft_strdup("");
	while (str[i])
	{
		while (str[i] && str[i] != '$')
			i++;
		tmp = ft_substr(str, start, (i) - start);
		if (str[i] == '$')
		{
			start = ++i;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_') && str[i] != '$')
				i++;
			tmp = ft_stradd(tmp, get_env_var(envp, ft_substr(str, start, i - start)));
			start = i;
		}
		new = ft_stradd(new, tmp);
		free(tmp);
	}
	return (free(str), new);
}

char	*get_env_var(t_env *envp, char *var)
{
	if (var && var[0] == '?')
		return (NULL);// var globale
	else
	{
		while (envp)
		{
			if (!ft_strncmp(envp->var, var, ft_strlen(envp->var)))
				break ;
			envp = envp->next;
		}
	}
	free (var);
	if (!envp)
		return (0);
	return (envp->content);
}
