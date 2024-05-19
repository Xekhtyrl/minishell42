/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:18:05 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/18 19:36:14 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ctrl_d(t_env **envp, int f)
{
	if (f)
	{
		rl_clear_history();
		printf("exit\n");
		free_env(envp);
		system("leaks minishell");
		exit(0);
	}
}

void	sign_handler(int code)
{
	if (code == SIGINT)
	{
		write(1, "\n", 1);
		if (g_ret_val != -1)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		g_ret_val = 1;
	}
}

void	set_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, &sign_handler);
}
