/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:56:39 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/14 15:43:23 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/execution.h"

int	main(int ac, char **av, char **en)
{
	int	i;

	i = 0;
	if (ac == 1)
	{
		while (ft_strncmp(en[i], "HOME=", 5))
			i++;
		if (chdir(en[i] + 5) < 0)
			return (perror("CD"), errno);
	}
	else if (ac == 2)
		if (chdir(av[1]) < 0)
			return (perror("CD"), errno);
}
