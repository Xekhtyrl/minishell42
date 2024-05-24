/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:20:26 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/25 00:35:09 by Gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*split_token(char *str, int	*start, char quote)
{
	int		len;
	int		beg;

	len = 0;
	beg = *start;
	if (str[*start] == '<' || str[*start] == '>')
		while ((str[*start] == '<' || str[*start] == '>') && ++len <= 2)
			(*start)++;
	else if (quote != '\'' && quote != '\"')
		while (str[*start] && (is_not_sep(str[*start]) || *start == beg)
			&& ++len)
			(*start)++;
	else
	{
		if (str[*start] == quote && ++len)
			(*start)++;
		while (str[*start] && str[*start] != quote && ++len)
			(*start)++;
		(*start)++;
		len++;
	}
	return (ft_substr(str, *start - len, len));
}

int	increase_token(t_input **cmd, int *token, char *str, int i)
{
	int j;

	j = -1;
	while (++j <= i)
	{
		if (j && (str[j - 1] == '<' || str[j - 1] == '>') && !*cmd)
			*token = 1;
		else if (is_white_space(str[j]))
		{
			while (str[j] && is_white_space(str[j]))
				j++;
			(*token)++;
		}
	}
	if ((*token) == 3 && !*cmd)
		return (0);
	return (1);
}

void	check_for_empty_arg(t_arg_lst *lst, int token)
{
	if (!lst)
		return ;
	while (lst->next)
		lst = lst->next;
	if ((lst->token[0] == '\"' || lst->token[0] == '\'')
		&& lst->token[1] == lst->token[0] && token != 2)
		lst->type = EMPTY_TK;
	else if (token == 2) // && (lst->type == WORD_TK || lst->type == EMPTY_TK))
		lst->type = BEF_CMD_TK;
}

int	split_cmd_redir(t_input **cmd, char *str, int i, t_env *envp)
{
	t_arg_lst	*lst;
	int			token;

	token = 0;
	lst = NULL;
	while (i >= 0 && str[i] && str[i] != '|' && i < (int)ft_strlen(str))
	{
		if (token == 2 && str[i - 1] == ' ')
			*cmd = create_node(split_token(str, &i, str[i]), WORD_TK, envp);
		else
			i = create_and_add_node(str, (int []){i, 0}, &lst, envp);
		while (i >= 0 && str[i] && is_white_space(str[i]))
			i++;
		if (i > 0 && str[i - 1] == ' ' && token >= 3)
			i = create_and_add_node(str, (int []){i, 1}, &lst, envp);
		if (!increase_token(cmd, &token, str, i))
			return (-1);
		if (token <= 2)
			check_for_empty_arg(lst, token);
	}
	if (i != -1 && !*cmd)
		*cmd = create_node(NULL, 0, envp);
	(*cmd)->arg = lst;
	return (free_arg_lst(&(*cmd)->arg, i));
}

int	split_cmd(t_input **cmd, char *str, int i, t_env *env)
{
	int	token;

	token = 0;
	while (str[i] && str[i] != '|' && i < (int)ft_strlen(str))
	{
		if (token == 0)
			*cmd = create_node(split_token(str, &i, str[i]), WORD_TK, env);
		else
			i = create_and_add_node(str, (int []){i, 0}, &((*cmd)->arg), env);
		if (!*cmd || i == -1)
			return (-1);
		while (str[i] && is_white_space(str[i]))
			i++;
		if (str[i - 1] == ' ' && (*cmd)->arg)
			i = create_and_add_node(str, (int []){i, 1}, &(*cmd)->arg, env);
		if (i == -1)
			return (free_arg_lst(&(*cmd)->arg, i));
		token++;
	}
	return (i);
}

static int	get_input_struct(t_input **start, char *str, t_env *envp)
{
	t_input	*cmd;
	int		i;

	i = -1;
	cmd = 0;
	while (++i < (int)ft_strlen(str))
	{
		if (i == 0 || str[i] == '|' || (str[i - 1] == '|' && i > 1))
		{
			if (i && str[i - 1] == '|')
				while (str[i] && is_white_space(str[i]))
					i++;
			i = choose_split_kind(str, i, &cmd, envp);
			if (i == -1)
				return (i);
		}
		ft_lstadd_back((t_list **)start, (t_list *)cmd);
		if (cmd)
			cmd = cmd->next;
		while (str[i] && is_white_space(str[i]))
			i++;
	}
	return (i);
}

int	parse(t_input **input, char *str, t_env *envp)
{
	char	*strc;

	*input = NULL;
	strc = str;
	if (!str)
		return (0);
	if (parse_error(str))
		return (free(str), g_ret_val = 258, 0);
	while (*strc && is_white_space(*strc))
		strc++;
	if (get_input_struct(input, strc, envp) == -1)
		return (free_input(input), free(str), 0);
	return (free(str), 1);
}
