/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:09:38 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/10 20:29:49 by lvodak           ###   ########.fr       */
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

// REMOVE
void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		printf("lst %s\n", envp[i++]);
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
	if (!m_env)
		return (ft_putendl_fd("Error: env not loaded", 2), 1);
	update_shell_lvl(m_env);
	print_env(envp);
	ft_env(m_env);
	using_history();
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
		if (!parse(&input, str, m_env))
			send_error(MALLOC_ERR);
		else
		{
			pipe = fill_fd(input, ft_lstsize((t_list *)input));
			if (!pipe)
				return (printf("yoloooo\n"));
			if (detect_all_heredocs(input))
				heredoc(input);
			empty_args(input);
			execute_command(&m_env, input, pipe);
			print_input_lst(input);
			// free_input(&input);
		}
	}
	clear_history();
	return (0);
}
