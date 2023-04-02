/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 05:12:41 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/30 21:16:31 by marvin           ###   ########.fr       */
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

int	is_exit(t_list *cmd)
{
	t_list	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->wt == CMD)
			if (!ft_strncmp(tmp->pt, "exit", 5))
				return (1);
		tmp = tmp->next;
	}
	return (0);
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

void	my_exit(t_list *cmd, t_minishell *mini)
{
	char	**cm;
	long	ext;

	cm = take_char_cmd(cmd);
	ext = 0;
	if (mtx_len(cm) > 2)
	{
		deallocate(cm);
		*mini->ext_st = (ft_printf("exit\nMinishell : %s : exit\n",
					STDERR_FILENO, "too many arguments"), 1 * 256);
		return ;
	}
	ft_printf("exit\n", STDERR_FILENO);
	if (cm[1])
	{
		if (valid_arg(cm[1]))
			ext = ft_atoi(cm[1]);
		else
			ext = (ft_printf("Minishell : %s : %s\n",
						STDERR_FILENO, "numeric arguments is required",
						cm[1]), 255);
	}
	deallocate(cm);
	exit(ext);
}
