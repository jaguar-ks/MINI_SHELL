/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:55:39 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/18 02:40:40 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include"../../libtool/inc/libft.h"

# define EMPTY 0
# define HEREDOC 1
# define CMD 2
# define FL 3
# define APND 4
# define TRNC 5
# define INPT 6
# define FLG 7
# define VRB 8
# define PP 9
# define LM 10
# define ARG 11
# define WRD 12
# define QTS 12
# define ENV 13

/*Store the environment*/
t_list	*take_env(char **en);
/*checking if quotes are valide*/
int		valid_ct(char *cl);
/*take qoutes*/
void	take_quotes(t_minishell *mini, t_list **cmd, int *i);
/*take dollar*/
char	*take_dollar(t_minishell *mini, int *i);
/*check if you should try expand Dollar $*/
int		check_expand(char *str);
/*try expand the variable*/
char	*expan_variable(char *var, t_minishell *mini);

#endif
