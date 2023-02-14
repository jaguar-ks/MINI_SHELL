/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 03:52:08 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/14 00:28:12 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/libft.h"

t_list	*ft_lstmap(t_list *lst, char *(*f)(char *))
{
	t_list	*new;
	t_list	*r;

	if (!lst || !f)
		return (NULL);
	new = ft_lstnew((f)(lst->pt), 0);
	r = new;
	lst = lst->next;
	while (lst)
	{
		new = ft_lstnew((f)(lst->pt), 0);
		if (!new)
		{
			ft_lstclear(&lst);
			ft_lstclear(&r);
			return (NULL);
		}
		lst = lst->next;
		ft_lstadd_back(&r, new);
	}
	return (r);
}
