/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:37:04 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/29 17:23:35 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// This function check some of the validity and / or information of the arg
// and send an int based on the info it could gather(valid or not and if +/=/$)
static int	checkarg(char *arg)
{
	int		flag;
	int		i;
	char	*err;

	i = 0;
	flag = 0;
	err = ft_substr(arg, 0, ft_strleng(arg, '='));
	if (arg[0] == '\"')
		flag = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (i && arg[i] == '+' && arg[i + 1] == '=')
			flag += 4;
		else if (arg[i] == '+')
			return (printf("export: `%s': not a valid identifier\n", err),
				free(err), -1);
		else if (ft_isdigit(arg[0]) || !(ft_isalnum(arg[i]) || arg[i] == '_'
				|| arg[i] == '\"' || arg[i] == '\''))
			return (printf("export: `%s': not a valid identifier\n", err),
				free(err), -1);
		i++;
	}
	if (arg[i] == '=')
		flag += 2;
	return (free(err), flag);
}

static void	print_no_arg(t_env *envp)
{
	sort_lst(&envp);
	while (envp)
	{
		if (ft_strncmp(envp->var, "_", ft_strlen(envp->var)))
		{
			if ((envp)->content)
				printf("declare -x %s=\"%s\"\n", envp->var, envp->content);
			else
				printf("declare -x %s\n", envp->var);
		}
		envp = envp->next;
	}
	free_env(&envp);
	exit(0);
}

static char	*combine_arg(t_arg_lst *arg)
{
	char		*str;
	char		*tmp;
	t_arg_lst	*start;

	str = NULL;
	tmp = NULL;
	start = arg;
	while (arg && arg->type != SPACE_TK)
	{
		if (arg->token[0] == '\'')
			tmp = ft_strtrim(arg->token, "\'");
		else if (arg->token[0] == '\"')
			tmp = ft_strtrim(arg->token, "\"");
		else
			tmp = ft_strdup(arg->token);
		free(arg->token);
		arg->token = tmp;
		str = ft_stradd(str, arg->token);
		arg = arg->next;
	}
	free(start->token);
	return (str);
}

static void	exporto_patronum(t_env *envp, t_arg_lst *arg, int flag)
{
	char	*var;
	char	*content;
	char	*tmp;

	tmp = NULL;
	g_ret_val = 0;
	if (arg->token[0] == '\'')
		tmp = ft_strtrim(arg->token, "\'");
	else if (arg->token[0] == '\"')
		tmp = ft_strtrim(arg->token, "\"");
	if (tmp)
	{
		free(arg->token);
		arg->token = tmp;
		tmp = NULL;
	}
	if (flag < 4)
		var = ft_substr(arg->token, 0, ft_strleng(arg->token, '='));
	else
		var = ft_substr(arg->token, 0, ft_strleng(arg->token, '+'));
	if (flag > 0 && ft_strchr(arg->token, '='))
		content = ft_strdup(ft_strchr(arg->token, '=') + 1);
	else
		content = NULL;
	create_new_envar(var, content, (flag >= 4), envp);
}

void	ft_export(t_arg_lst *arg, t_env *envp, int flag)
{
	if (flag)
		print_exporto_patronum();
	if (!arg)
		print_no_arg(envp);
	flag = 0;
	while (arg)
	{
		while (arg && arg->type != WORD_TK)
			arg = arg->next;
		if (!arg)
			break ;
		if (!ft_strncmp(arg->token, "_", ft_strlen(arg->token))
			|| arg->type == SPACE_TK)
			arg = arg->next;
		if (arg->next && arg->next->type != SPACE_TK)
			arg->token = combine_arg(arg);
		if (!arg)
			break ;
		flag = checkarg(arg->token);
		if (flag > -1)
			exporto_patronum(envp, arg, flag);
		while (arg && arg->type != SPACE_TK)
			arg = arg->next;
	}
}
