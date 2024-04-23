/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 20:48:41 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/23 21:28:32 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	push(t_env **lst1, t_env **lst2)
{
	t_env	*temp;

	if (!*lst1)
		return ;
	temp = *lst1;
	(*lst1)->next = (*lst2);
	if (*lst2)
		(*lst2)->prev = *lst1;
	*lst2 = *lst1;
	(*lst2)->prev = NULL;
	*lst1 = temp->next;
	(*lst1)->prev = NULL;
}

void	rotate(t_env **lst1)
{
	if (!*lst1)
		return ;
	if ((*lst1)->next)
		*lst1 = (*lst1)->next;
	else
		while ((*lst1)->prev)
			*lst1 = (*lst1)->prev;
}

void	sort_LSD_recursive(t_env **lsta, t_env **lstb, int msd)
{
	if (msd > 0)
		sort_LSD_recursive(lsta, lstb, msd>>1);
	while (msd > 0)
	{
		if (!(*lsta)->flag && ((*lsta)->var[msd] & msd))
			rotate(lsta);
		else
			push(lsta, lstb);
		if (*lstb)
		{
			while (*lstb)
				push(lstb, lsta);
		}
	}
	return ;
}