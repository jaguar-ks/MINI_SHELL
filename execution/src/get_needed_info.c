/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_needed_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:41:33 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/20 02:22:42 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/execution.h"

int	check_out_rdrct(t_list *cmd)
{
	t_list	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->wt == TRNC || tmp->wt == APND)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	error(char *er, int ext_er)
{
	if (ext_er == 127)
		ft_printf("Minishell : command not found : %s\n", STDERR_FILENO, er);
	else if (ext_er == 1)
		ft_printf("Minishell : No such file or directory : %s\n",
			STDERR_FILENO, er);
	else if (ext_er == 258)
		ft_printf("Minishell : Syntax error\n", STDERR_FILENO);
	else
		ft_printf("Minishell : %s : %s\n", STDERR_FILENO, strerror(errno), er);
	return (ext_er);
}

void	cmd_not_found(char **cm)
{
	int	ext;

	ext = error(cm[0], 127);
	deallocate(cm);
	exit(ext);
}

int	how_many_pipe(t_list *cmd)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = cmd;
	while (tmp)
	{
		if (tmp->wt == PP)
			i++;
		tmp = tmp->next;
	}
	return (i + 1);
}

void	split_and_execute_cmd(t_minishell *mini)
{
	t_list	**cmd;
	int		i;
	int		j;

	i = how_many_pipe(mini->cmd);
	cmd = (t_list **)malloc(sizeof(t_list *) * (i + 1));
	if (!cmd)
		return ;
	j = -1;
	while (++j <= i)
		cmd[j] = single_cmd(mini);
	execute_all(cmd, i, mini);
}
