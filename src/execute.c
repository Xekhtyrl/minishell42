/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:20:36 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/28 22:42:08 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int exec_cmd_ve(t_input *cmd, char *path)
{
	(void)cmd;
	printf("%s\n", path);

	return (1);
}


int exec_builtin(t_input *cmd, t_env *envp)
{
	char **built;
	int f;

	printf("builtin\n");
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
	return (strarray_free(built), 1);
}

int uni_dup(int fd_in, int fd_out)
{
	if (fd_in > 0)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			return (-1);
	}
	if (fd_out > 1)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			return (-1);
	}
	return (1);
}

int	mini_dup(int *fd_in_out[2], int n_cmd, int size)
{
	int *prev = 0;
	int *next;
	int pipe_fd[2];

	if (n_cmd == 0 && fd_in_out[0][1] != 1)
		return (uni_dup(fd_in_out[0][0], fd_in_out[0][1]));
	if (size > 1 && fd_in_out[n_cmd][1] == 1)

	if (fd_in_out[n_cmd - 1][1])
	pipe_fd[0] = fd_in_out[n_cmd - 1][1];
	pipe_fd[1] = fd_in_out[n_cmd][1];
	if (*prev == 0 && fd_in_out[n_cmd][0] == 0)
	{
		if (dup2(*prev, STDIN_FILENO) == -1)
			return (-1);
	}
	else if (fd_in_out[n_cmd][0] > 0)
	{
		if (dup2(fd_in_out[n_cmd][0], STDIN_FILENO) == -1)
			return (-1);
	}
	if (*next > 0)
	{
		if (dup2(*next, STDOUT_FILENO))
			return (-1);
	}
	mini_cls_fd(*prev, *next, fd_in_out[n_cmd][0]);
	return (1);
}

int	execute_command(t_env *envp, t_input *cmd, int *pipe[2])
{
	char	*path = 0;
	t_input *tmp;
	int n_cmd;
	pid_t *proc;
	int size;
	
	(void)envp;
	(void)pipe;
	tmp = cmd;
	n_cmd = 0;
	size = ft_lstsize((t_list *)cmd);
	proc = malloc(sizeof(pid_t) * size);
	if (!trad_input(cmd))
		return (close_pipes(pipe, size),
			send_error(-1), 0);
	while (tmp)
	{
		if (pipe[0])
			printf("in %d\n",pipe[0][n_cmd]);
		if (pipe[1])
			printf("out %d\n",pipe[1][n_cmd]);
		if (tmp->type == WORD_TK)
		{
			path = get_cmd_path(envp, tmp);
			if (path == 0)
				return (close_pipes(pipe, ft_lstsize((t_list *)cmd)), -1); //error path
			proc[n_cmd] = fork();
			if (!proc[n_cmd])
			{
				mini_dup(pipe, n_cmd, ft_lstsize((t_list *)cmd));
				exec_cmd_ve(tmp, path);
			}
		}
		else if (tmp->type == BUILT_TK)
		{
			proc[n_cmd] = fork();
			if (!proc[n_cmd])
			{
				mini_dup(pipe, n_cmd, ft_lstsize((t_list *)cmd));
				exec_builtin(tmp, envp);
			}
		}
		tmp = tmp->next;
		n_cmd++;
	}
	close_pipes(pipe, ft_lstsize((t_list *)cmd));
	return (0);
}



