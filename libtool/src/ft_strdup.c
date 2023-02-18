/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:26:18 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/17 22:06:38 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*d;

	i = -1;
	if (!s)
		return (NULL);
	d = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!d)
		return (NULL);
	while (s[++i])
		d[i] = s[i];
	d[i] = '\0';
	return (d);
}
