/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_needed_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:41:33 by faksouss          #+#    #+#             */
/*   Updated: 2023/04/11 03:27:39 by faksouss         ###   ########.fr       */
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




