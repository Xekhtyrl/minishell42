/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:09:46 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/24 21:26:53 by gfinet           ###   ########.fr       */
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
# include </Users/lvodak/.brew/Cellar/readline/8.2.10/include/readline/readline.h>
# include </Users/lvodak/.brew/Cellar/readline/8.2.10/include/readline/history.h>
# include "/Users/gfinet/homebrew/Cellar/readline/8.2.10/include/readline/readline.h"
# include "/Users/gfinet/homebrew/Cellar/readline/8.2.10/include/readline/history.h"
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
# define GREEN "\001\033[0;32m\x1b[1m\002"
# define LBLUE "\001\033[0;36m\x1b[1m\002"
# define BLUE "\001\033[0;34m\x1b[1m\002"
# define RED "\001\033[0;31m\x1b[1m\002"
# define WHITE "\001\033[0;30m\002"
# define NC "\001\033[0m\002"

# define WORD_TK 13
# define PIPE_TK 14
# define WRITE_TK 15
# define APPEN_TK 16
# define READ_TK 17
# define HEREDOC_TK 18
# define ENV_VAR_TK 19
# define SPACE_TK 20

typedef struct s_arg_lst
{
	struct s_arg_lst	*next;
	char				*token;
	int					type;
}	t_arg_lst;

typedef	struct s_input
{
	struct s_input		*next;
	char				*token;
	int					type;
	t_arg_lst			*arg;
}	t_input;

typedef struct s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	char			*var;
	char			*content;
	int				flag;
}	t_env;

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