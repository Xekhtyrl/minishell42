/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:16:11 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/07 15:11:02 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*trim_quote(char *str)
{
	char	*new;

	if (str[0] == '\'')
		new = ft_strtrim(str, "\'");
	else if (str[0] == '\"')
		new = ft_strtrim(str, "\"");
	else
		new = ft_strdup(str);
	return (new);
}

static int	check_n_arg(t_arg_lst *arg, int *flag)
{
	char	*str;
	int		i;

	i = 0;
	if (arg->type != WORD_TK)
		return (1);
	str = trim_quote(arg->token);
	if (!str)
		return (0);
	if (str[i++] != '-')
		return (free(str), 0);
	while (str[i])
		if (str[i++] != 'n')
			return (free(str), 0);
	if (arg->next && arg->next->type != SPACE_TK)
		return (free(str), 0);
	*flag = 1;
	return (free(str), 1);
}

int	ft_echo(t_arg_lst *arg)
{
	int	flag;

	flag = 0;
	while (arg)
	{
		if (!check_n_arg(arg, &flag))
			break ;
		if (arg->type == HEREDOC_TK)
			arg = arg->next;
		arg = arg->next;
	}
	while (arg && arg->token)
	{
		if (arg->token[0] == '\'')
			arg->token = ft_strtrim(arg->token, "\'");
		else if (arg->token[0] == '\"')
			arg->token = ft_strtrim(arg->token, "\"");
		ft_putstr_fd(arg->token, 1);
		arg = arg->next;
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
	return (1);
}
