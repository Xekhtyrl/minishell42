/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:57:52 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/07 18:51:56 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	set_input(t_input *cmd, char *token, int type)
{
	if (!cmd)
		return ;
	cmd->token = token;
	cmd->type = type;
}

int	create_and_add_node(char *str, int data[2], t_arg_lst **lst, t_env *envp)
{
	t_arg_lst	*arg;

	if (data[1])
	{
		arg = arg_node(SPACE_TK, " ", envp);
		if (arg)
			ft_lstadd_back((t_list **)&lst, (t_list *)arg);
	}
	else
	{
		arg = arg_node(get_token_type(str, data[0]), split_token(str, &data[0],
					str[data[0]]), envp);
		if (arg)
			ft_lstadd_back((t_list **)lst, (t_list *)arg);
	}
	return (data[0]);
}
