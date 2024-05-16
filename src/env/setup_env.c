/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:39:08 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/16 16:22:55 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*create_env_node(char *var, char *content, int flag, t_env *prev)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (send_error(MALLOC_ERR), NULL);
	new->var = var;
	new->content = NULL;
	if (content)
		new->content = ft_strdup(content);
	new->flag = flag;
	new->next = NULL;
	new->prev = prev;
	return (new);
}

void	set_home_var(t_env **envp)
{
	t_env	*start;
	char	*str;
	int		i;
	int		flag;

	start = *envp;
	i = -1;
	flag = 0;
	while (start && start->next)
	{
		if (!ft_strncmp(start->var, "HOME", ft_strlen(start->var)))
			return ;
		start = start->next;
	}
	str = getcwd(NULL, 0);
	while (str[++i])
	{
		if (str[i] == '/')
			flag += 1;
		if (flag == 3)
			break ;
	}
	ft_lstadd_back((t_list **)envp, (t_list *)create_env_node(ft_strdup("HOME"),
			ft_substr(str, 0, i), 3, (t_env *)ft_lstlast((t_list *)*envp)));
	free(str);
}

void	check_absent_envar2(t_env **env, int flag)
{
	char	*pwd;

	pwd = getcwd(0, 0);
	if (!(flag % 2) || !flag)
		ft_lstadd_back((t_list **)env, (t_list *)create_env_node(ft_strdup
				("PWD"), pwd, 3, (t_env *)ft_lstlast((t_list *)*env)));
	if (!(flag == 2 || flag == 3 || flag == 6 || flag == 7))
		ft_lstadd_back((t_list **)env, (t_list *)create_env_node(ft_strdup
				("OLDPWD"), NULL, 0, (t_env *)ft_lstlast((t_list *)*env)));
	if (flag < 4)
		ft_lstadd_back((t_list **)env, (t_list *)create_env_node(ft_strdup
				("SHLVL"), "0", 0, (t_env *)ft_lstlast((t_list *)*env)));
	free(pwd);
}

void	check_absent_envar(t_env **env)
{
	t_env	*start;
	int		flag;

	start = *env;
	flag = 0;
	while (start && start->next)
	{
		if (!ft_strncmp(start->var, "PWD", ft_strlen(start->var)))
			flag += 1;
		if (!ft_strncmp(start->var, "OLDPWD", ft_strlen(start->var)))
			flag += 2;
		if (!ft_strncmp(start->var, "SHLVL", ft_strlen(start->var)))
			flag += 4;
		start = start->next;
	}
	check_absent_envar2(env, flag);
	replace_or_append(ft_strdup("_"), ft_strdup("/usr/bin/env"), 0, *env);
	set_home_var(env);
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
	while (envp && *envp)
	{
		if (ft_strchr(*envp, '='))
		{
			var = ft_substr(*envp, 0, ft_strleng(*envp, '='));
			new = create_env_node(var, ft_strchr(*envp, '=') + 1, 0, prev);
			if (!new)
				return(free_env(&start), NULL);
			ft_lstadd_back((t_list **)&start, (t_list *)new);
			prev = new;
			if (ft_strlen(var) > (size_t)len)
				len = ft_strlen(var);
		}
		envp++;
	}
	return (check_absent_envar(&start), sort_lst(&start), start);
}
