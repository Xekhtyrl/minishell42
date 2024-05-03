/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:17:12 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/03 23:47:13 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_error(char *str)
{
	if (!closed_quotes(str))
		return (ft_putstr_fd("parse error: quote left opened\n", 2), 1);
	while (*str)
	{
		if ((*str == '>' && *(str + 1) == '<'))
			return (ft_putstr_fd("syntax error near unexpected token `", 2),
				ft_putchar_fd(*(str + 1), 2), ft_putendl_fd("'", 2),1);
		str++;
	}
	return (0);
}
