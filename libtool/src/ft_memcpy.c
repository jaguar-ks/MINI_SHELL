/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deman_wolf <deman_wolf@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:13:23 by faksouss          #+#    #+#             */
/*   Updated: 2023/01/12 00:14:00 by deman_wolf       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/libft.h"

void	*ft_memcpy(void *d, const void *s, size_t l)
{
	size_t	i;

	i = 0;
	if (!d && !s)
		return (NULL);
	while (i < l)
	{
		((char *)d)[i] = ((char *)s)[i];
		i++;
	}
	return (d);
}
