/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:09:38 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/09 16:35:22 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

// REMOVE
void	print_input_lst(t_input	*i)
{
	t_input	*input;

	input = i;
	printf("____________________________________________________________\n");
	while (input)
	{
		printf("%scmd%s = %s type > %d\n", RED, NC, input->token, input->type);
		if (input->arg)
		{
			while (input->arg)
			{
				printf("\t%sarg%s = %s\t type > %i\n", LBLUE, NC,
					input->arg->token, input->arg->type);
				input->arg = input->arg->next;
			}
		}
		input = input->next;
	}
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

int	prep_exec(t_input *input, t_env *m_env)
{
	int				**pipe;

	if (!fill_fd(input, ft_lstsize((t_list *)input), &pipe))
		send_error(-1);
	if (detect_all_heredocs(input))
		heredoc(input);
	empty_args(input);
	if (!trad_input(input, &m_env))
		send_error(-1);
	execute_command(&m_env, input, pipe);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	static char		*str = NULL;
	t_input			*input;
	t_env			*m_env;
	int				**pipe;

	(void)argc;
	(void)argv;
	m_env = env_lst(envp);
	update_shell_lvl(m_env);
	set_signals();
	pipe = 0;
	while (1)
	{
		str = readline(pick_title());
		while (str && (ft_strlen(str) < 1 || only_space(str)))
			str = readline(pick_title());
		if (!str)
			ctrl_d();
		add_history(str);
		input = parse(str, m_env);
		free(str);
		prep_exec(input, m_env);
	}
	clear_history();
	return (0);
}
		// pipe = fill_fd(input, ft_lstsize((t_list *)input));
		// if (!pipe)
		// 	send_error(-1);
		// if (detect_all_heredocs(input))
		// 	heredoc(input);
		// empty_args(input);
		// if (!trad_input(input, &m_env))
		// 	send_error(-1);
		// execute_command(&m_env, input, pipe);
		// print_input_lst(input);