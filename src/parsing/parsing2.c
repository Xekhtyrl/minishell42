/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:37:02 by Gfinet            #+#    #+#             */
/*   Updated: 2024/05/25 01:29:24 by Gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int get_infile(char *str, t_input **cmd, t_env *envp)
{
	int i;
	int j;
	char *infile;
	t_arg_lst *arg;

	i = 0;
	infile = 0;
	while (str && str[i] && str[i] != '|')
	{
		if (str[i + 1] == '<')
		{
			infile = ft_substr(str, i - 1, 2);
			arg = arg_node(HEREDOC_TK, infile, envp);
		}
		else
		{
			if (str[i + 1] == ' ')
			{
				infile = ft_strdup("<");
				arg = arg_node(READ_TK, infile, envp);
			}
			else
			{
				j = i;
				while (str[i + j] && is_not_sep(str[i + j]))
					j++;
			}
		}
		ft_lstadd_back((t_list **)cmd, (t_list *)(*cmd)->arg);
	}
}

int get_redir_bef(char *str, t_input **cmd, t_env *envp)
{
	int i;

	i = 0;
	while (str && str[i] && str[i] != '|')
	{
		if (str[i] == '<')
			i = get_infile(&str[i], cmd, envp);
		else if (str[i] == '>')
			i = get_outfile(&str[i], cmd, envp);
		else if (str[i] && str[i] != '|')
			i = get_cmd(&str[i], cmd);
		if (!str[i] || str[i] == '|')
			return (i);
		i++;
	}
	return (i);
}

int get_one_cmd(char *str, t_input **cmd, t_env *envp)
{
	int i;

	i = 0;
	*cmd = create_node(0, 0, 0);
	while (str && str[i] && str[i] != '|')
	{
		i = get_redir_bef(&str[i], cmd, envp);
		i = get_arg_after(&str[i], cmd, envp);
		i++;
	}
}

int get_input_struct(t_input **start, char *str, t_env *envp)
{
	t_input *cmd;
	int i;

	i = 0;
	cmd = 0;
	while (i < (int)ft_strlen(str))
	{
		if (i == 0 || str[i] == '|')
		{
			while (str[i] && is_white_space(str[i]))
					i++;
			i = get_one_cmd(&str[i], &cmd, envp);
		}
		ft_lstadd_back((t_list **)start, (t_list *)cmd);
		if (cmd)
			cmd = cmd->next;
		while (str[i] && is_white_space(str[i]))
			i++;
		if (str[i])
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