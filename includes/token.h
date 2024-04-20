/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:05:00 by gfinet            #+#    #+#             */
/*   Updated: 2024/04/20 17:15:20 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# define GREEN "\033[0;32m\x1b[1m"
# define LBLUE "\033[0;36m\x1b[1m"
# define BLUE "\033[0;34m\x1b[1m"
# define RED "\033[0;31m\x1b[1m"
# define WHITE "\033[0;30m"
# define NC "\033[0m"

# define BUILT_TK 12
# define WORD_TK 13
# define PIPE_TK 14
# define WRITE_TK 15
# define APPEN_TK 16
# define READ_TK 17
# define HEREDOC_TK 18
# define ENV_VAR_TK 19

#endif