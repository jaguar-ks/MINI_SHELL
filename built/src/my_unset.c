/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 06:00:29 by faksouss          #+#    #+#             */
/*   Updated: 2023/04/04 03:58:15 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/built.h"

int	is_unset(t_list *cmd)
{
	t_list	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->wt == CMD)
			if (!ft_strncmp(tmp->pt, "unset", 5))
				return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	check_unset_syntax(char *str, int *ext_st)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (*ext_st = 1, 0);
	while (str[++i])
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (*ext_st = 1, 0);
	return (1);
}

int	is_the_target(char *str, char *env)
{
	int	i;

	i = 0;
	while (env[i] != '=' && env[i] != '\0')
	{
		if (str[i] && (str[i] != env[i]))
			return (0);
		i++;
	}
	if ((env[i] == '=' || env[i] == '\0') && (str[i] == '\0'))
		return (1);
	return (0);
}

void	unset_from_env(char *str, t_minishell *mini)
{
	t_list	*tmp;

	if (!check_unset_syntax(str, mini->ext_st))
	{
		ft_printf("%sMinishell : %s%s%s : %s%s\n", 2, RED, WHITE,
			"not a valid identifier", RED, str, WHITE);
		return ;
	}
	else if (!ft_strcmp(str, "_") || !ft_strcmp(str, "PWD"))
		return ;
	tmp = mini->env;
	while (tmp)
	{
		if (is_the_target(str, tmp->pt))
			tmp->acs = 0;
		tmp = tmp->next;
	}
}

void	my_unset(t_list *cmd, t_minishell *mini)
{
	char	**cm;
	int		i;

	cm = take_char_cmd(cmd);
	i = 0;
	while (cm[++i])
		unset_from_env(cm[i], mini);
	deallocate(cm);
}
