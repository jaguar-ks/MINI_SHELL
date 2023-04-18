/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 06:00:29 by faksouss          #+#    #+#             */
/*   Updated: 2023/04/17 02:58:12 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/built.h"

int	is_unset(char *cmd)
{
	return (ft_strcmp(cmd, "unset"));
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
	char	*key;

	if (ft_strchr(env, '='))
		key = ft_substr(env, 0, ft_strchr(env, '=') - env);
	else
		key = ft_strdup(env);
	if (!ft_strcmp(key, str))
		return (free(key), 1);
	free(key);
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
		{
			printf("-> %s\n", tmp->pt);
			tmp->acs = 0;
		}
		tmp = tmp->next;
	}
}

void	my_unset(t_exec *cmd, t_minishell *mini)
{
	int		i;

	i = 0;
	while (cmd->cmd_exec[++i])
		unset_from_env(cmd->cmd_exec[i], mini);
}
