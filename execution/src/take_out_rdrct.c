/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_out_rdrct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 01:39:26 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/09 01:17:59 by faksouss         ###   ########.fr       */
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

void	open_output(t_list *fl, int *fd)
{
	if (fl->wt == TR_F)
		*fd = open(fl->pt, (O_CREAT | O_TRUNC | O_WRONLY), 0777);
	else if (fl->wt == AP_F)
		*fd = open(fl->pt, (O_CREAT | O_APPEND | O_WRONLY), 0777);
	if (*fd < 0)
		exit(error(fl->pt, 1));
}

void	take_output(t_list *cmd)
{
	int		fd;
	t_list	*tmp;

	tmp = cmd;
	fd = -1;
	while (tmp)
	{
		if (tmp->wt == APND || tmp->wt == TRNC)
			open_output(tmp->next, &fd);
		tmp = tmp->next;
	}
	if (fd > 0)
		dup2(fd, STDOUT_FILENO);
}
