/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:55:39 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/21 16:18:36 by faksouss         ###   ########.fr       */
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

/*check synstax*/
int		check_syntax(char *line);
int		empty_line(char *line);
int		valid_pipe(char *line);
int		valid_rediraction(char *line);
int		check_output(char *line, int i);
int		check_input(char *line, int i);
int		check_heredoc(char *line, int i);
int		in_quotes(char *line, int i);
int		valid_ct(char *cl);
/*Store the environment*/
t_list	*take_env(char **en);
/*take qoutes*/
void	take_quotes(t_minishell *mini, t_list **cmd, int *i);
char	*take_double_qts(t_minishell *mini, int i);
/*take Dollar*/
char	*take_dollar(t_minishell *mini, int *i);
int		check_expand(char *str);
char	*expan_variable(char *var, t_minishell *mini);
/*take rediraction*/
void	take_redirection(t_minishell *mini, t_list **cmd, int *i);
void	take_input(t_minishell *mini, t_list **cmd, int *i);
void	take_input_fl(t_minishell *mini, t_list **cmd, int *i);
void	take_heredoc(t_minishell *mini, t_list **cmd, int *i);
char	*take_lemiter(t_minishell *mini, int *i);
void	take_output(t_minishell *mini, t_list **cmd, int *i);
void	take_outfile(t_minishell *mini, t_list **cmd, int *i, int tp);
/*skiping white spaces*/
void	skip_white_spaces(t_minishell *mini, int *i);

#endif
