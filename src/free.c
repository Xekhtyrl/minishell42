/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:14:05 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/17 19:21:38 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	strarray_free(char **built)
{
	int	i;

	i = 0;
	while (built[i])
	{
		free(built[i]);
		i++;
	}
	free(built);
}

int	send_error(int flag)
{
	if (flag == OPEN_ERR)
		printf("%s\n", strerror(FILE_MSG));
	else if (flag == READ_ERR)
		printf("%s\n", strerror(PERM_MSG));
	else if (flag == WRITE_ERR)
		printf("%s\n", strerror(PERM_MSG));
	else if (flag == FORK_ERR)
		perror("fork error");
	else if (flag == MALLOC_ERR)
		printf("%s\n", strerror(ALLOC_MSG));
	else if (flag == PIPE_ERR)
		printf("%s\n", strerror(PIPE_MSG));
	else if (flag == ACCESS_ERR)
		printf("%s\n", strerror(FILE_MSG));
	else if (flag == PERM_ERR)
		printf("%s\n", strerror(PERM_MSG));
	else if (flag == PATH_ERR)
		perror("PATH not found");
	else if (flag == CMD_ERR)
		perror(CMD_MSG);
	else if (flag == ARG_ERR)
		printf("%s\n", strerror(ARG_MSG));
	else if (flag == ARG_L_ERR)
		printf("%s\n", strerror(ARG_L_ERR));
	return (g_ret_val);
}

void	mini_cls_fd(int fd1, int fd2)
{
	if (fd1 > 1 && close(fd1) == -1)
		perror("close1");
	if (fd2 > 2 && close(fd2) == -1)
		perror("close2");
}

void	multi_array_free(char **str1, char *str2)
{
	if (str1)
		strarray_free(str1);
	if (str2)
		free(str2);
}
