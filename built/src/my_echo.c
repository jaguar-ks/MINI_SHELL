/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:44:45 by faksouss          #+#    #+#             */
/*   Updated: 2023/04/21 11:22:41 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/built.h"

int	is_echo(char *cmd)
{
	return ((ft_strcmp(cmd, "echo") == 0));
}

int	check_echo_flg(char *flg)
{
	int	i;

	i = 1;
	while (flg[i] == 'n')
		i++;
	if (flg[0] == '-' && flg[i] == '\0' && i > 1)
		return (1);
	else
		return (0);
}

void	my_echo(t_exec *cmd)
{
	int		i;

	i = 0;
	while (cmd->cmd_exec[++i])
		if (!(cmd->cmd_exec[i] && check_echo_flg(cmd->cmd_exec[i])))
			break ;
	i -= 1;
	while (cmd->cmd_exec[++i])
	{
		write(STDOUT_FILENO, cmd->cmd_exec[i], ft_strlen(cmd->cmd_exec[i]));
		if (cmd->cmd_exec[i + 1])
			write(STDOUT_FILENO, " ", 1);
	}
	if (!(cmd->cmd_exec[1] && check_echo_flg(cmd->cmd_exec[1])))
		write(STDOUT_FILENO, "\n", 1);
}
