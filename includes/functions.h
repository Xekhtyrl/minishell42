/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:08:12 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/06 18:49:05 by Gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "libft/headers/ft_printf.h"
# include "structures.h"

//______________________PARSING_______________________//
t_input		*parse(char *str, t_env *envp);
int			split_cmd(t_input **cmd, char *str, int start, t_env *envp);

//___________________PARSING_UTILS____________________//
int			is_white_space(char c);
int			is_not_sep(char c);
int			closed_quotes(char *str);
int			check_for_pipe(char *str);
int			get_token_type(char *c, int start);
int			parse_error(char *str);

//____________________PARSING_LST_____________________//
t_arg_lst	*arg_node(int type, char *token, t_env *envp);
t_input		*create_node(char *str, int type, t_env *envp);
void 		set_input(t_input *cmd, char *token, int type);

//________________________MAIN_________________________//
char		*pick_title();
void		print_input_lst(t_input	*input);

//_______________________SIGNAL________________________//
void		ctrl_c(int num);
void		ctrl_d(void);
void		set_signals(void);

//______________________EXECUTE________________________//
int			**fill_fd(t_input *input, int size);
int			execute_command(t_env **envp, t_input *cmd, int *pipe[2]);

//______________________EXECUTE2_______________________//
int			in_str_array(char *str,char **lst);
int			in_int_array(int t, int *l, int size);
int			trad_input(t_input *cmd, t_env **env);
char		**get_our_path(t_env *envp);
char		*get_cmd_path(t_env *envp, t_input *input);
void		mini_cls_fd(int fd1, int fd2);

//_______________________GET_FD________________________//
int			*get_fd_infiles(t_input *input, int size);
int			*get_fd_outfiles(t_input *input, int size);
int			open_infile(t_arg_lst *tmp);
int			open_outfile(t_arg_lst *tmp);

//________________________FREE_________________________//
void		strarray_free(char **built);
int			send_error(int flag);
void		close_pipes(int **pipe, int size);

//_______________________UTILS________________________//
void		push(t_env **lst1, t_env **lst2);
void		rotate(t_env **lst1);
void		sort_lst(t_env **lsta);
char		*ft_stradd(char *s1, char const *s2);
char		**lst_to_tab(t_list *lst);
char		**get_all_cmd(t_input *cmd, int len);
void		clear_arg(t_arg_lst **lst);
void		empty_args(t_input *input);

//________________________ENV_________________________//
t_env		*env_lst(char **envp);
t_env		*create_env_node(char *var, char *content, int flag, t_env *prev);
void		create_new_envar(char *var, char *content, int append, t_env *envp);
void		update_shell_lvl(t_env *envp);
int			replace_or_append(char *var, char *content, int append, t_env *envp);
char		*get_env_var(t_env *envp, char *var);
char		*replace_str_env_var(char *str, t_env *envp);
char		**get_env(t_env *envp);
void		print_env(char **envp);

//_______________________BUILT________________________//
void		ft_env(t_env *envp);
int			ft_echo(t_arg_lst *arg);
void		ft_cd(t_env *envp, t_arg_lst *arg);
void		ft_pwd();
int			ft_exit();
void		ft_unset(t_env	**envp, t_arg_lst *arg);
void		ft_export(t_arg_lst *arg, t_env *envp, int flag);

//________________________DUP_________________________//
int			uni_dup(int fd_in, int fd_out);
int			mini_dup(int *fd_in_out[2], int cur, t_cmd_info * inf, t_arg_lst *arg);
int			mini_dup2(int *fd_in_out[2], int cur, t_cmd_info * inf);
int			check_next_pipe(int *fd_in_out[2], int cur, t_cmd_info *inf);

//_______________________ECHO_________________________//
char	*trim_quote(char *str);

//_____________________HEREDOC_________________________//
int detect_all_heredocs(t_input *input);
int detect_heredoc(t_arg_lst *args);
char *get_heredoc(t_arg_lst *arg);
int heredoc(t_input *input);

#endif