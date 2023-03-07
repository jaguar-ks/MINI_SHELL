/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:37:02 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/07 19:51:31 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*cr;

	if (lst)
	{
		if (*lst)
		{
			cr = ft_lstlast(*lst);
			cr->next = new;
		}
		else
			*lst = new;
	}
}
