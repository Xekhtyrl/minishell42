/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:51:08 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/12 16:42:18 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_arg_lst	*skip_arg(t_arg_lst *t)
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
		if ((*head)->type != SPACE_TK)
			free((*head)->token);
		free((*head));
		*head = next;
	}
}

t_arg_lst	*keep_arg_only(t_input *cmd)
{
	t_arg_lst	*futur_arg;
	t_arg_lst	*tmp;
	int			ret;

	tmp = cmd->arg;
	futur_arg = 0;
	while (tmp)
	{
		if (in_int_array(tmp->type, (int []){READ_TK, WRITE_TK, APPEN_TK}, 3))
			tmp = skip_arg(tmp);
		else if (tmp->type == HEREDOC_TK && !detect_token(tmp->next, HEREDOC_TK)
			&& !detect_token(tmp, READ_TK))
			ret = add_node(&futur_arg, &tmp);
		else if (tmp && tmp->type == HEREDOC_TK)
			tmp = skip_arg(tmp);
		else if (tmp && tmp->type == WORD_TK)
			ret = add_node(&futur_arg, &tmp);
		else if (tmp->type == SPACE_TK && tmp->next && tmp->next->type == 13)
			ret = add_node(&futur_arg, &tmp);
		else
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
