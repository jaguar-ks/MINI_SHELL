/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 01:06:38 by faksouss          #+#    #+#             */
/*   Updated: 2023/04/04 03:53:41 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/built.h"

int	is_export(t_list *cmd)
{
	t_list	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->wt == CMD)
			if (!ft_strncmp(tmp->pt, "export", 7))
				return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	print_export(t_minishell *mini)
{
	t_list	*tmp;
	t_list	*exprt;

	exprt = NULL;
	take_export(&exprt, mini->env);
	sort_list(exprt);
	tmp = exprt;
	while (tmp)
	{
		if (tmp->acs)
			ft_printf("%sdeclare - x %s%s\n", STDOUT_FILENO, GREEN,
				WHITE, tmp->pt);
		tmp = tmp->next;
	}
	ft_lstclear(&exprt);
}

void	export_var(char *str, t_minishell *mini)
{
	char	*key;
	char	*val;
	int		tp;
	int		acs;

	if (!check_export_syntax(str, mini->ext_st))
		return ;
	key = NULL;
	val = NULL;
	tp = 0;
	take_key_and_val(str, &key, &val, &tp);
	if (!ft_strcmp(key, "_"))
		return ;
	if (already_exists(mini->env, key, &acs))
	{
		if (acs && tp)
			change_env_prt(mini, key, val, tp);
		else if (!acs)
			bring_back_env_prt(mini, key, val, tp);
	}
	else
		add_new_env_prt(mini, key, val, tp);
	free(key);
	if (val)
		free(val);
}

void	my_export(t_list *cmd, t_minishell *mini)
{
	char	**cm;
	int		i;

	cm = take_char_cmd(cmd);
	i = 0;
	if (!cm[1])
		print_export(mini);
	else
	{
		while (cm[++i])
			export_var(cm[i], mini);
	}
	deallocate(cm);
}
