/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:09:46 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/29 19:13:31 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include "pipex_bonus.h"
# include "token.h"
# include "functions.h"
# include "structures.h"

# include <stdio.h>
# define READLINE_LIBRARY 1
# define RL_PROMPT_START_IGNORE  '\001'
# define RL_PROMPT_END_IGNORE    '\002'
# include </Users/lvodak/.brew/Cellar/readline/8.2.10/include/readline/readline.h>
# include </Users/lvodak/.brew/Cellar/readline/8.2.10/include/readline/history.h>
// # include "/Users/gfinet/homebrew/Cellar/readline/8.2.10/include/readline/readline.h"
// # include "/Users/gfinet/homebrew/Cellar/readline/8.2.10/include/readline/history.h"
// # include "/opt/homebrew/Cellar/readline/8.2.10/include/readline/readline.h"
// # include "/opt/homebrew/Cellar/readline/8.2.10/include/readline/history.h"
# include <signal.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <errno.h>

#endif