/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 05:12:41 by faksouss          #+#    #+#             */
/*   Updated: 2023/04/04 03:51:57 by faksouss         ###   ########.fr       */
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
		*mini->ext_st = (ft_printf("exit\n%sMinishell : %s%s : %sexit%s\n",
					STDERR_FILENO, RED, WHITE, "too many arguments",
					RED, WHITE), 1);
		return ;
	}
	ft_printf("exit\n", STDERR_FILENO);
	if (cm[1])
	{
		if (valid_arg(cm[1]))
			ext = ft_atoi(cm[1]);
		else
			ext = (ft_printf("%sMinishell : %s%s : %s%s%s\n", STDERR_FILENO,
						RED, WHITE, "numeric arguments is required", RED, cm[1],
						WHITE), 2);
	}
	deallocate(cm);
	exit(ext);
}
