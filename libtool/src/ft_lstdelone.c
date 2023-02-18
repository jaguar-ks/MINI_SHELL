/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 23:26:01 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/17 22:38:07 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/libft.h"

void	ft_lstdelone(t_list *lst)
{
	if (lst->pt)
		free(new->pt);
	if (lst)
		free(lst);
	return ;
}
