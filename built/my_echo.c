/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:44:45 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/14 01:52:01 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/execution.h"

int	main(int ac, char **av)
{
	int		i;
	int		fd;

	if (ac > 1)
	{
		i = (ft_strncmp(av[1], "-n", 3) == 0 || ft_strncmp(av[1], "<<", 3) == 0);
		fd = 1;
		while (av[++i])
		{
			if (!ft_strncmp(av[i], "<<", 3) || !ft_strncmp(av[i], "<", 2))
				break ;
			if (av[i + 1] && av[i + 2] && (!ft_strncmp(av[i + 1], ">>", 3) || !ft_strncmp(av[i + 1], ">", 2)))
			{
				if (!ft_strncmp(av[i + 1], ">>", 3))
					fd = open(av[i + 2], O_CREAT, O_APPEND);
				else if (!ft_strncmp(av[i + 1], ">", 2))
					fd = open(av[i + 2], O_CREAT, O_TRUNC);
				if (fd < 0)
					return (0);
			}
			write(fd, av[i], ft_strlen(av[i]));
			if (av[i + 1])
				write(fd, " ", 1);
		}
		if (ft_strncmp(av[1], "-n", 3))
			write(fd, "\n", 1);
	}
	else
		write(fd, "\n", 1);
}
