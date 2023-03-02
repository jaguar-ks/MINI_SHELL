/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 20:42:10 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/02 17:07:05 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/libft.h"

t_list	*ft_lstnew(char *wrd, int tp)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->pt = ft_strdup(wrd);
	new->wt = tp;
	new->acs = 1;
	new->next = NULL;
	return (new);
}

t_list	*dup_node(t_list *nd)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->pt = ft_strdup(nd->pt);
	new->wt = nd->wt;
	new->acs = nd->acs;
	new->next = NULL;
	return (new);
}
