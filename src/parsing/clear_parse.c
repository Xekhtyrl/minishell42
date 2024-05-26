/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:51:08 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/26 19:42:56 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_arg_lst	*skip_arg(t_arg_lst *t, t_arg_lst *head)
{
	t_arg_lst *prev;

	prev = t;
	if (t && t->type == EMPTY_TK)
	{
		while (head && head->next != t)
			head = head->next;
		if (head && head->type == SPACE_TK && (!t->next || (t->next && t->next->type == SPACE_TK)))
			return (t);
	}
	if (t)
	{
		t = t->next;
		if (t && t->type == SPACE_TK && prev->type != EMPTY_TK)
			t = t->next;
		if (t && t->type == WORD_TK && prev->type != EMPTY_TK)
			t = t->next;
		if (t && t->type == SPACE_TK && prev->type != EMPTY_TK)
			t = t->next;
	}
	return (t);
}

int	add_node(t_arg_lst **head, t_arg_lst **node)
{
	char		*str;
	t_arg_lst	*tmp;

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
		ft_lstadd_back((t_list **)(head), (t_list *)tmp);
	}
	if ((*node)->type == HEREDOC_TK && (*node)->next->type == SPACE_TK)
		*node = (*node)->next->next;
	if ((*node)->type == HEREDOC_TK)
		*node = (*node)->next;
	*node = (*node)->next;
	return (1);
}

void	free_all_args(t_arg_lst **head)
{
	t_arg_lst	*next;

	while ((*head))
	{
		next = (*head)->next;
		free((*head)->token);
		free((*head));
		*head = next;
	}
}

t_arg_lst	*keep_arg_only(t_input *cmd)
{
	t_arg_lst	*futur_arg;
	t_arg_lst	*tmp;
	t_arg_lst	*head;
	int			ret;

	tmp = cmd->arg;
	futur_arg = 0;
	head = cmd->arg;
	while (tmp)
	{
		if (in_int_array(tmp->type, (int []){READ_TK, WRITE_TK, APPEN_TK, EMPTY_TK}, 4))
			tmp = skip_arg(tmp, head);
		if (tmp && tmp->type == HEREDOC_TK && !detect_token(tmp->next, HEREDOC_TK)
			&& !detect_token(tmp, READ_TK))
			ret = add_node(&futur_arg, &tmp);
		else if (tmp && tmp->type == HEREDOC_TK)
			tmp = skip_arg(tmp, head);
		else if (tmp && (tmp->type == WORD_TK || tmp->type == EMPTY_TK))
			ret = add_node(&futur_arg, &tmp);
		else if (tmp && tmp->type == SPACE_TK && tmp->next && (tmp->next->type == 13 || tmp->next->type == 11))
			ret = add_node(&futur_arg, &tmp);
		else if (tmp)
			tmp = tmp->next;
		if (ret == -1)
			return (free_all_args(&futur_arg), NULL);
	}
	return (futur_arg);
}

void	empty_args(t_input *cmd)
{
	t_input		*tmp;
	t_arg_lst	*old_arg;

	tmp = cmd;
	while (tmp)
	{
		old_arg = tmp->arg;
		tmp->arg = keep_arg_only(tmp);
		free_all_args(&old_arg);
		tmp = tmp->next;
	}
}
