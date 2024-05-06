/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:52:09 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/06 20:39:47 by Gfinet           ###   ########.fr       */
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
		if (is_redir_tk(lst->type) && lst) //is_redir_tk(lst->type))
		{
			lst = lst->next;
			if (lst && lst->type == SPACE_TK)
				lst = lst->next;
			if (lst && lst->type == WORD_TK)
				lst = lst->next;
			if (lst && lst->type == SPACE_TK)
				lst = lst->next;
		}
		else
			break ;
	}
	return (lst);
}

void jump_free_arg(t_arg_lst **start, t_arg_lst *prev)
{
	if (is_redir_tk((*start)->type)) // READ_TK, WRITE_TK, APPEN_TK
	{
		free_and_relink_node(start, prev);
		if (*start && (*start)->type == SPACE_TK)
			free_and_relink_node(start, prev);
		if (*start && (*start)->type == WORD_TK)
			free_and_relink_node(start, prev);
		if (*start && (*start)->type == SPACE_TK)
			free_and_relink_node(start, prev);
	}
	else
	{
		prev = *start;
		*start = (*start)->next;
	}
}

void empty_args(t_input *input)
{
	t_input		*tmp;
	t_arg_lst	*start;
	t_arg_lst	*prev;

	tmp = input;
	while (tmp)
	{
		start = tmp->arg;
		tmp->arg = find_start(tmp->arg);
		prev = NULL;
		while (start)
			jump_free_arg(&start, prev);
		tmp = tmp->next;
	}
}
