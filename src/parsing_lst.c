/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:57:52 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/24 17:10:42 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_input	*create_node(char *str, int type)
{
	t_input	*node;

	node = malloc(sizeof(t_input));
	if (!node)
		return (0);
	node->token = str;
	node->type = type;
	node->next = NULL;
	node->arg = NULL;
	return (node);
}

t_arg_lst	*arg_node(int type, char *token)
{
	t_arg_lst	*node;

	node = malloc(sizeof(t_arg_lst));
	if (!node)
		return (0);
	node->token = token;
	node->type = type;
	node->next = NULL;
	return (node);
}

void set_input(t_input *cmd, char *token, int type)
{
	if (!cmd)
		return ;
	cmd->token = token;
	cmd->type = type;
}