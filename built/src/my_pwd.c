/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:32:59 by faksouss          #+#    #+#             */
/*   Updated: 2023/04/04 03:58:46 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/built.h"

int	is_pwd(t_list *cmd)
{
	t_list	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->wt == CMD)
			if (!ft_strncmp(tmp->pt, "pwd", 4))
				return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	my_pwd(t_list *env)
{
	char	cd[PATH_MAX];
	t_list	*tmp;

	if (getcwd(cd, PATH_MAX))
	{
		ft_printf("%s\n", STDOUT_FILENO,cd);
		return ;
	}
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->pt, "PWD=", 4))
		{
			ft_printf("%s\n", STDOUT_FILENO, tmp->pt + 4);
			break ;
		}
		tmp = tmp->next;
	}
}
