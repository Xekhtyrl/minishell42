/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:20:36 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/22 16:49:55 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

pid_t	exec_cmd(t_input *cmd, t_cmd_info *inf, int n_cmd, int **pipe_fd)
{
	pid_t	proc;

	proc = 0;
	if (in_int_array(cmd->type, (int []){CMD_TK, BUILT_TK, ERROR_TK}, 3))
	{
		if (inf->size > 1 && check_next_pipe(pipe_fd, n_cmd, inf)
			&& pipe(inf->pipe) < 0)
			send_error(PIPE_ERR);
		proc = fork();
		if (!proc)
		{
			if (check_good_pipe(pipe_fd, n_cmd) && cmd->type != ERROR_TK)
				cmd_fork(cmd, inf, n_cmd, pipe_fd);
			else
			{
				mini_cls_fd(inf->pipe[0], inf->pipe[1]);
				exit(EXIT_FAILURE);
			}
		}
	}
	else if (cmd->type == ENV_TK && n_cmd == 0 && !cmd->next)
		exec_builtin(cmd, inf->env, inf->size);
	return (proc);
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

void	cmd_not_found(t_input *cmd)
{
	ft_printf("%s : ", cmd->token);
	send_error(CMD_ERR);
}

int	set_inf(t_cmd_info *inf, t_env **envp, t_input *cmd)
{
	inf->size = ft_lstsize((t_list *)cmd);
	inf->env = envp;
	inf->envtb = get_env(*envp);
	inf->proc = malloc(sizeof(pid_t) * inf->size);
	if (!inf->proc)
		return (0);
	return (1);
}

/*
Main function of execute

*/

int	execute_command(t_env **envp, t_input *cmd, int **pipe_fd)
{
	t_cmd_info	inf;
	t_input		*tmp;
	int			n_cmd;

	tmp = cmd;
	n_cmd = 0;
	g_ret_val = -1;
	if (!set_inf(&inf, envp, cmd))
		return (send_error(MALLOC_ERR), 0);
	while (tmp)
	{
		if (tmp->token && !ft_strncmp(tmp->token, "exit\0", 5) && inf.size == 1)
			tmp->type = ENV_TK;
		else if (tmp->token && !ft_strncmp(tmp->token, "exit\0", 5)
			&& inf.size != 1 && n_cmd != inf.size)
			check_exit_error(tmp->arg);
		if (cmd_start(&inf, tmp, pipe_fd, n_cmd++) && tmp->type == ERROR_TK)
			cmd_not_found(tmp);
		tmp = tmp->next;
	}
	wait_proc(&inf);
	close_pipes(pipe_fd, inf.size);
	return (free(inf.proc), free_tab(inf.envtb), 0);
}
