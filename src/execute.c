/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:20:36 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/29 01:24:39 by Gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_stradd(char *s1, char const *s2)
{
	size_t		j;
	size_t		i;
	char		*p;

	if (!s1 && !s2)
		return (0);
	p = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	i = 0;
	j = 0;
	if (p == NULL)
		return (free(s1), NULL);
	while (s1 && i < ft_strlen(s1))
	{
		p[i] = s1[i];
		i++;
	}
	free(s1);
	while (s2 && j < ft_strlen(s2))
	{
		p[i + j] = s2[j];
		j++;
	}
	p[i + j] = '\0';
	return (p);
}

char *get_all_cmd(t_input *cmd)
{
	t_arg_lst *tmp;
	char *res;

	res = 0;
	res = ft_strdup(cmd->token);
	tmp = cmd->arg;
	if (tmp)
		res = ft_stradd(res, " ");
	while (tmp)
	{
		res = ft_stradd(res, tmp->token);
		tmp = tmp->next;
	}
	return (res);
}

void exec_cmd_ve(t_input *cmd, char **envp, char *path)
{	
	char *cmd_cplt;

	cmd_cplt = get_all_cmd(cmd);
	printf("%s\n", path);
	ft_printf("%s\n", cmd_cplt);
	
	execve(&path, cmd_cplt, envp);

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
	return (strarray_free(built), 1);
}

pid_t exec_cmd(t_input *cmd,t_cmd_info *inf, int n_cmd, int *pipe[2])
{
	char *path;
	char **envp;
	pid_t proc;

	path = 0;
	n_cmd = n_cmd - 1 + 1;
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
			exec_cmd_ve(cmd, envp, path);
		else if (cmd->type == BUILT_TK)
			exec_builtin(cmd, inf->env);
		exit(0);
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

int	execute_command(t_env *envp, t_input *cmd, int *pipe[2])
{
	t_input *tmp;
	int n_cmd;
	t_cmd_info inf;
	
	(void)envp;
	(void)pipe;
	tmp = cmd;
	n_cmd = 0;
	inf.size = ft_lstsize((t_list *)cmd);
	inf.proc = malloc(sizeof(pid_t) * inf.size);
	inf.env = envp;
	if (!trad_input(cmd))
		return (close_pipes(pipe, inf.size),
			send_error(-1), 0);
	while (tmp)
	{
		if (pipe[0])
			printf("%s in %d\n", tmp->token, pipe[0][n_cmd]);
		if (pipe[1])
			printf("%s out %d\n", tmp->token, pipe[1][n_cmd]);
		inf.proc[n_cmd] = exec_cmd(tmp, &inf, n_cmd, pipe);
		tmp = tmp->next;
		n_cmd++;
	}
	wait_proc(&inf);
	close_pipes(pipe, inf.size);
	return (0);
}



