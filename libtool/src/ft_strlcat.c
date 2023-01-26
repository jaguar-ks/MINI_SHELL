/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deman_wolf <deman_wolf@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:19:58 by faksouss          #+#    #+#             */
/*   Updated: 2023/01/12 00:14:00 by deman_wolf       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	unsigned int	i;
	unsigned int	ds;
	unsigned int	ss;

	ss = ft_strlen(src);
	if (!dest && !size)
		return (ss);
	i = 0;
	ds = ft_strlen(dest);
	if (size <= ds)
		return (size + ss);
	while (src[i] && i < size - ds - 1)
	{
		dest[ds + i] = src[i];
		i++;
	}
	dest[ds + i] = '\0';
	return (ds + ss);
}
