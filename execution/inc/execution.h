/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:18:23 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/07 03:17:32 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include"../../libtool/inc/libft.h"
# include"../../parsing/inc/parsing.h"

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
void	split_and_execute_cmd(t_minishell *mini);
/*print error and return the errno value to the exit status*/
int		error(char *er);
/*check if there is a input rederction*/
int		check_in_rdrct(t_list *cmd);
/*take the input rederction and make it the stander input*/
void	take_input(t_list *cmd, t_minishell *mini);
/*open the input file*/
void	open_input(char *file, int *fd);
/*open the heredoc*/
void	open_heredoc(t_list *lim, t_minishell *mini, int *fd);
/*check if there is an output rederction*/
int		check_out_rdrct(t_list *cmd);
/*open the output file*/
void	open_output(t_list *fl, int *fd);
/*take the output rederction and make it the stander output*/
void	take_output(t_list *cmd);
/*check if there is a command to execute*/
int		check_cmd(t_list *cmd);
/*count how many element of the command (command, arguments, flags)*/
int		count_cmd_prt(t_list *cmd);
/*take the command and there flags and arguments if they exisset and
stor them in a 2 demantional array*/
char	**take_char_cmd(t_list *cmd);
/*take the command path or return NULL if there is no executable file 
found*/
char	*take_path(char *cm, t_minishell *mini);
/*search for the node that got the paths and check if it is accessable
if not it return NULL else it return a 2 demantional array of the path
splited by ':'*/
char	**take_env_pths(t_list *en);
/*try to look if there is a path to the command and return it else it 
return NULL*/
char	*find_path(char	*cm, t_list *en);
/*take all the possible path in the envirement and test them one by one
if one of them work it return the path else it return NULL*/
char	*get_path(char **pth, char *cm);
/*execute the command line*/
void	execute_all(t_list **cmd, int ct, t_minishell *mini);
/*if there is only one command this function fork for it and execute it*/
void	execute_one(t_list *cmd, t_minishell *mini);
/*this function is called by the child process to execute the command*/
void	do_single_cmd(t_list *cmd, t_minishell *mini);
/*print the error and return the errno macro this function is used inside exit*/
int		error(char *er);
/*this function is used to in case of the command not found it print the error 
and deallocate the envirenment and the command and exit the process*/
void	cmd_not_found(char **en, char **cm);

#endif
