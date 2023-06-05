/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 05:12:41 by faksouss          #+#    #+#             */
/*   Updated: 2023/04/18 11:09:57 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/built.h"

int	mtx_len(char **mx)
{
	int	i;

	i = 0;
	while (mx[i])
		i++;
	return (i);
}

int	is_exit(char *cmd)
{
	return ((ft_strcmp(cmd, "exit") == 0));
}

int	valid_arg(char *arg)
{
	int	i;

	i = -1 + (arg[0] == '-');
	while (arg[++i])
		if (!ft_isdigit(arg[i]))
			return (0);
	return (1);
}

void	my_exit(t_exec *cmd, t_minishell *mini)
{
	long	ext;

	ext = 0;
	if (mtx_len(cmd->cmd_exec) > 2)
	{
		*mini->ext_st = (ft_printf("exit\nMinishell : %s : exit\n",
					STDERR_FILENO, "too many arguments"), 1);
		return ;
	}
	ft_printf("exit\n", STDERR_FILENO);
	if (cmd->cmd_exec[1])
	{
		if (valid_arg(cmd->cmd_exec[1]))
			ext = ft_atoi(cmd->cmd_exec[1]);
		else
			ext = (ft_printf("Minishell : %s : %s\n", STDERR_FILENO,
						"numeric arguments is required", cmd->cmd_exec[1],
						WHITE), 2);
	}
	exit(ext);
}
