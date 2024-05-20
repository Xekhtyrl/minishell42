/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:48:05 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/20 22:45:32 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	detect_token(t_arg_lst *args, int token)
{
	t_arg_lst	*arg;

	arg = args;
	while (arg)
	{
		if (arg->type == token)
			return (1);
		arg = arg->next;
	}
	return (0);
}

int	detect_all_heredocs(t_input *input)
{
	t_input	*tmp;

	tmp = input;
	while (tmp)
	{
		if (detect_token(tmp->arg, HEREDOC_TK))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	add_here(char **buff, char **res, char *word)
{
	int	add;

	*buff = readline("> ");
	if (!*buff)
		return (0);
	add = ft_strncmp(*buff, word, ft_strlen(*buff) + !ft_strlen(*buff));
	if (!add)
	{
		if (!*res)
			*res = ft_strdup("");
		if (!*res)
			return (0);
		return (1);
	}
	if (!*res)
		*res = ft_strdup(*buff);
	else if (*res)
		*res = ft_stradd(*res, *buff);
	if (!*res)
		return (free(buff), 0);
	*res = ft_stradd(*res, "\n");
	return (1);
}

char	*get_heredoc(t_arg_lst *arg, int fd)
{
	char		*res;
	char		*buff;
	t_arg_lst	*tmp;

	tmp = arg->next;
	res = 0;
	buff = 0;
	if (tmp->type == SPACE_TK)
		tmp = tmp->next;
	if (!add_here(&buff, &res, tmp->token))
		return (free(arg->token), NULL);
	while (ft_strncmp(buff, tmp->token, ft_strlen(buff) + (!ft_strlen(buff))))
	{
		free(buff);
		if (!add_here(&buff, &res, tmp->token))
			return (ft_putstr_fd(res, fd), free(arg->token), res);
	}
	free(buff);
	free(arg->token);
	ft_putstr_fd(res, fd);
	return (res);
}

char	*get_file_heredoc(void)
{
	char	*str;
	char	*final;
	int		fd;

	final = ft_strdup("");
	fd = open("/tmp/here_doc.txt", O_RDONLY, 0666);
	if (fd < 0)
		return (final);
	while (1)
	{
		str = get_next_line(fd);
		// printf("%i >>> %s", fd, str);
		if (!str)
			break ;
		final = ft_stradd(final, str);
		free(str);
	}
	return (close(fd), final);
}

int	fork_heredoc(t_arg_lst *arg)
{
	int	fd;
	
	fd = 0;
	if (arg->type == HEREDOC_TK)
	{
	
		if (fork() == 0)
		{
			g_ret_val = -2;
			fd = open("/tmp/here_doc.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
			// if (fd < 0)
			// 	exit(1);
			get_heredoc(arg, fd);
			close(fd);
			exit(0);
		}
		wait(0);
		if (g_ret_val == 1)
			return (close(fd), 0);
		arg->token = get_file_heredoc();
		if (!arg->token)
			arg->token = ft_strdup("");
	}
	return (1);
}

int	heredoc(t_input *input)
{
	t_input		*tmp;
	t_arg_lst	*arg;

	tmp = input;
	while (tmp)
	{
		arg = tmp->arg;
		while (arg)
		{
			g_ret_val = -1;
			if (!fork_heredoc(arg))
				return (0);
			arg = arg->next;
		}
		tmp = tmp->next;
	}
	return (1);
}
