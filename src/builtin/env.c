/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:21:14 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/01 22:39:38 by lvodak           ###   ########.fr       */
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
		return (str);
	i = start + 1;
	new = ft_substr(str, 0, start);
	while (str[i] && ft_isalnum(str[i]))
		i++;
	tmp = ft_substr(str, start+1, i - start - 1);
	new = ft_stradd(new, get_env_var(envp, tmp));
	tmp = ft_substr(str, i, ft_strlen(str + i));
	new = ft_stradd(new, tmp);
	free(tmp);
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
	// printf("%s\n", envp->content);
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
	ft_lstadd_back((t_list **)envp, (t_list *)create_env_node("HOME", ft_substr(str, 0, i), 3,
		(t_env *)ft_lstlast((t_list *)*envp)));
}

void	check_absent_envar(t_env **envp)
{
	t_env	*start;
	int		flag;

	start = *envp;
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
	if (!(flag % 2) || !flag)
		ft_lstadd_back((t_list **)envp, (t_list *)create_env_node("PWD", getcwd(NULL, 0), 3,
			(t_env *)ft_lstlast((t_list *)*envp)));
	if (!(flag == 2 || flag == 3 || flag == 6 || flag == 7))
		ft_lstadd_back((t_list **)envp, (t_list *)create_env_node("OLDPWD", NULL, 0,
			(t_env *)ft_lstlast((t_list *)*envp)));
	if (flag < 4)
		ft_lstadd_back((t_list **)envp, (t_list *)create_env_node("SHLVL", "0", 0,
			(t_env *)ft_lstlast((t_list *)*envp)));
	set_home_var(envp);
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
		var = ft_substr(*envp, 0, ft_strlen(*envp)
				- ft_strlen(ft_strchr(*envp, '=')));
		new = create_env_node(var, ft_strchr(*envp, '=') + 1, 0, prev);
		ft_lstadd_back((t_list **)&start, (t_list *)new);
		prev = new;
		if (ft_strlen(var) > (size_t)len)
			len = ft_strlen(var);
		envp++;
	}
	check_absent_envar(&start);
	while (start && start->prev)
		start = start->prev;
	sort_lst(&start);
	return (start);
}

void	ft_env(t_env *envp)
{
	create_new_envar("_", "/usr/bin/env", 0, envp);
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