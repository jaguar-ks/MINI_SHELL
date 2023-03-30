/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:17:06 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/30 22:32:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/mini_shell.h"

void	handl_segint_heredoc(int segnum)
{
	if (segnum == SIGINT)
	{
		g_ext_st = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		exit(EXT_ST);
	}
}

void	handl_segint(int segnum)
{
	if (segnum == SIGINT)
	{
		g_ext_st = 130 * 256;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	take_and_do_cmd(t_minishell *mini)
{
	take_cmd(mini);
	split_and_execute_cmd(mini);
	ft_lstclear(&mini->cmd);
}

void	mini_shell(t_minishell *mini)
{
	mini->prompt = inisialise_prompt();
	mini->line = readline(mini->prompt);
	if (!mini->line)
		out(mini);
	free(mini->prompt);
	if (!empty_line(mini->line))
		add_history(mini->line);
	if (check_syntax(mini->line) == 258)
		*mini->ext_st = error(NULL, 258) * 256;
	else if (!empty_line(mini->line))
		take_and_do_cmd(mini);
	free(mini->line);
}

int	main(int ac, char **av, char **en)
{
	t_minishell			mini;

	(void)ac;
	(void)av;
	if (!en[0])
	{
		ft_printf("Minishell : there is no envirenment !*#^&# 😡🤬\n", 2);
		exit(1);
	}
	mini.env = take_env(en);
	mini.ext_st = &g_ext_st;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handl_segint);
	while (1)
		mini_shell(&mini);
}
