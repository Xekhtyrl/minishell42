/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:57:52 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/29 20:14:10 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_input	*create_node(char *str, int type, t_env *envp)
{
	t_input	*node;

	node = malloc(sizeof(t_input));
	if (!node)
		return (0);
	if (str && str[0] != '\'')
		str = replace_str_env_var(str, envp);
	node->token = str;
	node->type = type;
	node->next = NULL;
	node->arg = NULL;
	return (node);
}

t_arg_lst	*arg_node(int type, char *token, t_env *envp)
{
	t_arg_lst	*node;

	node = malloc(sizeof(t_arg_lst));
	if (!node)
		return (0);
	if (token && token[0] != '\'')
		token = replace_str_env_var(token, envp);
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