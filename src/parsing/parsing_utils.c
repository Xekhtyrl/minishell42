/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:40:23 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/27 22:56:25 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_white_space(char c)
{
	return (((c >= 9 && c <= 13) || c == 32));
}

int	is_not_sep(char c, int token_nbr)
{
	if (token_nbr >= 3 && c == '-')
		return (1);
	return (!(is_white_space(c) || c == '\'' || c == '\"' || c == '-'
			|| c == '<' || c == '>' || c == '|'));
}

int	check_pipe(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if ((i == 0 && str[i + 1]) || str[i] == '|')
		{
			i++;
			while (is_white_space(str[i]))
				i++;
		}
		if (!str[i] || str[i] == '|')
			return (0);
	}
	return (1);
}

int	closed_quotes(char *str)
{
	int		i;
	char	quote;

	i = -1;
	if (!check_pipe(str))
		return (124);
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			i++;
			if (!str[i])
				return (quote);
			while (str[i] && str[i] != quote)
				if (!str[++i])
					return (quote);
		}
	}
	return (1);
}

int	get_token_type(char *c, int start)
{
	if (c[0] == '|')
		return (PIPE_TK);
	else if (c[start] == '<' && c[start + 1] == '<')
		return (HEREDOC_TK);
	else if (c[start] == '<')
		return (READ_TK);
	else if (c[start] == '>' && c[start + 1] == '>')
		return (APPEN_TK);
	else if (c[start] == '>')
		return (WRITE_TK);
	else
		return (WORD_TK);
}
