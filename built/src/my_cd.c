/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:56:39 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/08 04:43:54 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/built.h"

// int	main(int ac, char **av, char **en)
// {
// 	int	i;

// 	i = -1;
// 	if (ac == 1)
// 	{
// 		while (en[++i])
// 		{
// 			if (!ft_strncmp(en[i], "HOME=", 5))
// 			{
// 				if (chdir(en[i] + 5) < 0)
// 					return (ft_printf("CD: %s\n", 2, strerror(errno)), errno);
// 				else
// 					return (0);
// 			}
// 		}
// 		if (!en[i])
// 			return (0);
// 	}
// 	else if (ac == 2)
// 		if (chdir(av[1]) < 0)
// 			return (ft_printf("CD: %s: %s\n", 2, strerror(errno), av[1]), errno);
// }

int	is_cd(t_list *cmd)
{
	t_list	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->wt == CMD)
			if (!ft_strncmp(tmp->pt, "cd", 3))
				return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	go_home(t_minishell *mini)
{
	t_list	*tmp;

	tmp = mini->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->pt, "HOME=", 5))
			if (tmp->acs)
				break ;
		tmp = tmp->next;
	}
	if (tmp)
	{
		if (chdir(tmp->pt + 5) < 0)
		{
			mini->ext_st = 1;
			error("cd");
		}
	}
	else
		mini->ext_st = (ft_printf("Minishell : HOME not set : cd\n", 2), 1);
}

void	go_to_path(t_minishell *mini, char *pth)
{
	if (chdir(pth) < 0)
	{
		error(pth);
		mini->ext_st = 1;
	}
}

void	update_env(t_minishell *mini)
{
	t_list	*tmp;
	char	cw[PATH_MAX];

	if (!getcwd(cw, PATH_MAX))
	{
		error("getcwd");
		ft_printf("can not retrive the current directory path\n", 2);
		mini->ext_st = 1;
		return ;
	}
	else
	{
		tmp = mini->env;
		while (tmp)
		{
			if (!ft_strncmp(tmp->pt, "PWD=", 4))
			{
				free(tmp->pt);
				tmp->pt = ft_strjoin(ft_strdup("PWD="), ft_strdup(cw));
			}
			tmp = tmp->next;
		}
	}
}

void	my_cd(t_list *cmd, t_minishell *mini)
{
	char	**cm;

	cm = take_char_cmd(cmd);
	if (!cm[1])
		go_home(mini);
	else
		go_to_path(mini, cm[1]);
	update_env(mini);
}
