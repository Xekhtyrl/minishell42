/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:20:26 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/31 16:28:15 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*split_token(char *str, int	*start, char quote, int token)
{
	int		len;
	int		beg;

	len = 0;
	beg = *start;
	if (str[*start] == '<' || str[*start] == '>')
		while (str[*start] == str[beg] && ++len <= 2)
			(*start)++;
	else if (quote != '\'' && quote != '\"')
		while (str[*start] && (is_not_sep(str[*start], token) || *start == beg)
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

int	split_cmd_redir(t_input **cmd, char *str, int i, t_env *envp)
{
	t_arg_lst	*lst;
	int			token;

	token = 0;
	lst = NULL;
	while (i >= 0 && str[i] && str[i] != '|' && i < (int)ft_strlen(str))
	{
		if (token == 3 && !*cmd && is_valid_cmd(str, i))
			*cmd = create_node(split_token(str, &i, str[i], token), 13, envp);
		else
			i = create_and_add_node(str, (int []){i, 0, token}, &lst);
		while (i >= 0 && str[i] && is_white_space(str[i]))
			i++;
		check_for_empty_arg(lst, i);
		if (i > 0 && str[i - 1] == ' ')
			i = create_and_add_node(str, (int []){i, 1, token}, &lst);
		increase_token(cmd, lst, &token);
		if (!check_for_empty_arg(lst, i))
			return (-1);
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
			*cmd = create_node(split_token(str, &i, str[i], 3), WORD_TK, env);
		else
			i = create_and_add_node(str, (int []){i, 0, 3}, &((*cmd)->arg));
		if (!*cmd || i == -1)
			return (-1);
		check_for_empty_arg((*cmd)->arg, i);
		while (str[i] && is_white_space(str[i]))
			i++;
		if (str[i - 1] == ' ' && (*cmd)->arg)
			i = create_and_add_node(str, (int []){i, 1, 3}, &(*cmd)->arg);
		if (i == -1)
			return (free_arg_lst(&(*cmd)->arg, i));
		check_for_empty_arg((*cmd)->arg, i);
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
			add_prev_to_arg(&cmd->arg);
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
