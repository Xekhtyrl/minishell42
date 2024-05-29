/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:52:45 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/29 16:45:02 by lvodak           ###   ########.fr       */
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

void	replace_token(t_arg_lst *arg, char *new, int n_type)
{
	free(arg->token);
	arg->token = new;
	arg->type = n_type;
}

int	concat_arg(t_arg_lst **start)
{
	t_arg_lst	*tmp;
	char		*final;

	tmp = *start;
	final = ft_strdup("");
	while (tmp && !in_int_array(tmp->type, (int []){SPACE_TK, READ_TK, WRITE_TK,
			APPEN_TK, HEREDOC_TK, HEREDOC2_TK}, 6))
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

void	env_var_heredoc_cond(t_arg_lst *arg)
{
	t_arg_lst	*tmp;

	tmp = arg;
	tmp = tmp->next;
	if (tmp && tmp->type == SPACE_TK)
		tmp = tmp->next;
	if (tmp && tmp->type == WORD_TK && tmp->next
		&& !in_int_array(tmp->next->type, (int []){WORD_TK, EMPTY_TK}, 2))
		if (tmp->token[0] != '\"' && tmp->token[0] != '\'')
			return ;
	arg->type = HEREDOC2_TK;
}
