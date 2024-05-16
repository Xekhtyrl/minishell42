/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:20:36 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/15 19:27:47 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd_ve(char **cmd_cplt, char **envp, char *path, int pipe[2])
{
	if (pipe[0] > 2)
		close(pipe[0]);
	if (pipe[1] > 2)
		close(pipe[1]);
	if (!ft_strncmp(cmd_cplt[0], "./minishell", 11)
		&& atoi(get_env_var(env_lst(envp), "SHLVL")) >= 42)
		execute_order_66(envp);
	else
		execve(path, cmd_cplt, envp);
	exit(EXIT_FAILURE);
}

int	exec_builtin(t_input *cmd, t_env **envp)
{
	char	**built;
	int		f;

	f = 0;
	built = (char *[]){"cd", "pwd", "env", "echo", "exit", "unset", "export",
		"exporto_patronum", 0};
	if (!built)
		return (-1);
	while (built[f] && strncmp(built[f], cmd->token, ft_strlen(cmd->token)))
		f++;
	if (f == 0)
		return (ft_cd(*envp, cmd->arg), 1);
	if (f == 1)
		return (ft_pwd(), exit(0), 1);
	if (f == 2)
		return (ft_env(*envp), exit(0), 1);
	if (f == 3)
		return (ft_echo(cmd->arg), exit(0), 1);
	if (f == 4)
		return (ft_exit(), exit(0), 1);
	if (f == 5)
		return (ft_unset(envp, cmd->arg), 1);
	if (f == 6 || f == 7)
		return (ft_export(cmd->arg, *envp, f - 6), 1);
	return (0);
}

int	set_path_env(t_cmd_info *inf, t_input *cmd, char **path)
{
	*path = get_cmd_path(*inf->env, cmd);
	if (*path == 0)
		return (0);
	return (1);
}

void	cmd_fork(t_input *cmd, t_cmd_info *inf, int n_cmd, int **pipe_fd)
{
	char	*path;


	path = 0;
	mini_dup(pipe_fd, n_cmd, inf, cmd->arg);
	if (cmd->type == CMD_TK)
	{
		if (!set_path_env(inf, cmd, &path))
		{
			close_pipes(pipe_fd, inf->size);
			multi_array_free(inf->envtb, path);
		}
		exec_cmd_ve(get_all_cmd(cmd, ft_lstsize((t_list *)cmd->arg)),
			inf->envtb, path, pipe_fd[n_cmd]);
	}
	else
		exec_builtin(cmd, inf->env);
}

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
			if (pipe_fd[n_cmd][0] != -1 && cmd->type != ERROR_TK)
				cmd_fork(cmd, inf, n_cmd, pipe_fd);
			else
				return (close(inf->pipe[0]), close(inf->pipe[1]),
					exit(EXIT_FAILURE), (pid_t){0});
		}
	}
	else if (cmd->type == ENV_TK && n_cmd == 0 && !cmd->next)
		exec_builtin(cmd, inf->env);
	return (proc);
}

// void	wait_proc(t_cmd_info *info)
// {
// 	int	i;

// 	i = 0;
// 	while (i < info->size)
// 	{
// 		if (i == info->size -1 && g_ret_val == 127)
// 			waitpid(info->proc[i], 0, 0);
// 		else
// 			waitpid(info->proc[i], &g_ret_val, 0);
// 		i++;
// 	}
// 	if (g_ret_val != 127)
// 		g_ret_val = !(!g_ret_val);
// }
void    wait_proc(t_cmd_info *info)
{
    int i;    i = 0;
    while (i < info->size)
    {
        if (i == info->size -1 && in_int_array(g_ret_val, (int []){126, 127}, 2))
            waitpid(info->proc[i], 0, 0);
        else
            waitpid(info->proc[i], &g_ret_val, 0);
        i++;
    }
    if (g_ret_val == 2)
        g_ret_val = 130;
    else if (!in_int_array(g_ret_val, (int []){126, 127}, 2))
        g_ret_val = !(!g_ret_val);
}

int	cmd_start(t_cmd_info *inf, t_input *cmd, int **pipe_fd, int n_cmd)
{
	inf->proc[n_cmd] = exec_cmd(cmd, inf, n_cmd, pipe_fd);
	mini_cls_fd(pipe_fd[n_cmd][0], pipe_fd[n_cmd][1]);
	if (check_next_pipe(pipe_fd, n_cmd, inf))
	{
		close(inf->pipe[1]);
		pipe_fd[n_cmd + 1][0] = inf->pipe[0];
	}
	if (cmd->type == ERROR_TK)
		g_ret_val = 127;
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
	inf.size = ft_lstsize((t_list *)cmd);
	inf.proc = malloc(sizeof(pid_t) * inf.size);
	inf.env = envp;
	inf.envtb = get_env(*envp);
	while (tmp)
	{
		cmd_start(&inf, tmp, pipe_fd, n_cmd);
		tmp = tmp->next;
		n_cmd++;
	}
	close_pipes(pipe_fd, inf.size);
	wait_proc(&inf);
	return (free(inf.proc), free_tab(inf.envtb), 0);
}
