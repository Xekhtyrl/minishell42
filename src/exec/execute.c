/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:20:36 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/19 16:54:18 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_proc(t_cmd_info *info)
{
	int	i;
	int	status;

	i = 0;
	while (i < info->size)
	{
		waitpid(info->proc[i], &status, 0);
		if (WIFEXITED(status) && !in_int_array(g_ret_val,
				(int []){126, 127}, 2))
			g_ret_val = WEXITSTATUS(status);
		else if (status == 2 && !in_int_array(g_ret_val, (int []){126, 127}, 2))
			g_ret_val = 130;
		else if (!in_int_array(g_ret_val, (int []){126, 127}, 2))
			g_ret_val = !(!g_ret_val);
		i++;
	}
	if (status == 2 && !in_int_array(g_ret_val, (int []){126, 127}, 2))
		g_ret_val = 130;
	else if (!in_int_array(g_ret_val, (int []){126, 127}, 2))
		g_ret_val = !(!g_ret_val);
}

int	cmd_start(t_cmd_info *inf, t_input *cmd, int **pipe_fd, int n_cmd)
{
	g_ret_val = -1;
	inf->proc[n_cmd] = exec_cmd(cmd, inf, n_cmd, pipe_fd);
	mini_cls_fd(pipe_fd[n_cmd][0], pipe_fd[n_cmd][1]);
	if (check_next_pipe(pipe_fd, n_cmd, inf))
	{
		close(inf->pipe[1]);
		pipe_fd[n_cmd + 1][0] = inf->pipe[0];
	}
	if (cmd->type == ERROR_TK)
	{
		if (!access(cmd->token, F_OK))
			g_ret_val = 126;
		else
			g_ret_val = 127;
	}
	return (1);
}

int	execute_command(t_env **envp, t_input *cmd, int **pipe_fd)
{
	t_cmd_info	inf;
	t_input		*tmp;
	int			n_cmd;

	tmp = cmd;
	n_cmd = 0;
	g_ret_val = -1;
	inf = (t_cmd_info){ft_lstsize((t_list *)cmd), {0}, envp, get_env(*envp),
		malloc(sizeof(pid_t) * inf.size)};
	if (!inf.proc)
		return (send_error(MALLOC_ERR), 0);
	while (tmp)
	{
		if (tmp->token && !ft_strncmp(tmp->token, "exit\0", 5) && inf.size == 1)
			tmp->type = ENV_TK;
		else if (tmp->token && !ft_strncmp(tmp->token, "exit\0", 5)
			&& inf.size != 1 && n_cmd != inf.size)
			check_exit_error(tmp->arg);
		if (cmd_start(&inf, tmp, pipe_fd, n_cmd++) && tmp->type == ERROR_TK)
			send_error(CMD_ERR);
		tmp = tmp->next;
	}
	wait_proc(&inf);
	close_pipes(pipe_fd, inf.size);
	return (free(inf.proc), free_tab(inf.envtb), 0);
}
