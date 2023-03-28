/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 14:10:03 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/28 02:11:28 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/libft.h"

char	*take_line(char *r)
{
	char	*ln;
	int		i;

	if (!r || !ft_strlen(r))
		return (NULL);
	i = -1;
	if (!ft_strchr(r, '\n'))
		return (NULL);
	else
		i = ft_strchr(r, '\n') - r;
	ln = ft_substr(r, 0, i);
	return (ln);
}

char	*take_rest(char *r)
{
	char	*rst;
	int		i;

	if (!r)
		return (NULL);
	i = -1;
	if (!ft_strchr(r, '\n'))
		return (free(r), NULL);
	else
		i = (ft_strchr(r, '\n') - r);
	rst = ft_substr(r, i, ft_strlen(r) - i - 1);
	return (free(r), rst);
}

char	*gnl(int fd)
{
	int			i;
	static char	*r;
	char		*bf;
	char		*ln;

	i = 1;
	while (i && !ft_strchr(r, '\n'))
	{
		bf = (char *)malloc(2);
		i = read(fd, bf, 1);
		if (i < 0)
			return (free(bf), NULL);
		bf[i] = '\0';
		if (!ft_strlen(bf))
		{
			free(bf);
			break ;
		}
		r = ft_strjoin(r, bf);
	}
	return ((ln = take_line(r)), (r = take_rest(r)), ln);
}
