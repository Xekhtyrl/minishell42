/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:18:05 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/20 22:51:00 by lvodak           ###   ########.fr       */
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
		// system("leaks minishell");
		exit(0);
		
	}
}

void	sign_handler(int code)
{
	if (code == SIGINT)
	{
		if (g_ret_val != -1 && g_ret_val != -2)
		{
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			g_ret_val = 1;
		}
		else if (g_ret_val == -2)
		{
			write(1, "\n", 1);
			rl_replace_line("", 0);
			g_ret_val = -1;
			exit(1);
		}
	}
}

void	set_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, &sign_handler);
}
