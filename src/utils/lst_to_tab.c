/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:20:26 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/29 19:21:49 by gfinet           ###   ########.fr       */
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
	// printf("len %d\n",len);
	res = malloc((len + 2) * sizeof(char *));
	if (!res)
		return (0);
	res[len + 1] = NULL;
	res[0] = cmd->token;
	tmp = cmd->arg;
	i = 1;
	while (tmp)
	{
		res[i] = tmp->token;
		tmp = tmp->next;
		i++;
	}
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
