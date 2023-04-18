/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:50:21 by faksouss          #+#    #+#             */
/*   Updated: 2023/04/17 02:48:18 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/built.h"

int	is_env(char *cmd)
{
	return (ft_strcmp(cmd, "env"));
}

void	my_env(t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->acs && ft_strchr(tmp->pt, '='))
			ft_printf("%s\n", STDOUT_FILENO, tmp->pt);
		tmp = tmp->next;
	}
}
