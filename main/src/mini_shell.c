/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:17:06 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/17 23:24:38 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/mini_shell.h"

void	out(t_minishell *mini)
{
	ft_lstclear(&mini->env);
	ft_lstclear(&mini->cmd);
	free(mini->prompt);
	exit(0);
}

char	*inisialise_prompt(void)
{
	char		cd[PATH_MAX];
	char		*ttl;
	static char	*r;
	int			i;

	i = 0;
	if (getcwd(cd, PATH_MAX) < 0)
		return (r);
	else
	{
		while (cd[i])
			i++;
		while (cd[i] != '/')
			i--;
		ttl = ft_strjoin("(", cd + i + 1);
		r = ft_strjoin(ttl, ")~> ");
		free(ttl);
	}
	return (r);
}

void	mini_shell(t_minishell *mini, char **en)
{
	mini->prompt = inisialise_prompt();
	mini->line = readline(mini->prompt);
	free(mini->prompt);
	if (!mini->line)
		out(mini);
	add_history(mini->line);
	mini->cmd = parss_command_line(mini);
	free(mini->line);
}

int	main(int ac, char **av, char **en)
{
	t_minishell	mini;

	(void)ac;
	(void)av;
	mini.env = take_env(en);
	while (1)
		mini_shell(&mini, en);
}
