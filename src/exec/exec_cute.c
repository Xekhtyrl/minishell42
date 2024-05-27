/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:23:10 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/27 21:31:20 by gfinet           ###   ########.fr       */
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

int	exec_builtin(t_input *cmd, t_env **envp, int size, t_cmd_info *inf)
{
	char	**built;
	int		f;

	f = 0;
	built = (char *[]){"cd", "pwd", "env", "echo", "exit", "unset", "export",
		"exporto_patronum", 0};
	if (!built)
		return (-1);
	while (built[f] && ft_strncmp(built[f], cmd->token, ft_strlen(cmd->token)))
		f++;
	if (f == 0)
		return (ft_cd(*envp, cmd->arg), 1);
	if (f == 1)
		return (ft_pwd(), free_info(inf), free_env(envp), exit(0), 1);
	if (f == 2)
		return (ft_env(*envp), free_info(inf), free_env(envp), exit(0), 1);
	if (f == 3)
		return (ft_echo(cmd->arg), free_info(inf), free_env(envp), exit(0), 1);
	if (f == 4)
		return (free_env(envp), ft_exit(cmd->arg, size == 1, inf), 1);
	if (f == 5)
		return (ft_unset(envp, cmd->arg), 1);
	if (f == 6 || f == 7)
		return (ft_export(cmd->arg, *envp, f - 6), 1);
	return (0);
}

void	cmd_fork(t_input *cmd, t_cmd_info *inf, int n_cmd, int **pipe_fd)
{
	char	*path;

	path = 0;
	mini_dup(pipe_fd, n_cmd, inf, cmd->arg);
	if (cmd->type == CMD_TK)
	{
		path = get_cmd_path(*inf->env, cmd);
		if (!path)
		{
			close_pipes(pipe_fd, inf->size);
			multi_array_free(inf->envtb, path);
			exit(EXIT_FAILURE);
		}
		exec_cmd_ve(get_all_cmd(cmd, ft_lstsize((t_list *)cmd->arg)),
			inf->envtb, path, pipe_fd[n_cmd]);
	}
	else
		exec_builtin(cmd, inf->env, inf->size, inf);
}

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
