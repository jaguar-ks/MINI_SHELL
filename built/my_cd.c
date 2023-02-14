/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:56:39 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/14 16:37:08 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/execution.h"

int	main(int ac, char **av, char **en)
{
	int	i;

	i = -1;
	if (ac == 1)
	{
		while (en[++i])
		{
			if (!ft_strncmp(en[i], "HOME=", 5))
			{
				if (chdir(en[i] + 5) < 0)
					return (ft_printf("CD: %s\n", 2, strerror(errno)), errno);
				else
					return (0);
			}
		}
		if (!en[i])
			return (0);
	}
	else if (ac == 2)
		if (chdir(av[1]) < 0)
			return (ft_printf("CD: %s: %s\n", 2, strerror(errno), av[1]), errno);
}
