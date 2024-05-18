/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:23:10 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/18 17:24:56 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_cmd_ve(char **cmd_cplt, char **envp, char *path, int pipe[2])
{
	if (pipe[0] > 2)
		close(pipe[0]);
	if (pipe[1] > 2)
		close(pipe[1]);
	if (!ft_strncmp(cmd_cplt[0], "./minishell", 11)
		&& atoi(get_env_var(env_lst(envp), ft_strdup("SHLVL"))) >= 42)
		execute_order_66(envp);
	else
		execve(path, cmd_cplt, envp);
	exit(EXIT_FAILURE);
}

int	exec_builtin(t_input *cmd, t_env **envp, int size)
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
		return (ft_exit(cmd->arg, size == 1), 1);
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
			exit(EXIT_FAILURE);
		}
		exec_cmd_ve(get_all_cmd(cmd, ft_lstsize((t_list *)cmd->arg)),
			inf->envtb, path, pipe_fd[n_cmd]);
	}
	else
		exec_builtin(cmd, inf->env, inf->size);
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
