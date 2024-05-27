/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:17:12 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/27 22:59:57 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parse_error(char *s)
{
	int	i;
	int	j;

	i = closed_quotes(s);
	if (i == 124 || i == '\'' || i == '\"')
		return (print_parse_message(i, 0), 1);
	j = -1;
	while (s[++j])
	{
		if ((s[j] == '>' && s[j + 1] == '<'))
			return (print_parse_message(s[j + 1], 0), 1);
		else if (s[j] == '>' || s[j] == '<')
		{
			i = j;
			if (s[++i] == s[j])
				i++;
			while (s[i] && is_white_space(s[i]))
				i++;
			if ((!s[i] || s[i] == '<' || s[i] == '>') && !(s[i - 1] == '<'
					&& s[i] == '>'))
				return (print_parse_message(s[j], s[j + 1]), 1);
		}
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
