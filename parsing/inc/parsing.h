/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:55:39 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/22 19:42:46 by faksouss         ###   ########.fr       */
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
# define QTS 13
# define EN 14

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
int		take_quotes(t_minishell *mini, t_list **cmd, int i);
char	*take_double_qts(t_minishell *mini, int i);
/*take Dollar*/
int		take_var(t_minishell *mini, int i);
char	*take_dollar(t_minishell *mini, int *i);
int		check_expand(char *str);
char	*expan_variable(char *var, t_minishell *mini);
/*take rediraction*/
int		take_rediraction(t_minishell *mini, t_list **cmd, int i);
int		take_input(t_minishell *mini, t_list **cmd, int i);
int		take_input_fl(t_minishell *mini, t_list **cmd, int i);
void	take_heredoc(t_minishell *mini, t_list **cmd, int *i);
char	*take_lemiter(t_minishell *mini, int *i);
int		take_output(t_minishell *mini, t_list **cmd, int i);
int		take_outfile(t_minishell *mini, t_list **cmd, int i, int tp);
/*take pipe*/
int		take_pipe(t_minishell *mini, t_list **cmd, int i);
/*take flag*/
int		take_flag(t_minishell *mini, t_list **cmd, int i);
/*skiping white spaces*/
int		skip_white_spaces(t_minishell *mini, int i);
void	parss_command_line(t_minishell *mini);
char	*take_wrd(t_minishell *mini, int *i);
int		take_word(t_minishell *mini, int i);

#endif
