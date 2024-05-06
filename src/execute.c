/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:20:36 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/06 20:33:03 by Gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void exec_cmd_ve(char **cmd_cplt, char **envp, char *path, int pipe[2])
{	
	if (pipe[0] > 2)
		{close(pipe[0]);}
	if (pipe[1] > 2)
		{printf("close out %d\n", pipe[1]);close(pipe[1]);}
	//print_env(cmd_cplt);
	
	if (!ft_strncmp(cmd_cplt[0], "./minishell", 11)
		&& atoi(get_env_var(env_lst(envp), "SHLVL")) >= 42)
		execute_order_66(envp);
	else
		execve(path, cmd_cplt, envp);
	exit(EXIT_FAILURE);
}

int exec_builtin(t_input *cmd, t_env **envp)
{
	char	**built;
	int		f;

	f = 0;
	built = (char*[]){"cd", "pwd","env", "echo", "exit", "unset", "export", "exporto_patronum", 0};
	if (!built)
		return (-1);
	while (built[f] && strncmp(built[f], cmd->token, ft_strlen(cmd->token)))
		f++;
	if (f == 0)
		ft_cd(*envp, cmd->arg);
	if (f == 1)
		ft_pwd();
	if (f == 2)
		ft_env(*envp);
	if (f == 3)
		ft_echo(cmd->arg);
	if (f == 4)
		ft_exit(/**/);
	if (f == 5)
		ft_unset(envp, cmd->arg);
	if (f == 6 || f == 7)
		ft_export(cmd->arg, *envp, f - 6);
	if (f < 5 && f)
		exit(0);
	return (/*strarray_free(built),*/ 1);
}
pid_t exec_cmd(t_input *cmd, t_cmd_info *inf, int n_cmd, int **pipe_fd)
{
	char *path;
	char **envp;
	pid_t proc;

	path = 0;
	proc = 0;
	printf("cmd %s\n", cmd->token);
	if (cmd->type == CMD_TK)
	{
		path = get_cmd_path(*inf->env, cmd);
		if (path == 0)
			return (close_pipes(pipe_fd, inf->size), -1); //error path
		envp = get_env(*(inf->env));
	}
	if (cmd->type == CMD_TK || cmd->type == BUILT_TK)
	{
		if (inf->size > 1 && check_next_pipe(pipe_fd, n_cmd, inf)
			&& printf("pipe_check\n") && pipe(inf->pipe) < 0)
				send_error(-6);
		proc = fork();
		if (!proc)
		{
			mini_dup(pipe_fd, n_cmd, inf, cmd->arg);
			if (cmd->type == CMD_TK)
				exec_cmd_ve(get_all_cmd(cmd, ft_lstsize((t_list *)cmd->arg)), envp, path, pipe_fd[n_cmd]);
			else if (cmd->type == BUILT_TK)
				exec_builtin(cmd, inf->env);
		}
	}
	else
		exec_builtin(cmd, inf->env);
	return (proc);
}

void wait_proc(t_cmd_info *info)
{
	int i;

	i = 0;
	while (i < info->size)
	{
		waitpid(info->proc[i], 0, 0);
		i++;
	}
}

int	execute_command(t_env **envp, t_input *cmd, int **pipe_fd)
{
	t_cmd_info inf;
	t_input *tmp;
	int n_cmd;
	
	tmp = cmd;
	n_cmd = 0;
	inf.size = ft_lstsize((t_list *)cmd);
	inf.proc = malloc(sizeof(pid_t) * inf.size);
	inf.env = envp;
	if (!trad_input(cmd, envp))
	{
		printf("yo\n");
		return (close_pipes(pipe_fd, inf.size),
			send_error(-2), 0);
	}
	printf("cmd %s\n", (*inf.env)->content);
	while (tmp)
	{
		if (pipe_fd && pipe_fd[n_cmd])
		{
			if (pipe_fd[n_cmd][0])
				printf("ex pipe in  : %d\n", pipe_fd[n_cmd][0]);
			if (pipe_fd[n_cmd][1])
				printf("ex pipe out : %d\n", pipe_fd[n_cmd][1]);
		}
		if (in_int_array(tmp->type, (int[]){CMD_TK, BUILT_TK, ENV_TK}, 3))
		{
			printf("launch cmd %s %d\n", tmp->token, tmp->type);
			inf.proc[n_cmd] = exec_cmd(tmp, &inf, n_cmd, pipe_fd);
			mini_cls_fd(pipe_fd[n_cmd][0],pipe_fd[n_cmd][1]);
			if (check_next_pipe(pipe_fd, n_cmd, &inf))
			{
				close(inf.pipe[1]);
				pipe_fd[n_cmd + 1][0] = inf.pipe[0];
			}
		}
		else
			{printf("wassup\n");send_error(-5);}
		tmp = tmp->next;
		n_cmd++;
	}
	wait_proc(&inf);
	close_pipes(pipe_fd, inf.size);
	return (0);
}



