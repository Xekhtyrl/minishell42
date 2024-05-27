/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:17:12 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/27 22:05:24 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parse_error(char *str)
{
	int	i;

	i = closed_quotes(str);
	if (!i)
		return (ft_putstr_fd("syntax error near quote left opened\n", 2), 1);
	else if (i == -1)
		return (ft_putstr_fd("syntax error near unexpected token `|'\n", 2), 1);
	else if ((str[0] == '<' || str[0] == '>') && (!str[1] || (str[0] == str[1]
			&& !str[2])))
		return (ft_putstr_fd("syntax error near unexpected token `", 2),
			ft_putchar_fd(str[0], 2), ft_putchar_fd(str[1], 2),
			ft_putstr_fd("'\n", 2), 1);
	while (*str)
	{
		if ((*str == '>' && *(str + 1) == '<'))
			return (ft_putstr_fd("syntax error near unexpected token `", 2),
				ft_putchar_fd(*(str + 1), 2), ft_putendl_fd("'", 2), 1);
		str++;
	}
	return (0);
}

int	choose_split_kind(char *str, int i, t_input **cmd, t_env *envp)
{
	if (str[i] == '|')
		i++;
	else if (str[i] == '<' || str[i] == '>')
		i = split_cmd_redir(cmd, str, i, envp);
	else
		i = split_cmd(cmd, str, i, envp);
	return (i);
}

int	increase_token(t_input **cmd, t_arg_lst *lst, int *token)
{
	t_arg_lst	*tp;

	tp = lst;
	*token = 0;
	while (tp && tp->next)
	{
		if (tp && tp->type == SPACE_TK)
			tp = tp->next;
		if (tp && (tp->type == READ_TK || tp->type == WRITE_TK
				|| tp->type == APPEN_TK || tp->type == HEREDOC_TK))
		{
			if (!*cmd)
				*token = 1;
			tp = tp->next;
		}
		if (tp && (tp->type == 13 || tp->type == 11 || tp->type == 10))
		{
			while (tp && (tp->type == 11 || tp->type == 13 || tp->type == 10))
				tp = tp->next;
			*token += 1;
		}
	}
	if (tp && *token == 2 && tp->type == SPACE_TK)
		*token = 3;
	return (1);
}

int	check_for_empty_arg(t_arg_lst *lst, int i)
{
	t_arg_lst	*tmp;

	tmp = lst;
	if (i == -1)
		return (0);
	if (!lst)
		return (1);
	while (lst->next)
		lst = lst->next;
	if ((lst->token[0] == '\"' || lst->token[0] == '\'') && lst->token[1]
		== lst->token[0])
		lst->type = EMPTY_TK;
	return (1);
}

int	is_valid_cmd(char *str, int i)
{
	if (str[i] == '<' || str[i] == '>' || str[i] == ' ')
		return (0);
	else if ((str[i] == '\"' || str[i] == '\'') && str[i] == str[i + 1]
		&& str[i + 2] != ' ')
		return (0);
	return (1);
}
