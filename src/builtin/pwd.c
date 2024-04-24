/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:10:14 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/23 15:05:21 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd()
{
	char	*pwd;
	
	printf("%s", getcwd(pwd, 0));
	if (pwd)
		printf("\n");
	free(pwd);
}