/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:09:38 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/19 19:41:16 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
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

char	*pick_title()
{
	int		l;

	l = 2;
	if (getenv("SHLVL="))
		l = ft_atoi(getenv("SHLVL="));
	if (l == 2)
		return(GREEN"Minishell "NC);
	if (l == 3)
		return(GREEN"Minishel"RED"l "NC);
	if (l == 4)
		return(GREEN"Minishe"RED"ll "NC);
	if (l == 5)
		return(GREEN"Minish"RED"ell "NC);
	if (l == 6)
		return(GREEN"Minis"RED"hell "NC);
	if (l == 7)
		return(GREEN"Mini"RED"shell "NC);
	if (l == 8)
		return(GREEN"Min"RED"ishell "NC);
	if (l == 9)
		return(GREEN"Mi"RED"nishell "NC);
	if (l == 10)
		return(GREEN"M"RED"inishell "NC);
	return (RED"Mini hell "NC);
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

	str = NULL;
	(void)argc;
	(void)argv;
	(void)envp;
	using_history();
	set_signals();
	while (1)
	{
		printf("end    = %d\n",rl_end);
		printf("point  = %d\n",rl_point);
		printf("max_in = %d\n",max_input_history);
		printf("%s\n",rl_line_buffer);
		str = readline(pick_title());
		while (str && (ft_strlen(str) < 1 || only_space(str)))
			str = readline(pick_title());
		if (!str)
			ctrl_d();
		input = parse(str);
		add_history(str);
		free(str);
		print_input_lst(input);
	}
}