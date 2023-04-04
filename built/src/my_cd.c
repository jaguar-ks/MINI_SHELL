/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:56:39 by faksouss          #+#    #+#             */
/*   Updated: 2023/04/04 03:43:07 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/built.h"

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
			*mini->ext_st = error("cd", 1);
	}
	else
		*mini->ext_st = (ft_printf("%sMinishell : %sHOME not set : %scd%s\n", 2,
					RED, WHITE, RED, WHITE), 1 * 256);
}

void	update_oldpwd(t_minishell *mini)
{
	t_list	*tmp;
	char	*oldpwd;

	tmp = mini->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->pt, "PWD=", 4))
			oldpwd = ft_strjoin(ft_strdup("OLDPWD="), ft_strdup(tmp->pt + 4));
		tmp = tmp->next;
	}
	tmp = mini->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->pt, "OLDPWD=", 7))
		{
			free(tmp->pt);
			tmp->pt = oldpwd;
		}
		tmp = tmp->next;
	}
}

void	update_env(t_minishell *mini)
{
	t_list	*tmp;
	char	cw[PATH_MAX];

	if (!getcwd(cw, PATH_MAX))
	{
		*mini->ext_st = error("getcwd", 1);
		ft_printf("\tcan not retrive the current directory path\n", 2);
		return ;
	}
	update_oldpwd(mini);
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

void	my_cd(t_list *cmd, t_minishell *mini)
{
	char	**cm;

	cm = take_char_cmd(cmd);
	if (!cm[1])
		go_home(mini);
	else if (chdir(cm[1]) < 0)
		*mini->ext_st = error(cm[1], 1);
	deallocate(cm);
	update_env(mini);
}
