/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:20:26 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/19 16:12:24 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// dans le cas de quotes ouvertes il semblerait qu'il faudrait un readline
// pour chaque ligne d'input a la suite tant que la deuxieme quotes n'est pas
// mise, et chaque nv input est precedé d'un \n

static char	*split_token(char *str, int	*start, char quote)
{
	int		len;
	int		beg;

	len = 0;
	beg = *start;
	if (str[*start] == '<' || str[*start] == '>')
		while ((str[*start] == '<' || str[*start] == '>') && ++len <= 2)
			(*start)++;
	else if (quote != '\'' && quote != '\"')
		while (str[*start] && (is_not_sep(str[*start]) || *start == beg) && ++len)
			(*start)++;
	else
	{
		if (str[*start] == quote)
			(*start)++;
		while (str[*start] && str[*start] != quote && ++len)
			(*start)++;
		(*start)++;
	}
	return (ft_substr(str, *start - len - (quote == '\'' || quote == '\"'), len));
}

// < arg(1) cmd arg
// << arg(1) cmd arg
// cmd arg <> file
// ... | cmd (|| ...) arg

// a: 1er est cmd si pas de redir
// b: si redir, le suivant est arg et celui apres est cmd
// si pipe > a ou b

static int	split_cmd_redir(t_input **cmd, char *str, int start)
{
	t_arg_lst	*arg;
	t_arg_lst	*first;
	int			token;

	token = 0;
	arg = NULL;
	first = arg;
	while (str[start] && str[start] != '|')
	{
		arg = malloc(sizeof(t_arg_lst));
		if (!arg)
			return (0);
		if (token == 2)
			*cmd = create_node(split_token(str, &start, 0), WORD_TK);
		else
		{
			arg->type = get_token_type(str, start);
			arg->token = split_token(str, &start, str[start]);
			arg = arg->next;
		}
		token++;
	}
	(*cmd)->arg = first;
	return (start);
}

static int split_cmd(t_input **cmd, char *str, int start)
{
	t_arg_lst	*arg;
	int			token;

	token = 0;
	arg = NULL;
	while (str[start] && str[start] != '|' && start < (int)ft_strlen(str))
	{
		if (token == 0)
			*cmd = create_node(split_token(str, &start, str[start]), WORD_TK);
		else
		{
			arg = arg_node(get_token_type(str, start), split_token(str, &start, str[start]));
			if (arg)
				ft_lstadd_back((t_list **)&(*cmd)->arg, (t_list *)arg);
		}
		while (str[start] && is_white_space(str[start]))
			start++;
		token++;
	}
	return (start);
}

static void	get_input_struct(t_input **start, char *str)
{
	t_input	*cmd;
	int		i;

	i = -1;
	while (++i < (int)ft_strlen(str))
	{
		if (i == 0 || str[i] == '|' || (str[i - 1] == '|' && i > 1))
		{
			if (i && str[i - 1] == '|')
				while (str[i] && is_white_space(str[i]))
					i++;
			if (str[i] == '|')
				i++;
			else if (str[i] == '<')
				i = split_cmd_redir(&cmd, str, i);
			else
				i = split_cmd(&cmd, str, i);
		}
		if (cmd)
		{
			ft_lstadd_back((t_list **)start, (t_list *)cmd);
			cmd = cmd->next;
		}
		while (str[i] && is_white_space(str[i]))
			i++;
	}
}

t_input	*parse(char *str)
{
	t_input	*input;

	input = NULL;
	if (!str || !closed_quotes(str))
		return (ft_putstr_fd("parse error\n !!! HAS TO BE CHANGED", 2), NULL);
	get_input_struct(&input, str);
	return (input);
}
