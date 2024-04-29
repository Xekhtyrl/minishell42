/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:47:24 by gfinet            #+#    #+#             */
/*   Updated: 2024/04/29 19:41:33 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_stradd(char *s1, char const *s2)
{
	size_t		j;
	size_t		i;
	char		*p;

	if (!s1 && !s2)
		return (0);
	p = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	i = 0;
	j = 0;
	if (p == NULL)
		return (free(s1), NULL);
	while (s1 && i < ft_strlen(s1))
	{
		p[i] = s1[i];
		i++;
	}
	free(s1);
	while (s2 && j < ft_strlen(s2))
	{
		p[i + j] = s2[j];
		j++;
	}
	p[i + j] = '\0';
	return (p);
}

char **get_env(t_env *envp)
{
	char *p;
	char **env;

	env = 0;
	p = 0;
	p = ft_stradd(p, envp->var);
	if (envp->content)
	{
		p = ft_stradd(p, " ");
		p = ft_stradd(p, envp->content);
	}
	while (envp)
	{
		p = ft_stradd(p, " ");
		p = ft_stradd(p, envp->var);
		if (envp->content)
		{
			p = ft_stradd(p, "=");
			p = ft_stradd(p, envp->content);
		}
		envp = envp->next;
	}
	env = ft_split(p, ' ');
	free(p);
	return (env);
}

int	in_list(char *str,char **lst)
{
	int		i;
	size_t	size;

	i = 0;
	size = ft_strlen(str);
	while (lst[i] && ft_strncmp(str, lst[i], size))
	{
		size = ft_strlen(str);
		i++;
	}
	if (!lst[i])
		return (0);
	return (1);
}

int trad_input(t_input *cmd)
{
	t_input *tmp;
	char **built;

	built = ft_split("cd pwd env echo exit unset export", ' ');
	if (!built)
		return (0);
	tmp = cmd;
	while (tmp)
	{
		if (in_list(tmp->token, built))
			tmp->type = BUILT_TK;
		tmp = tmp->next;
	}
	return (strarray_free(built), 1);
}

