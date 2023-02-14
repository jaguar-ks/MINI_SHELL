/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mini_Shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:52:20 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/13 22:11:02 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/parcing.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>

int	main(int ac, char **av, char **en)
{
	char	cd[PATH_MAX];
	char	**nm;
	char	*ms;
	char	*cmd_ln;
	int		i;

	while (1)
	{
		i = 0;
		if (getcwd(cd, sizeof(cd)))
		{
			nm = ft_split(cd, '/');
			while (nm[i + 1])
				i++;
			ms = ft_strjoin("(", nm[i]);
			ms = ft_strjoin(ms, ")~> ");
			cmd_ln = readline(ms);
			if (!cmd_ln)
				return (1);
		}
		else
			return (1);
	}
}
