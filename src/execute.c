/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:20:36 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/30 17:17:05 by Gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void exec_cmd_ve(t_input *cmd, char **envp, char *path, int pipe[2])
void exec_cmd_ve(char **cmd_cplt, char **envp, char *path, int pipe[2])
{	
	//char **cmd_cplt;
	// cmd_cplt = get_all_cmd(cmd);
	

	// pipe[0]++;
	// pipe[0]--;
	
	
	// int i =0;
	// while (i < 2 && cmd_cplt[i])
	// 	ft_printf("%s\n", cmd_cplt[i++]);
	if (pipe[0] > 2)
		{printf("close in %d\n", pipe[0]);close(pipe[0]);}
	if (pipe[1] > 2)
		{printf("close out %d\n", pipe[0]);close(pipe[1]);}
	execve(path, cmd_cplt, envp);
	exit(EXIT_FAILURE);
}


int exec_builtin(t_input *cmd, t_env *envp)
{
	char **built;
	int f;

	printf("builtin %s\n", cmd->token);
	f = 0;
	built = (char*[]){"cd","pwd","env","echo","exit","unset","export", 0};
	if (!built)
		return (-1);
	while (built[f] && strncmp(built[f], cmd->token, ft_strlen(cmd->token)))
		f++;
	(void)envp;
	// if (f == 0)
	// 	ft_cd(cmd->arg);
	// if (f == 1)
	// 	ft_pwd(cmd->arg);
	// if (f == 2)
	// 	ft_env(envp);
	// if (f == 3)
	// 	ft_echo(cmd->arg);
	// if (f == 4)
	// 	ft_exit();
	// if (f == 5)
	// 	ft_unset();
	// if (f == 6)
	// 	ft_export();
	exit(0);
	return (1);
}

pid_t exec_cmd(t_input *cmd, t_cmd_info *inf, int n_cmd, int **pipe_fd)
{
	char *path;
	char **envp;
	pid_t proc;

	path = 0;
	if (cmd->type == WORD_TK)
	{
		path = get_cmd_path(cmd, inf->env);
		if (path == 0)
			return (close_pipes(pipe_fd, inf->size), -1); //error path
		envp = get_env(inf->env);
	}
	if (n_cmd < inf->size - 1 && inf->size > 1
		&& check_next_pipe(pipe_fd, n_cmd, inf) && pipe(inf->pipe) < 0)
			send_error(-6);
	proc = fork();
	if (!proc)
	{
		mini_dup(pipe_fd, n_cmd, inf);
		if (cmd->type == WORD_TK)
			exec_cmd_ve(get_all_cmd(cmd), envp, path, pipe_fd[n_cmd]);
		else if (cmd->type == BUILT_TK)
			exec_builtin(cmd, inf->env);
	}
	return (proc);
}

void wait_proc(t_cmd_info *info)
{
	int i;
	int *bugs;

	i = 0;
	bugs = 0;
	bugs = malloc(sizeof(int) * info->size);
	if (!bugs)
		send_error(-1);
	while (i < info->size)
	{
		waitpid(info->proc[i], bugs, 0);
		i++;
	}
}

int	execute_command(t_env *envp, t_input *cmd, int **pipe_fd)
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
		return (close_pipes(pipe_fd, inf.size),
			send_error(-1), 0);
	while (tmp)
	{
		if (tmp->type == CMD_TK || tmp->type == BUILT_TK)
		{
			inf.proc[n_cmd] = exec_cmd(tmp, &inf, n_cmd, pipe_fd);
			mini_cls_fd(pipe_fd[n_cmd][0],pipe_fd[n_cmd][1]);
			if (check_next_pipe(pipe_fd, n_cmd, &inf))
			{
				close(inf.pipe[1]);
				pipe_fd[n_cmd + 1][0] = inf.pipe[0];
			}
		}
		//waitpid(inf.proc[n_cmd], 0, 0);
		tmp = tmp->next;
		n_cmd++;
	}
	wait_proc(&inf);
	close_pipes(pipe_fd, inf.size);
	return (0);
}



