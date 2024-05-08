/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:40:58 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/07 14:59:53 by lvodak           ###   ########.fr       */
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
				env->content = ft_strjoin_f(env->content, content, env->flag);
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

	start = ft_strleng(str, '$');
	if (start == (int)ft_strlen(str))
		return (str);
	i = start + 1;
	new = ft_substr(str, 0, start);
	while (str[i] && ft_isalnum(str[i]))
		i++;
	tmp = ft_substr(str, start + 1, i - start);
	new = ft_stradd(new, get_env_var(envp, tmp));
	tmp = ft_substr(str, i, ft_strlen(str + i));
	new = ft_stradd(new, tmp);
	free(tmp);
	return (new);
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
	if (!envp)
		return (0);
	return (envp->content);
}
