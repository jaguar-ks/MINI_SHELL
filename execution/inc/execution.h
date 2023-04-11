/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:18:23 by faksouss          #+#    #+#             */
/*   Updated: 2023/04/11 03:21:44 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include"../../libtool/inc/libft.h"
# include"../../parsing/inc/parsing.h"
# include"../../built/inc/built.h"
# include"../../main/inc/mini_shell.h"

/*check if there is a input rederction*/
int		check_in_rdrct(t_list *cmd);
/*open the input file*/
void	open_input(char *file, int *fd);
/*open the heredoc*/
void	open_heredoc(t_list *lim, t_minishell *mini, int *fd);
/*check if there is an output rederction*/
int		check_out_rdrct(t_list *cmd);
/*open the output file*/
void	open_output(t_list *fl, int *fd);
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
/*print the error and return the ext_er this function is used inside
exit mosrtly*/
int		error(char *er, int ext_er);
/*this function is used to in case of the command not found it print the error 
and deallocate the command and exit the process*/
void	cmd_not_found(char **cm);
/*execute command line with multipel pipes*/
void	execute_mltpl_cmd(t_list **cmd, t_minishell *mini, int i);
/*open all rederection*/
void	open_rdrct(t_list *cmd, t_minishell *mini);

#endif
