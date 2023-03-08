/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:50:21 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/08 05:02:55 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/built.h"

int	is_env(t_list *cmd)
{
	t_list	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->wt == CMD)
			if (!ft_strncmp(tmp->pt, "env", 4))
				return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	my_env(t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->acs)
			ft_printf("%s\n", STDOUT_FILENO, tmp->pt);
		tmp = tmp->next;
	}
}
