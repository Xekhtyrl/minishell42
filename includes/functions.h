/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:08:12 by gfinet            #+#    #+#             */
/*   Updated: 2024/04/29 00:09:25 by Gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "libft/headers/ft_printf.h"
# include "structures.h"

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
void 		set_input(t_input *cmd, char *token, int type);

char	*pick_title();

//_______________________SIGNAL________________________//
void ctrl_c(int num);
void ctrl_d(void);
void set_signals(void);

//______________________EXECUTE________________________//
int	fill_fd(int *pipe[2], t_input *input);
int	execute_command(t_env *envp, t_input *cmd, int *pipe[2]);

//______________________EXECUTE2_______________________//
int	in_list(char *str,char **lst);
int trad_input(t_input *cmd);
char	**get_our_path(t_env *envp);
char *get_cmd_path(t_env *envp, t_input *input);
void	mini_cls_fd(int fd1, int fd2, int fd3);

//_______________________GET_FD________________________//
int *get_fd_infiles(t_input *input, int size);
int *get_fd_outfiles(t_input *input, int size);
int open_infile(t_arg_lst *tmp);
int open_outfile(t_arg_lst *tmp);

//________________________FREE_________________________//
void strarray_free(char **built);
int	send_error(int flag);
void close_pipes(int *pipe[2], int size);

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

//_______________________UTILS________________________//
void	push(t_env **lst1, t_env **lst2);
void	rotate(t_env **lst1);
void	sort_lst(t_env **lsta);

//________________________ENV_________________________//
void	ft_env(t_env *envp);
t_env	*env_lst(char **envp);
t_env	*create_env_node(char *var, char *content, int flag, t_env *prev);
void ft_export();

//_______________________BUILT________________________//
int ft_echo();
int ft_cd();
int ft_pwd();
int ft_exit();
int ft_unset();
// int ft_export();

//________________________DUP_________________________//
int uni_dup(int fd_in, int fd_out);
int	mini_dup(int *fd_in_out[2], int cur);


int split_cmd(t_input **cmd, char *str, int start);
void	update_shell_lvl(t_env *envp);

#endif