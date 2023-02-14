/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:32:59 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/14 18:02:16 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/built.h"

int	main(void)
{
	char	cd[PATH_MAX];

	if (getcwd(cd, sizeof(cd)))
		printf("%s\n", cd);
	else
		return (ft_printf("PWD: %s\n", 2, strerror(errno)), errno);
}
