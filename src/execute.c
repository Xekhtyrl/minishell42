/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:20:36 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/29 20:22:36 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void exec_cmd_ve(t_input *cmd, char **envp, char *path, int pipe[2])
{	
	char **cmd_cplt;
	

	pipe[0]++;
	pipe[0]--;
	// close(pipe[0]);
	// close(pipe[1]);

	cmd_cplt = get_all_cmd(cmd);
	execve(path, cmd_cplt, envp);
	exit(EXIT_FAILURE);
}


int exec_builtin(t_input *cmd, char **envp)
{
	char **built;
	int f;

	printf("builtin %s\n", cmd->token);
	f = 0;
	built = ft_split("cd pwd env echo exit unset export", ' ');
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
	return (strarray_free(built), 1);
}

pid_t exec_cmd(t_input *cmd,t_cmd_info *inf, int n_cmd, int **pipe)
{
	char *path;
	char **envp;
	pid_t proc;

	path = 0;
	if (cmd->type == WORD_TK)
	{
		path = get_cmd_path(inf->env, cmd);
		if (path == 0)
			return (close_pipes(pipe, inf->size), -1); //error path
		envp = get_env(inf->env);
	}
	proc = fork();
	if (!proc)
	{
		mini_dup(pipe, n_cmd);
		if (cmd->type == WORD_TK)
			exec_cmd_ve(cmd, envp, path, pipe[n_cmd]);
		else if (cmd->type == BUILT_TK)
			exec_builtin(cmd, envp);
	}
	return (proc);
}

void wait_proc(t_cmd_info * info)
{
	int i;
	int *bugs;

	i = 0;
	bugs = 0;
	bugs = malloc(sizeof(int) * info->size);
	while (i < info->size)
	{
		waitpid(info->proc[i], bugs, 0);
		i++;
	}
}

int	execute_command(t_env *envp, t_input *cmd, int **pipe_fd)
{
	t_input *tmp;
	int n_cmd;
	t_cmd_info inf;
	
	tmp = cmd;
	n_cmd = 0;
	inf.size = ft_lstsize((t_list *)cmd);
	inf.proc = malloc(sizeof(pid_t) * inf.size);
	inf.env = envp;
	if (!trad_input(cmd))
		return (close_pipes(pipe_fd, inf.size),
			send_error(-1), 0);
	while (tmp)
	{
		if (pipe_fd[n_cmd])
		{
			printf("%s in %d\n", tmp->token, pipe_fd[n_cmd][0]);
			printf("%s out %d\n", tmp->token, pipe_fd[n_cmd][1]);
		}
		inf.proc[n_cmd] = exec_cmd(tmp, &inf, n_cmd, pipe_fd);
		tmp = tmp->next;
		n_cmd++;
	}
	wait_proc(&inf);
	close_pipes(pipe_fd, inf.size);
	return (0);
}



