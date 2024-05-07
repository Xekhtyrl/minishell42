/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:37:04 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/07 15:08:34 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// This function check some of the validity and / or information of the arg
// and send an int based on the info it could gather(valid or not and if +/=/$)
static int	checkarg(char *arg)
{
	int	flag;
	int	i;

	i = 0;
	flag = 0;
	if (arg[0] == '\"')
		flag = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			flag += 4;
		else if (arg[i] == '+')
			return (printf("export: `%s': not a valid identifier", arg), -1);
		else if (ft_isdigit(arg[0]) || !(ft_isalnum(arg[i]) || arg[i] == '_'
				|| arg[i] == '\"' || arg[i] == '\''))
			return (printf("export: `%s': not a valid identifier", arg), -1);
		i++;
	}
	if (arg[i] == '=')
		flag += 2;
	return (flag);
}

static void	print_no_arg(t_env *envp)
{
	sort_lst(&envp);
	while (envp)
	{
		if ((envp)->content)
			printf("declare -x %s=\"%s\"\n", envp->var, envp->content);
		else
			printf("declare -x %s\n", envp->var);
		envp = envp->next;
	}
}

static char	*combine_arg(t_arg_lst *arg)
{
	char	*str;

	str = NULL;
	while (arg && arg->type != SPACE_TK)
	{
		if (arg->token[0] == '\'')
			arg->token = ft_strtrim(arg->token, "\'");
		else if (arg->token[0] == '\"')
			arg->token = ft_strtrim(arg->token, "\"");
		str = ft_stradd(str, arg->token);
		arg = arg->next;
	}
	return (str);
}

static void	exporto_patronum(t_env *envp, t_arg_lst *arg, int flag)
{
	char	*var;
	char	*content;

	if (arg->token[0] == '\'')
		arg->token = ft_strtrim(arg->token, "\'");
	else if (arg->token[0] == '\"')
		arg->token = ft_strtrim(arg->token, "\"");
	var = ft_substr(arg->token, 0, ft_strleng(arg->token, '='));
	if (flag > 0 && ft_strchr(arg->token, '='))
		content = ft_strchr(arg->token, '=') + 1;
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
