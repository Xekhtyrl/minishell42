/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:21:14 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/29 19:04:52 by gfinet           ###   ########.fr       */
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

char	*replace_str_env_var(char *str, t_env *envp)
{
	int	start;
	int	i;
	char	*new;
	char	*tmp;

	start = ft_strleng(str, '$');
	if (start == (int)ft_strlen(str))
		return (printf("%s\n", "SAME LENGTH"), str);
	i = start;
	new = ft_substr(str, 0, start);
	while (str[i] && !is_white_space(str[i]))
		i++;
	tmp = ft_substr(str, start+1, i - start - 1);
	printf("%i\n%s\n", i - start, tmp);
	new = ft_stradd(new, get_env_var(envp, tmp));
	tmp = ft_substr(str, i, ft_strlen(str + i));
	new = ft_stradd(new, tmp); // souci ici
	free(tmp);
	printf(">>> %s\n", new);
	return (new);
}

char	*get_env_var(t_env *envp, char *var)
{
	// if (var && var[0] == '$')
	// 	var = var + 1;
	if (var && var[0] == '?')
		return (0);  // var globale
	else
	{
		while (envp)
		{
			if (!ft_strncmp(envp->var, var, ft_strlen(var)))
				break ;
			envp = envp->next;
		}
	}
	if (!envp)
		return (0);
	printf("%s\n", envp->content);
	return (envp->content);
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

t_env	*create_simple_env(t_env *start)
{
	t_env	*prev;
	t_env	*new;

	new = create_env_node("OLDPWD", 0, 0, NULL);
	ft_lstadd_back((t_list **)&start, (t_list *)new);
	prev = new;
	new = create_env_node("PWD", getcwd(NULL, 0), 3, prev);
	ft_lstadd_back((t_list **)&start, (t_list *)new);
	prev = new;
	new = create_env_node("SHLVL", "0", 0, prev);
	ft_lstadd_back((t_list **)&start, (t_list *)new);
	return (start);
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
	if (!envp || !*envp)
		return (create_simple_env(start));
	while (*envp)
	{
		var = ft_substr(*envp, 0, ft_strlen(*envp)
				- ft_strlen(ft_strchr(*envp, '=')));
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
	replace_or_append("_", "/usr/bin/env", 0, envp);
	if (!envp)
		return ;
	while (envp)
	{
		if (envp->content)
			printf("%s=%s\n", envp->var, envp->content);
		envp = envp->next;
	}
}

// a faire var d'env avec $