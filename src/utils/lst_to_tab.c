/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:20:26 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/28 16:27:52 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**lst_to_tab(t_list *lst)
{
	char	**tabl;
	int		len;
	int		i;

	len = ft_lstsize(lst);
	tabl = malloc(sizeof(char *) * (len + 1));
	if (!tabl);
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
