/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:52:09 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/08 18:41:55 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_and_relink_node(t_arg_lst **lst, t_arg_lst *prev)
{
	t_arg_lst	*temp;

	temp = *lst;
	printf("FREE %s %d\n", temp->token, temp->type);
	if (temp->type != SPACE_TK)
		free(temp->token);
	if (prev)
		prev->next = (*lst)->next;
	*lst = (*lst)->next;
	free(temp);
}

void	jump_free_arg(t_arg_lst **start, t_arg_lst *prev, int check_type)
{
	if (*start && check_type)
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

void	free_heredoc(t_arg_lst **start, t_arg_lst **prev, int flag)
{
	if (flag)
	{
		while (*start && (*start)->type != HEREDOC_TK)
			*start = (*start)->next;
	}
	if (*start && (*start)->type == HEREDOC_TK)
	{
		*prev = *start;
		*start = (*start)->next;
		free_and_relink_node(start, *prev);
		start = prev;
		if (detect_token(*start, READ_TK))
			free_and_relink_node(start, 0);
	}
}

void	free_to_heredoc(t_arg_lst **start, t_arg_lst **prev, int token1,
			int token2)
{
	while (*start && (*start)->type != token1 && (*start)->type != token2)
		jump_free_arg(start, *prev, (*start)->type != WORD_TK);
	free_heredoc(start, prev, 0);
}

void	empty_end(t_arg_lst **start, t_arg_lst **prev)
{
	//free_heredoc(start, prev, 1);
	while ((*start) && !in_int_array((*start)->type, (int []){READ_TK, WRITE_TK,
			APPEN_TK}, 3))
	{
		*prev = *start;
		*start = (*start)->next;
	}
	while (*start && in_int_array((*start)->type, (int []){READ_TK, WRITE_TK,
			APPEN_TK}, 3))
		jump_free_arg(start, *prev, in_int_array((*start)->type, (int [])
			{READ_TK, WRITE_TK, APPEN_TK}, 3));
}

void	empty_args(t_input *input)
{
	t_input		*tmp;
	t_arg_lst	*start;
	t_arg_lst	*prev;

	tmp = input;
	while (tmp)
	{
		start = tmp->arg;
		while (start && start->type != WORD_TK) // empty all if infile after heredoc or all to heredoc before cmd
		{
			prev = 0;
			free_to_heredoc(&start, &prev, HEREDOC_TK, WORD_TK);
		}
		tmp->arg = start;
		printf("arg %s\n", tmp->arg->token);
		while (start && detect_token(start, READ_TK))
		{
			prev = 0;
			while (start && (start->type == WORD_TK || start->type == SPACE_TK))
				start = start->next;
			free_to_heredoc(&start, &prev, HEREDOC_TK, 99);
		}
		start = tmp->arg;
		printf("arg %s\n", tmp->arg->token);
		empty_end(&start, &prev);
		tmp = tmp->next;
	}
}
