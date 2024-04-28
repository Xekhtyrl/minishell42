/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:16:11 by gfinet            #+#    #+#             */
/*   Updated: 2024/04/28 15:58:06 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int echo(int *pipe[2], t_input *cmd)
{
	size_t size;

	size = ft_strlen(cmd->token);
	if (ft_strlen("echo") != size || ft_strncmp(cmd->token, "echo", size))
		return (0);
	
}