/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:17:06 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/14 18:40:09 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/mini_shell.h"

char	*pass_to_readline(void)
{
	char	cd[PATH_MAX];
	char	*ttl;
	int		i;

	i = 0;
	if (getcwd(cd, PATH_MAX) < 0)
		exit(errno);
	else
	{
		while (cd[i])
			i++;
		while (cd[i] != '/')
			i--;
		ttl = ft_strjoin("(", cd + i + 1);
		ttl = ft_strjoin(ttl, ")~> ");
	}
	return (ttl);
}

int	main(int ac, char **av, char **en)
{
	t_list	*env;
	char	*cd;
	char	*ln;

	if (ac == 1)
	{
		while (1)
		{
			cd = pass_to_readline();
			ln = readline(cd);
			if (!ln)
				return (errno);
		}
	}
}
