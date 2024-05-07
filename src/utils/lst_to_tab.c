/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:20:26 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/07 14:55:28 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	set_res(char ***res, t_arg_lst **tmp, int len, t_input *cmd)
{
	*res = malloc((len + 2) * sizeof(char *));
	if (!res)
		return (0);
	*res[0] = cmd->token;
	*tmp = cmd->arg;
	return (1);
}

char	**get_all_cmd(t_input *cmd, int len)
{
	t_arg_lst	*tmp;
	char		**res;
	int			i;

	if (!set_res(&res, &tmp, len, cmd))
		return (0);
	i = 1;
	while (tmp)
	{
		if (!in_int_array(tmp->type,
				(int []){READ_TK, WRITE_TK, SPACE_TK, HEREDOC_TK}, 4))
		{
			res[i] = trim_quote(tmp->token);
			if (!res[i++])
				return (strarray_free(res), NULL);
		}
		else if (in_int_array(tmp->type,
				(int []){READ_TK, WRITE_TK, HEREDOC_TK}, 3))
			while (tmp && tmp->type != WORD_TK)
				tmp = tmp->next;
		if (tmp)
			tmp = tmp->next;
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
		return (0);
	i = -1;
	while (++i < len)
	{
		tabl[i] = lst->content;
		lst = lst->next;
	}
	tabl[i] = 0;
	return (tabl);
}
