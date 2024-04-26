/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:09:38 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/26 22:53:57 by Gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <time.h>
// #include <termios.h>

void	print_input_lst(t_input	*input)
{
	printf("____________________________________________________________\n");
	while (input)
	{
		printf("%scmd%s = %s\n", RED, NC, input->token);
		if (input->arg)
		{
			while (input->arg)
			{
				printf("\t%sarg%s = %s\t type > %i\n", LBLUE, NC, input->arg->token, input->arg->type);
				input->arg = input->arg->next;
			}
		}
		input = input->next;
	}
}

char	*ft_strjoinsup(char **tabl)
{
	int	i;
	int	j;
	int	len;
	char	*final;

	i = -1;
	len = ft_strlen(GREEN) + ft_strlen(RED) + ft_strlen(NC) + ft_strlen(tabl[1]) + ft_strlen(tabl[3]) + 1;
	final = malloc(sizeof(char) * (len + 1));
	len = 0;
	while (++i < 5)
	{
		j = 0;
		while (tabl[i][j])
			final[len++] = tabl[i][j++];
	}
	final[len] = 0;
	return final;
}

char *pick_title()
{
	char	*str;
	char	*path;
	char	*str2;
	int		lvl;
	int		len;

	lvl = 0;
	if (getenv("SHLVL"))
		lvl = atoi(getenv("SHLVL")) - 2;
	path = getcwd(NULL, 0);
	if (ft_strlen(ft_strrchr(path, '/')) + 10 > (size_t)lvl)
		str = ft_strjoin("Minishell ", ft_strrchr(path, '/'));
	else
		str = ft_strjoin("Mini hell ", ft_strrchr(path, '/'));
	len = ft_strlen(str);
	if (lvl > 10)
		lvl = 10;
	free(path);
	path = ft_substr(str, 0, (float)(len * (10 - lvl) / 10));
	str2 =  ft_substr(str, (float)(len * (10 - lvl) / 10), len);
	free(str);
	str = ft_strjoinsup((char *[5]){GREEN, path, RED, str2, NC" "});
	return (free(path), free(str2), str);
}

int only_space(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] == ' ')
		i++;
	if (!str[i])
		return (1);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	static char 	*str;
	t_input	*input;
	t_env	*m_env;
	int		*pipe[2];

	str = NULL;
	(void)argc;
	(void)argv;
	(void)envp;
	(void)m_env;
	// m_env = env_lst(envp);
	// ft_env(m_env);
	using_history();
	set_signals();
	pipe[0] = 0;
	pipe[1] = 0;
	while (1)
	{
		str = readline(pick_title());
		while (str && (ft_strlen(str) < 1 || only_space(str)))
			str = readline(pick_title());
		if (!str)
			ctrl_d();
		add_history(str);
		input = parse(str);
		free(str);
		if (fill_fd(pipe, input) == -1)
			printf("yolo\n");
		print_input_lst(input);
		execute_command(envp, input, pipe);
	}
	clear_history();
	return (0);
}
