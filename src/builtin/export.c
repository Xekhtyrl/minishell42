/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:37:04 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/29 00:42:57 by Gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//create a new environment variable by adding it to the end of the struct
//and if the var already exist, it will replace it or append it

int	replace_or_append(char *var, char *content, int append, t_env *envp)
{

	while (envp)
	{
		if (!ft_strncmp(envp->var, var, ft_strlen(var)))
		{
			if (append)
			{
				envp->content = ft_strjoin_f(envp->content, content, envp->flag);
				envp->flag = 3;
			}
			else
			{
				if (envp->flag == 3)
					free(envp->content);
				envp->content = content; 
			}
			return (1);
		}
		if (!envp->next)
			break ;
		envp = envp->next;
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

// This function check some of the validity and / or information of the arg
// and send an int based on the info it could gather(valid or not and if +/=/$)
int	checkarg(char *arg)
{
	int	c;
	int	flag;

	c = 0;
	flag = 0;
	if (arg[0] == '\"')
		flag = 1;
	while (*arg)
	{
		if (ft_isdigit(arg[0]) || !ft_isalnum(*arg))
			return (ft_putstr_fd("Unvalid variable name\n", 2), -1);
		if (*arg == '=' && flag < 2)
		{
			c += 1;
			if (*arg - 1 == '+')
				c += 2;
			flag += 3;
		}
		if (*arg++ == '$' && (flag == 1 || flag == 4))
		{
			c += 4;
			flag = 2;
		}
	}
	return (c);
}

static void	print_no_arg(t_env *envp)
{
	sort_lst(&envp);
	while (envp)
	{
		if ((envp)->content)
			printf("declare -x %s=%s\n", envp->var, envp->content);
		else
			printf("declare -x %s\n", envp->var);
	}
}

void	ft_export(t_arg_lst *arg, t_env *envp)
{
	// int		i;
	// t_env	*prev;

	// parse_envar(arg);
	// i = -1;
	// prev = ft_lstlast((t_list *)*envp);
	// while (var[++i])
	// 	if (ft_isdigit(var[i]))
	// 		return (ft_putstr_fd("Unvalid variable name\n", 2));
	// if (content)
	// 	ft_lstadd_back((t_list **)envp, (t_list *)create_env_node(var, content,
	// 		1 + !(content), prev));
	// else
	// 	sort_lst(envp);
	// 	while (*envp)
	// 	{
	// 		if ((*envp)->content)
	// 			printf("declare -x %s=%s\n");
	// 		else
	// 			printf("declare -x %s=''\n");

	// 	}
	char	*var;
	char	*content;
	int		flag;

	if (!arg)
		print_no_arg(envp);
	while (arg)
	{
		flag = checkarg(arg->token);
		if (flag > -1)
		{
			if (arg->token[0] == '\'' || arg->token[0] == '\"')
				arg->token = ft_strtrim(arg->token, &arg->token[0]);
			var = ft_substr(arg->token, 0, ft_strleng(arg->token, '='));
			if(flag >= 0 && ft_strchr(arg->token, '='))
				content = ft_strchr(arg->token, '=') + 1;
			else
				content = NULL;
			create_new_envar(var, content, (flag == 3 || flag == 7), envp);
		}
		arg = arg->next;
	}
}
