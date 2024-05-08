/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:52:09 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/08 18:05:32 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	is_redir_tk(int type)
// {
// 	return ((type == READ_TK || type == WRITE_TK || type == APPEN_TK));
// }

// void	free_and_relink_node(t_arg_lst **lst, t_arg_lst *prev)
// {
// 	t_arg_lst	*temp;

// 	temp = *lst;
// 	if (temp->type == WORD_TK)
// 		free(temp->token);
// 	if (prev)
// 		prev->next = (*lst)->next;
// 	*lst = (*lst)->next;
// 	free(temp);
// }

// t_arg_lst	*find_start(t_arg_lst *lst)
// {
// 	while (lst)
// 	{
// 		if (is_redir_tk(lst->type))
// 		{
// 			lst = lst->next;
// 			if (lst && lst->type == SPACE_TK)
// 				lst = lst->next;
// 			if (lst && lst->type == WORD_TK)
// 				lst = lst->next;
// 			if (lst && lst->type == SPACE_TK)
// 				lst = lst->next;
// 		}
// 		else
// 			break ;
// 	}
// 	return (lst);
// }

// void	clear_args_fd(t_arg_lst **lst)
// {
// 	t_arg_lst	*start;
// 	t_arg_lst	*prev;

// 	start = (*lst);
// 	*lst = find_start(*lst);
// 	prev = NULL;
// 	while (start)
// 	{
// 		if (is_redir_tk((start)->type))
// 		{
// 			free_and_relink_node(&start, prev);
// 			if (start && (start)->type == SPACE_TK)
// 				free_and_relink_node(&start, prev);
// 			if (start && (start)->type == WORD_TK)
// 				free_and_relink_node(&start, prev);
// 			if (start && (start)->type == SPACE_TK)
// 				free_and_relink_node(&start, prev);
// 		}
// 		else
// 		{
// 			prev = start;
// 			start = (start)->next;
// 		}
// 	}
// }

t_arg_lst *skip_arg(t_arg_lst *t)
{
	if (t)
	{
		t = t->next;
		if (t && t->type == SPACE_TK)
			t = t->next;
		if (t && t->type == WORD_TK)
			t = t->next;
		if (t && t->type == SPACE_TK)
			t = t->next;
	}
	return (t);
}

int add_node(t_arg_lst **head, t_arg_lst **node)
{
	char *str;
	t_arg_lst *tmp;

	str = ft_strdup((*node)->token);
	if (!str)
		return (-1);
	if (!*head)
	{
		*head = arg_node((*node)->type, str, 0);
		if (!*head)
			return (-1);
	}
	else
	{
		tmp = arg_node((*node)->type, str, 0);
		if (!tmp)
			return (-1);
		ft_lstadd_back((t_list **)(head), (t_list*)tmp);
	}
	if ((*node)->type == HEREDOC_TK && (*node)->next->type == SPACE_TK)
		*node = (*node)->next->next;
	if ((*node)->type == HEREDOC_TK)
		*node = (*node)->next;
	*node = (*node)->next;
	return (1);
}

void free_all_args(t_arg_lst **head)
{
	t_arg_lst *next;

	while ((*head))
	{
		next = (*head)->next;
		if ((*head)->type != SPACE_TK)
			free((*head)->token);
		free((*head));
		*head = next;
	}
}

t_arg_lst *keep_arg_only(t_input *cmd)
{
	t_arg_lst *futur_arg;
	t_arg_lst *tmp;
	int ret;

	tmp = cmd->arg;
	futur_arg = 0;
	while (tmp)
	{
		if (in_int_array(tmp->type, (int[]){READ_TK, WRITE_TK, APPEN_TK}, 3))
			tmp = skip_arg(tmp);
		else if (tmp && tmp->type == HEREDOC_TK
			&& !detect_token(tmp->next, HEREDOC_TK) && !detect_token(tmp, READ_TK))
			ret = add_node(&futur_arg, &tmp);
		else if(tmp && tmp->type == HEREDOC_TK)
			tmp = skip_arg(tmp);
		else if (tmp && tmp->type == WORD_TK)
			ret = add_node(&futur_arg, &tmp);
		else if (tmp && tmp->type == SPACE_TK && tmp->next && tmp->next->type == WORD_TK)
			ret = add_node(&futur_arg, &tmp);
		else
			tmp = tmp->next;
		if (ret == -1)
			return (free_all_args(&futur_arg), NULL);
	}
	return (futur_arg);
}

void clear_args_fd(t_input *cmd)
{
	t_input *tmp;
	t_arg_lst *old_arg;

	tmp = cmd;
	while (tmp)
	{
		old_arg = tmp->arg;
		tmp->arg = keep_arg_only(tmp);
		free_all_args(&old_arg);
		tmp = tmp->next;
	}
}