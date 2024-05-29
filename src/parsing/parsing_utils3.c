/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 23:00:34 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/29 16:29:48 by lvodak           ###   ########.fr       */
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

void	replace_env_var_lst(t_arg_lst *lst, t_env *envp)
{
	while (lst)
	{
		if (lst->type == HEREDOC2_TK)
			lst->type = HEREDOC_TK;
		else if (envp && lst->token && lst->token[0] != '\'')
			lst->token = replace_str_env_var(lst->token, envp);
		lst = lst->next;
	}
}
