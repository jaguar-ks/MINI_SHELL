/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:32:59 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/14 14:41:13 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/execution.h"

int	main(void)
{
	char	cd[PATH_MAX];

	if (getcwd(cd, sizeof(cd)))
		printf("%s\n", cd);
	else
		perror("MINI_SHELL:");
}
