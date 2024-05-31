/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 23:00:34 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/31 16:27:49 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_parse_message(char c1, char c2)
{
	ft_putstr_fd(PARS_ERR, 2);
	ft_putchar_fd(c1, 2);
	if (c2 && c2 == c1)
		ft_putchar_fd(c2, 2);
	ft_putendl_fd("\'", 2);
}

void	skip_quotes(char *s, int *j)
{
	char	quote;

	quote = *s;
	if (s[*j] != '\'' && s[*j] != '\"')
		return ;
	(*j)++;
	while (s[*j] && s[*j] != quote)
		(*j)++;
}

static void	remove_contatenated_token(t_arg_lst *lst)
{
	t_arg_lst	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->type == HEREDOC_TK)
		{
			tmp = tmp->next;
			if (tmp && tmp->type == SPACE_TK)
				tmp = tmp->next;
			while (tmp && tmp->type != SPACE_TK)
			{
				if (tmp->type == WORD_TK)
					replace_token(tmp, ft_strdup(""), EMPTY_TK);
				tmp = tmp->next;
			}
		}
		if (tmp)
			tmp = tmp->next;
	}
}

void	replace_env_var_lst(t_arg_lst *lst, t_env *envp)
{
	t_arg_lst	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->type == HEREDOC2_TK)
			tmp->type = HEREDOC_TK;
		else if (envp && tmp->token && tmp->token[0] != '\'')
			tmp->token = replace_str_env_var(tmp->token, envp);
		tmp = tmp->next;
	}
	remove_contatenated_token(lst);
}
