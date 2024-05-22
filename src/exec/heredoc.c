/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:48:05 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/22 22:34:09 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void fill_eof_heredoc(t_arg_lst **arg)
{
	t_arg_lst	*tmp;
	char		*add;

	add = 0;
	tmp = (*arg)->next;
	while (tmp && tmp->type != BEF_CMD_TK)
	{
		if (tmp->type == WORD_TK)
		{
			add = trim_quote(tmp->token, 0);
			(*arg)->token = ft_stradd((*arg)->token, add);
			free(add);
		}
		tmp = tmp->next;
	}
}

void	get_heredoc(t_arg_lst *arg, int fd)
{
	char		*res;
	char		*buff;
	t_arg_lst	*tmp;

	tmp = arg->next;
	res = 0;
	buff = 0;
	fill_eof_heredoc(&arg);
	if (!add_here(&buff, &res, tmp->token))
		return (free(arg->token), free(res));
	while (ft_strncmp(buff, tmp->token, ft_strlen(buff) + (!ft_strlen(buff))))
	{
		free(buff);
		if (!add_here(&buff, &res, tmp->token))
			return (ft_putstr_fd(res, fd), free(arg->token), free(res));
	}
	free(buff);
	free(arg->token);
	ft_putstr_fd(res, fd);
	free(res);
}

char	*get_file_heredoc(t_arg_lst *arg)
{
	char	*str;
	char	*final;
	int		fd;

	free(arg->token);
	final = ft_strdup("");
	fd = open("/tmp/here_doc.txt", O_RDONLY, 0666);
	if (fd < 0)
		return (final);
	while (1)
	{
		str = get_next_line(fd);
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
	int	status;

	fd = 0;
	if (arg->type == HEREDOC_TK)
	{
		if (fork() == 0)
		{
			signal(SIGINT, &sig_here_doc);
			fd = open("/tmp/here_doc.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
			get_heredoc(arg, fd);
			close(fd);
			exit(0);
		}
		wait(&status);
		if (WIFEXITED(status))
			g_ret_val = WEXITSTATUS(status);
		if (g_ret_val == 130)
			return (g_ret_val = 130, 0);
		arg->token = get_file_heredoc(arg);
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
	set_signals();
	return (1);
}
