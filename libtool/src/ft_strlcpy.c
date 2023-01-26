/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deman_wolf <deman_wolf@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:47:10 by faksouss          #+#    #+#             */
/*   Updated: 2023/01/12 00:14:00 by deman_wolf       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/libft.h"

size_t	ft_strlcpy(char	*d, char *s, size_t ds)
{
	size_t	i;

	i = 0;
	if (ds == 0)
		return (ft_strlen(s));
	while (s[i] && i < ds - 1)
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (ft_strlen(s));
}
