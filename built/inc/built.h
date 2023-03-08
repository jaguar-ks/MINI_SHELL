/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:58:41 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/08 05:46:28 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_H
# define BUILT_H

# include"../../libtool/inc/libft.h"
# include"../../parsing/inc/parsing.h"
# include"../../execution/inc/execution.h"

/*check if the command is a builtin command or not*/
int		check_builtin(char *cmd);
/*check if the command line if it have a builtin command*/
int		is_builtin(t_list *cmd);
/*if there is a single command check if should not fork for the command*/
int		should_not_fork(t_list *cmd);
/*execute a builting command*/
void	do_builtin(t_list *cmd, t_minishell *mini);
/*check if the flag -n chould work*/
int		check_echo_flg(char *flg);
/*repreduce the echo bihavior*/
void	my_echo(t_list *cmd);
/*check if the command is echo*/
int		is_echo(t_list *cmd);
/*repreduce the cd bihavior*/
void	my_cd(t_list *cmd, t_minishell *mini);
/*update the pwd in the envirenment*/
void	update_env(t_minishell *mini);
/*go to a speciphic path*/
void	go_to_path(t_minishell *mini, char *pth);
/*if cd is called whith out args go to home path*/
void	go_home(t_minishell *mini);
/*check if the command is cd*/
int		is_cd(t_list *cmd);
/*check if the command is pwd*/
int		is_pwd(t_list *cmd);
/*repreduce the pwd bihavior*/
void	my_pwd(t_list *env);
/*check if the command is env*/
int		is_env(t_list *cmd);
/*repreduce the env bihavior*/
void	my_env(t_list *env);
/*check if the command is exit*/
int		is_exit(t_list *cmd);
/*check if the argiment passed to exit is valid*/
int		valid_arg(char *arg);
/*repreduce the exit bihavior*/
void	my_exit(t_list *cmd, t_minishell *mini);

#endif
