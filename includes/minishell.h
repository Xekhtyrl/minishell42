/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:09:46 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/03 16:48:33 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include "pipex_bonus.h"
# include "token.h"
# include "functions.h"


# include <stdio.h>
// printf, strerror, perror,
# define READLINE_LIBRARY 1
# define RL_PROMPT_START_IGNORE  '\001'
# define RL_PROMPT_END_IGNORE    '\002'
// # include </Users/lvodak/.brew/Cellar/readline/8.2.10/include/readline/readline.h>
// # include </Users/lvodak/.brew/Cellar/readline/8.2.10/include/readline/history.h>
# include "/Users/gfinet/homebrew/Cellar/readline/8.2.10/include/readline/readline.h"
# include "/Users/gfinet/homebrew/Cellar/readline/8.2.10/include/readline/history.h"
// # include "/opt/homebrew/Cellar/readline/8.2.10/include/readline/readline.h"
// # include "/opt/homebrew/Cellar/readline/8.2.10/include/readline/history.h"
// readline, (rl_)clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history
# include <signal.h>
// signal, sigaction, sigemptyset, sigaddset
# include <sys/wait.h>
// wait, waitpid, wait3, wait4
# include <unistd.h>
# include <fcntl.h>
// write, access, open, read, close, fork, dup, dup2, pipe
// isatty, ttyname, ttyslot, getcwd, execve, unlink
# include <stdlib.h>
// malloc, free, getenv
# include <curses.h>
# include <term.h>
# include <termios.h>
// tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <sys/ioctl.h>
 // ioctl
# include <dirent.h>
// opendir, readdir, closedir,
# include <sys/stat.h>
// stat, lstat, fstat
# include <errno.h>
/* exit, kill, chdir, , unlink, */


#endif

//getcwd >> useful to print the current directory path