/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:50:21 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/06 19:44:04 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/execution.h"

int	main(int ac, char **av, char **en)
{
	if (ac == 1 && !ft_strncmp((av[0] + 2), "env_f", 6))
	{
		while (*en)
			printf("%s\n", *en++);
	}
}