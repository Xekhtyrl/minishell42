/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:52:09 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/05 22:12:49 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redir_tk(int type)
{
	return ((type == READ_TK || type == WRITE_TK || type == APPEN_TK));
}

void	free_and_relink_node(t_arg_lst **lst, t_arg_lst *prev)
{
	t_arg_lst	*temp;

	temp = *lst;
	if (temp->type == WORD_TK)
		free(temp->token);
	if (prev)
		prev->next = (*lst)->next;
	*lst = (*lst)->next;
	free(temp);
}

t_arg_lst	*find_start(t_arg_lst *lst)
{
	while (lst)
	{
		if (is_redir_tk(lst->type))
		{
			lst = lst->next;
			if (lst->type == SPACE_TK)
				lst = lst->next;
			if (lst->type == WORD_TK)
				lst = lst->next;
			if (lst->type == SPACE_TK)
				lst = lst->next;
		}
		else
			break ;
	}
	return (lst);
}

void	clear_args_fd(t_arg_lst **lst)
{
	t_arg_lst	*start;
	t_arg_lst	*prev;

	start = (*lst);
	*lst = find_start(*lst);
	prev = NULL;
	while (start)
	{
		if (is_redir_tk((start)->type))
		{
			free_and_relink_node(&start, prev);
			if (start && (start)->type == SPACE_TK)
				free_and_relink_node(&start, prev);
			if (start && (start)->type == WORD_TK)
				free_and_relink_node(&start, prev);
			if (start && (start)->type == SPACE_TK)
				free_and_relink_node(&start, prev);
		}
		else
		{
			prev = start;
			start = (start)->next;
		}
	}
}
