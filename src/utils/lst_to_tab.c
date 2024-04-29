/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:20:26 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/29 23:25:27 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **get_all_cmd(t_input *cmd)
{
	t_arg_lst *tmp;
	char **res;
	int len;
	int i;

	res = 0;
	len = ft_lstsize((t_list *)cmd->arg);
	res = malloc((len + 2) * sizeof(char *));
	if (!res)
		return (0);
	res[0] = cmd->token;
	tmp = cmd->arg;
	i = 1;
	while (tmp)
	{
		if (tmp->type == READ_TK || tmp->type == WRITE_TK
			|| tmp->type == SPACE_TK)
			tmp = tmp->next->next;
		else
		{
			res[i] = tmp->token;
			tmp = tmp->next;
			i++;
		}
		
	}
	res[i] = 0;
	return (res);
}

char	**lst_to_tab(t_list *lst)
{
	char	**tabl;
	int		len;
	int		i;

	len = ft_lstsize(lst);
	tabl = malloc(sizeof(char *) * (len + 1));
	if (!tabl)
		return(0);
	i = -1;
	while (++i < len)
	{
		tabl[i] = lst->content;
		lst = lst->next;
	}
	tabl[i] = 0;
	return (tabl);
}
