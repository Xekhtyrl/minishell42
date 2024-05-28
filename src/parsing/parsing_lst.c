/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:57:52 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/28 16:36:52 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_input	*create_node(char *str, int type, t_env *envp)
{
	t_input	*node;

	node = malloc(sizeof(t_input));
	if (!node)
		return (send_error(MALLOC_ERR), NULL);
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
		return (send_error(MALLOC_ERR), NULL);
	if (envp && token && token[0] != '\'')
		token = replace_str_env_var(token, envp);
	node->token = token;
	node->type = type;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	set_input(t_input *cmd, char *token, int type)
{
	if (!cmd)
		return ;
	cmd->token = token;
	cmd->type = type;
}

int	create_and_add_node(char *str, int data[3], t_arg_lst **lst, t_env *envp)
{
	t_arg_lst	*arg;

	if (data[1])
	{
		arg = arg_node(SPACE_TK, ft_strdup(" "), envp);
		if (arg)
			ft_lstadd_back((t_list **)&lst, (t_list *)arg);
		else
			return (free_arg_lst(&arg, -1), -1);
	}
	else
	{
		arg = arg_node(get_token_type(str, data[0]), split_token(str, &data[0],
					str[data[0]], data[2]), envp);
		if (arg)
			ft_lstadd_back((t_list **)lst, (t_list *)arg);
		else
			return (free_arg_lst(&arg, -1), -1);
	}
	return (data[0]);
}

void	add_prev_to_arg(t_arg_lst **arg)
{
	t_arg_lst	*prev;
	t_arg_lst	*tmp;

	prev = NULL;
	tmp = *arg;
	while (tmp)
	{
		tmp->prev = prev;
		prev = tmp;
		tmp = tmp->next;
	}
}
