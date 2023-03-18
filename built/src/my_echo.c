/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:44:45 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/18 15:05:52 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/built.h"

int	is_echo(t_list *cmd)
{
	t_list	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->wt == CMD)
			if (!ft_strncmp(tmp->pt, "echo", 5))
				return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	check_echo_flg(char *flg)
{
	int	i;

	i = 1;
	while (flg[i] == 'n')
		i++;
	if (flg[i] == '\0' && i > 1)
		return (1);
	else
		return (0);
}

void	my_echo(t_list *cmd)
{
	char	**cm;
	int		i;

	i = 0;
	cm = take_char_cmd(cmd);
	while (cm[++i])
		if (!(cm[i] && check_echo_flg(cm[i])))
			break ;
	i -= 1;
	while (cm[++i])
	{
		write(STDOUT_FILENO, cm[i], ft_strlen(cm[i]));
		if (cm[i + 1])
			write(STDOUT_FILENO, " ", 1);
	}
	if (!(cm[1] && check_echo_flg(cm[1])))
		write(STDOUT_FILENO, "\n", 1);
	deallocate(cm);
}
