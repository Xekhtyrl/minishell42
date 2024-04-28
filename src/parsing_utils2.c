/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:17:12 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/28 17:57:59 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_error(char *str)
{
	if (!closed_quotes(str))
		return (1);
	while (*str)
	{
		if ((*str == '<' && *(str + 1) == '>') || (*str == '>' && *(str + 1) == '<'))
			return (1);
		str++;
	}
	return (0);
}
