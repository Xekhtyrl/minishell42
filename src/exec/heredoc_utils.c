/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:52:45 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/28 22:29:10 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	detect_tk(t_arg_lst *args, int token)
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
		if (detect_tk(tmp->arg, HEREDOC_TK))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

//!!! env-var dans heredoc ne doivent pas etre interprete si LIMITER entre quote ou a du etre concatener
int	concat_arg(t_arg_lst **start)
{
	t_arg_lst	*tmp;
	char		*final;

	tmp = *start;
	final = ft_strdup("");
	while (tmp && !in_int_array(tmp->type,
			(int []){SPACE_TK, READ_TK, WRITE_TK, APPEN_TK, HEREDOC_TK}, 5))
	{
		if (tmp->type == WORD_TK)
		{
			tmp->token = trim_quote(tmp->token, 1);
			if (!tmp->token)
				return (0);
			final = ft_stradd(final, tmp->token);
			if (!final)
				return (0);
			if (tmp != (*start))
				tmp->type = EMPTY_TK;
		}
		else
			tmp->type = EMPTY_TK;
		tmp = tmp->next;
	}
	return (free((*start)->token), (*start)->token = final, 1);
}
