/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deman_wolf <deman_wolf@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:41:33 by faksouss          #+#    #+#             */
/*   Updated: 2023/01/17 05:49:04 by deman_wolf       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*d;
	unsigned int	i;
	unsigned int	j;

	if (!s)
		return (NULL);
	if (len >= ft_strlen(s))
		j = ft_strlen(s);
	else
		j = len + 1;
	d = (char *)malloc(j * sizeof(char) + 1);
	if (!d)
		return (NULL);
	i = 0;
	if (start >= ft_strlen(s))
		d[i] = 0;
	while (s[start] && i < len)
		d[i++] = s[start++];
	d[i] = '\0';
	return (d);
}
