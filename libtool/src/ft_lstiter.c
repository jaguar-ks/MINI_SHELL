/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 03:35:34 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/14 00:26:55 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/libft.h"

void	ft_lstiter(t_list *lst, void (*f)(char *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		(f)(lst->pt);
		lst = lst->next;
	}
}
