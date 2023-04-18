/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:55:39 by faksouss          #+#    #+#             */
/*   Updated: 2023/04/18 09:21:51 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include"../../libtool/inc/libft.h"

# define HEREDOC 1
# define LMTR 2
# define APND 3
# define TRNC 4
# define INPT 5
# define PP 6
# define IND 7
# define ARG 8
# define EN 9
# define AP_F 10
# define TR_F 11
# define IN_F 12
# define CMD 13
# define FLG 14

/*check synstax*/
int		check_syntax(char *line);
/*check if the line is empty*/
int		empty_line(char *line);
/*check if the pipes are valid*/
int		valid_pipe(char *line);
/*check if the redirections is valid*/
int		valid_rediraction(char *line);
/*check if the output file is valid*/
int		check_output(char *line, int i);
/*check if the input file is valid*/
int		check_input(char *line, int i);
/*check if the herdoc is valid*/
int		check_heredoc(char *line, int i);
/*check if the character is inside the quotes or outside*/
int		in_quotes(char *line, int i);
/*check if the quotes are valid*/
int		valid_ct(char *cl);
/*Store the environment*/
t_list	*take_env(char **en);
/*take Dollar signe*/
char	*take_dollar(t_minishell *mini, char *line, int *i);
/*check if the dollar signe should be expanded or nitt*/
int		check_expand(char *str);
/*try expan the dolar signe*/
char	*expan_variable(char *var, t_minishell *mini);
/*skiping white spaces*/
int		skip_white_spaces(t_minishell *mini, int i);
/*check if the string should be splited or not*/
int		should_be_splited(char *str);
/*take  the pipe or redirections and put them in a node*/
void	take_pp_or_rdrct(char *str, int *i, t_list **new);
/*if the string contain the special character it splite it and put in nodes*/
void	add_to_new_list(t_list **new, char *str);
/*split the strings by '|', '<', '>', '>>' and '<<'*/
void	split_by_pp_and_rdrct(t_minishell *mini);
/*check if the '$' signe should be expanded or not*/
int		check_for_expander(t_list *prt);
/*take the variable and replace it by it's value*/
char	*expand_var(t_minishell *mini, char *old_str);
/*check if there is a variable should be expanded and epand it*/
void	expander(t_minishell *mini);
/*split the command by spaces that ain't in quotes*/
void	split_cmd_line_by_space(t_minishell *mini);
/*locate <, <<, >, >> and |*/
void	identify_special_charcters(t_minishell *mini);
/*locate the redirections herdoc, input, output ...*/
void	identify_rdrct(t_minishell *mini);
/*locate the command*/
void	identify_cmd(t_minishell *mini);
/*locate command's flag*/
void	identify_flag(t_minishell *mini);
/*locate command's arguments*/
void	identify_arg(t_minishell *mini);
/*remove the qouts and expand if needed*/
void	remove_quotes(t_minishell *mini);
/*check if there is a '*' in the arguiment string*/
int		should_be_extracted(char *str);
/*repreducing the bihavior of wildcard*/
void	extract_wild_card(t_minishell *mini);
/*extract and add to the list*/
void	extract_and_add_to_list(t_list **new_lst, char *ex);
/*check if the file match the wildcard*/
int		is_a_match(char *name, char *pattren);
/* merge stras*/
char	*merge_star(char *str);
/*calculate the len of the accessable parts of envirement*/
int		env_len(t_list *en);
/*take the accessable parts of the enviremants and store them in
2 demantional array of type char*/
char	**take_char_env(t_list *en);
/*take single command at the time*/
t_list	*single_cmd(t_minishell *mini);
/*calculate how many pipe in the command*/
int		how_many_pipe(t_list *cmd);
/*split the command line by pipe*/
t_list	**split_cmd_list(t_minishell *mini);
/*check if there is a command to execute*/
int		check_cmd(t_list *cmd);
/*count how many element of the command (command, arguments, flags)*/
int		count_cmd_prt(t_list *cmd);
/*take the command and there flags and arguments if they exisset and
stor them in a 2 demantional array*/
char	**take_char_cmd(t_list *cmd);
/*initialise the linked list for execution*/
void	init_exc(t_minishell *mini);
/*command not found*/
void	cmd_not_found(char **cm);
/*error printing*/
int		error(char *er, int ext_er);

#endif
