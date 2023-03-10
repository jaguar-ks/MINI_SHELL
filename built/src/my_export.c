/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 01:06:38 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/10 09:07:50 by faksouss         ###   ########.fr       */
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

void	print_export(t_list *exp)
{
	t_list	*tmp;

	sort_list(exp);
	tmp = exp;
	while (tmp)
	{
		if (tmp->acs && ft_strchr(tmp->pt, '='))
			ft_printf("declare - x %s\n", STDOUT_FILENO, tmp->pt);
		tmp = tmp->next;
	}
}

void	export_var(char *str, t_list **exp, t_minishell *mini)
{
	(void)exp;
	if (!check_export_syntax(str, &mini->ext_st))
		return ;
}

void	my_export(t_list *cmd, t_minishell *mini)
{
	char	**cm;
	t_list	*exp;
	int		i;

	cm = take_char_cmd(cmd);
	exp = NULL;
	take_export(&exp, mini->env);
	i = 0;
	if (!cm[1])
		print_export(exp);
	else
		while (cm[++i])
			export_var(cm[i], &exp, mini);
	ft_lstclear(&exp);
	deallocate(cm);
}
