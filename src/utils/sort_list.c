/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 20:48:41 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/25 19:56:38 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	swap(t_env	**lst1)
{
	char	*temp;
	char	*temp2;
	int		tmp;

	temp = (*lst1)->content;
	temp2 = (*lst1)->var;
	tmp = (*lst1)->flag;
	(*lst1)->content = (*lst1)->next->content;
	(*lst1)->var = (*lst1)->next->var;
	(*lst1)->flag = (*lst1)->next->flag;
	(*lst1)->next->content = temp;
	(*lst1)->next->var = temp2;
	(*lst1)->next->flag = tmp;
}

void	sort_lst(t_env **lsta)
{
	while ((*lsta)->next)
	{
		if ((*lsta)->next && ft_strncmp((*lsta)->var, (*lsta)->next->var, ft_strlen((*lsta)->var)) > 0)
		{
			swap(lsta);
			while ((*lsta)->prev)
				*lsta = (*lsta)->prev; 
		}
		else
			*lsta = (*lsta)->next;
	}
	while ((*lsta)->prev)
		*lsta = (*lsta)->prev; 
}
