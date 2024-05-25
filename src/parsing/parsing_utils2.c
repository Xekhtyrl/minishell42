/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:17:12 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/13 20:37:11 by lvodak           ###   ########.fr       */
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
