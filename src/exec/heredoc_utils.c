/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:52:45 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/27 17:53:02 by lvodak           ###   ########.fr       */
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
