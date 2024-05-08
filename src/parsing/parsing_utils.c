/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:40:23 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/07 18:52:01 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_white_space(char c)
{
	return (((c >= 9 && c <= 13) || c == 32));
}

int	is_not_sep(char c)
{
	return (!(is_white_space(c) || c == 34 || c == 36 || c == 39 || c == 45
			|| c == 60 || c == 62 || c == 124));
}

int	closed_quotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			i++;
			if (!str[i])
				return (0);
			while (str[i] && str[i] != '\'')
				if (!str[++i])
					return (0);
		}
		else if (str[i] == '\"')
		{
			i++;
			if (!str[i])
				return (0);
			while (str[i] && str[i] != '\"')
				if (!str[++i])
					return (0);
		}
	}
	return (1);
}

int	check_for_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (str[i++] == '|')
			break ;
	if (!str[i])
		return (0);
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
	else if (c[start] == '$')
		return (ENV_VAR_TK);
	else
		return (WORD_TK);
}
