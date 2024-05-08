/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:20:26 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/08 18:23:48 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// dans le cas de quotes ouvertes il semblerait qu'il faudrait un readline
// pour chaque ligne d'input a la suite tant que la deuxieme quotes n'est pas
// mise, et chaque nv input est precedé d'un \n

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

static int	split_cmd_redir(t_input **cmd, char *str, int i, t_env *envp)
{
	t_arg_lst	*lst;
	int			token;

	token = 0;
	lst = NULL;
	while (str[i] && str[i] != '|' && i < (int)ft_strlen(str))
	{
		if (token == 2)
			*cmd = create_node(split_token(str, &i, str[i]), WORD_TK, envp);
		else
			i = create_and_add_node(str, (int []){i, 0}, &lst, envp);
		while (str[i] && is_white_space(str[i]))
			i++;
		if (i && str[i - 1] == ' ' && token >= 3)
			i = create_and_add_node(str, (int []){i, 1}, &lst, envp);
		if ((str[i] == '<' || str[i] == '>') && !*cmd)
			token = 0;
		else
			token++;
	}
	if (!*cmd)
		*cmd = create_node(NULL, 0, envp);
	(*cmd)->arg = lst;
	return (i);
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
			i = create_and_add_node(str, (int []){i, 0}, &(*cmd)->arg, env);
		while (str[i] && is_white_space(str[i]))
			i++;
		if (str[i - 1] == ' ' && (*cmd)->arg)
			i = create_and_add_node(str, (int []){i, 1}, &(*cmd)->arg, env);
		token++;
	}
	return (i);
}

static void	get_input_struct(t_input **start, char *str, t_env *envp)
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
			if (str[i] == '|')
				i++;
			else if (str[i] == '<' || str[i] == '>')
				i = split_cmd_redir(&cmd, str, i, envp);
			else
				i = split_cmd(&cmd, str, i, envp);
		}
		ft_lstadd_back((t_list **)start, (t_list *)cmd);
		cmd = cmd->next;
		while (str[i] && is_white_space(str[i]))
			i++;
	}
}

t_input	*parse(char *str, t_env *envp)
{
	t_input	*input;

	input = NULL;
	if (!str)
		return (ft_putstr_fd("NO STR\n", 2), NULL);
	if (parse_error(str))
		return (NULL);
	get_input_struct(&input, str, envp);
	return (input);
}
