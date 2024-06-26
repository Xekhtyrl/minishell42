/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:09:38 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/31 17:50:45 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

// int g_ret_val;
// REMOVE
void	print_input_lst(t_input	*i, int debug)
{
	t_input		*input;
	t_arg_lst	*start;

	if (!debug)
		return ;
	input = i;
	printf("____________________________________________________________\n");
	while (input)
	{
		printf("%scmd%s = %s type > %d\n", RED, NC, input->token, input->type);
		if (input->arg)
		{
			start = input->arg;
			while (input->arg)
			{
				printf("\t%sarg%s = %s\t type > %i\n", LBLUE, NC,
					input->arg->token, input->arg->type);
				input->arg = input->arg->next;
			}
			input->arg = start;
		}
		input = input->next;
	}
	i = input;
}

char	*pick_title(void)
{
	char	*str;
	char	*path;
	char	*str2;
	int		lvl;
	int		len;

	lvl = 0;
	if (getenv("SHLVL"))
		lvl = atoi(getenv("SHLVL")) - 1;
	path = getcwd(NULL, 0);
	if (!path)
		path = ft_strdup("/.");
	if (lvl < 10)
		str = ft_strjoin("Minishell ", ft_strrchr(path, '/'));
	else
		str = ft_strjoin("Mini hell ", ft_strrchr(path, '/'));
	len = ft_strlen(str);
	if (lvl > 10)
		lvl = 10;
	free(path);
	path = ft_substr(str, 0, (float)(len * (10 - lvl) / 10));
	str2 = ft_substr(str, (float)(len * (10 - lvl) / 10), len);
	free(str);
	str = ft_strjoinsup((char *[5]){GREEN, path, RED, str2, NC" "});
	return (free(path), free(str2), str);
}

int	prep_exec(t_input *input, t_env **m_env)
{
	int	**pipe;

	if (!fill_fd(input, ft_lstsize((t_list *)input), &pipe))
		send_error(MALLOC_ERR);
	if (detect_all_heredocs(input))
		if (!heredoc(input))
			return (close_pipes(pipe, ft_lstsize((t_list *)input)),
				free_input(&input), 0);
	print_input_lst(input, DEBUG);
	empty_args(input, *m_env);
	if (!access("/tmp/here_doc.txt", F_OK) && !fork())
		execve("/bin/rm", (char *[]){"rm", "/tmp/here_doc.txt", 0}, NULL);
	wait(0);
	if (!trad_input(input, m_env))
		send_error(-1);
	execute_command(m_env, input, pipe);
	free_input(&input);
	return (1);
}

char	*get_input(int debug)
{
	char	*str;
	char	*title;

	title = pick_title();
	if (debug == 2)
	{
		str = get_next_line(0);
		while (str && (ft_strlen(str) < 1 || only_space(str)))
		{
			free(str);
			str = get_next_line(0);
		}
	}
	else
	{
		str = readline(title);
		while (str && (ft_strlen(str) < 1 || only_space(str)))
		{
			free(str);
			str = readline(title);
		}
	}
	free(title);
	return (str);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_input	*input;
	t_env	*m_env;

	(void)argc;
	(void)argv;
	g_ret_val = 0;
	m_env = env_lst(envp);
	if (!m_env)
		return (ft_putendl_fd("Error: env not loaded", 2), 1);
	update_shell_lvl(m_env);
	set_signals();
	while (1)
	{
		str = get_input(DEBUG);
		if (!str)
			ctrl_d(&m_env, 1);
		add_history(str);
		if (parse(&input, str, m_env))
			prep_exec(input, &m_env);
	}
	return (g_ret_val);
}
