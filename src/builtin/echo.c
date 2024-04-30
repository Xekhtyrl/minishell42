/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:16:11 by gfinet            #+#    #+#             */
/*   Updated: 2024/04/30 16:53:54 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_echo(t_input *cmd)
{
	size_t size;

	size = ft_strlen(cmd->token);
	if (ft_strlen("echo") != size || ft_strncmp(cmd->token, "echo", size))
		return (0);
	return (write(1, cmd->arg->token, size));
}