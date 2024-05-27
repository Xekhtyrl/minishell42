/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 23:00:34 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/27 23:00:59 by lvodak           ###   ########.fr       */
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
