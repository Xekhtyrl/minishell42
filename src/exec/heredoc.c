/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:48:05 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/19 16:52:48 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	detect_token(t_arg_lst *args, int token)
{
	t_arg_lst	*arg;

	arg = args;
	while (arg)
	{
		if (arg->type == token)
			return (1);
		arg = arg->next;
	}
	return (0);
}

int	detect_all_heredocs(t_input *input)
{
	t_input	*tmp;

	tmp = input;
	while (tmp)
	{
		if (detect_token(tmp->arg, HEREDOC_TK))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	add_here(char **buff, char **res, char *word)
{
	int	add;

	*buff = readline("> ");
	if (!*buff || g_ret_val == 1)
		return (0);
	add = ft_strncmp(*buff, word, ft_strlen(*buff) + !ft_strlen(*buff));
	if (!add)
	{
		if (!*res)
			*res = ft_strdup("");
		if (!*res)
			return (0);
		return (1);
	}
	if (!*res)
		*res = ft_strdup(*buff);
	else if (*res)
		*res = ft_stradd(*res, *buff);
	if (!*res)
		return (free(buff), 0);
	*res = ft_stradd(*res, "\n");
	return (1);
}

char	*get_heredoc(t_arg_lst *arg)
{
	char		*res;
	char		*buff;
	t_arg_lst	*tmp;

	tmp = arg->next;
	res = 0;
	buff = 0;
	if (tmp->type == SPACE_TK)
		tmp = tmp->next;
	if (!add_here(&buff, &res, tmp->token))
		return (0);
	while (ft_strncmp(buff, tmp->token, ft_strlen(buff) + (!ft_strlen(buff))))
	{
		free(buff);
		if (!add_here(&buff, &res, tmp->token))
			return (free(arg->token), res);
	}
	free(buff);
	free(arg->token);
	return (res);
}

int	heredoc(t_input *input)
{
	t_input		*tmp;
	t_arg_lst	*arg;

	g_ret_val = -1;
	tmp = input;
	while (tmp)
	{
		arg = tmp->arg;
		while (arg)
		{
			if (arg->type == HEREDOC_TK)
			{
				arg->token = get_heredoc(arg);
				if (!arg->token)
				{
					arg->token = ft_strdup("");
					return (1);
				}
			}
			arg = arg->next;
		}
		tmp = tmp->next;
	}
	return (1);
}
