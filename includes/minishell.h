/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:09:46 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/28 16:21:57 by gfinet           ###   ########.fr       */
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

void		print_input_lst(t_input	*input);
//______________________PARSING_______________________//
t_input		*parse(char *str);
//___________________PARSING_UTILS____________________//
int			is_white_space(char c);
int			is_not_sep(char c);
int			closed_quotes(char *str);
int			check_for_pipe(char *str);
int			get_token_type(char *c, int start);
//____________________PARSING_LST_____________________//
t_arg_lst	*arg_node(int type, char *token);
t_input		*create_node(char *str, int type);

char	*pick_title();

//_______________________SIGNAL________________________//
void ctrl_c(int num);
void ctrl_d(void);
void set_signals(void);

//_______________________UTILS________________________//
void	push(t_env **lst1, t_env **lst2);
void	rotate(t_env **lst1);
void	sort_LSD_recursive(t_env **lsta, t_env **lstb, int msd);

void	ft_env(t_env *envp);
t_env	*env_lst(char **envp);
t_env	*create_env_node(char *var, char *content, int flag, t_env *prev);

#endif

//getcwd >> useful to print the current directory path