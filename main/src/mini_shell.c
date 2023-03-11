/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:17:06 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/11 06:06:30 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/mini_shell.h"

void	out(t_minishell *mini)
{
	ft_lstclear(&mini->env);
	free(mini->prompt);
	free(mini->line);
	// system("leaks minishell");
	ft_printf("exit\n", 1);
	exit(mini->ext_st / 255);
}

char	*inisialise_prompt(void)
{
	char		cd[PATH_MAX];
	char		*ttl;
	int			i;

	i = 0;
	if (!getcwd(cd, PATH_MAX))
		return (ft_strdup("(deleted directory)~> "));
	else
	{
		while (cd[i])
			i++;
		while (cd[i] != '/')
			i--;
		ttl = ft_strjoin(ft_strdup("("), ft_strjoin(ft_strdup(cd + i + 1),
				ft_strdup(")~> ")));
	}
	return (ttl);
}

/*************TESTING*************/

/*********************************/

void	take_cmd(t_minishell *mini)
{
	split_cmd_line_by_space(mini);
	split_by_pp_and_rdrct(mini);
	identify_special_charcters(mini);
	identify_rdrct(mini);
	expander(mini);
	identify_cmd(mini);
	remove_quotes(mini);
	identify_flag(mini);
	identify_arg(mini);
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
		mini->ext_st = error(NULL, 258) * 256;
	else if (!empty_line(mini->line))
		take_and_do_cmd(mini);
	free(mini->line);
	// system("leaks minishell");
}

int	main(int ac, char **av, char **en)
{
	t_minishell	mini;

	(void)ac;
	(void)av;
	mini.env = take_env(en);
	while (1)
		mini_shell(&mini);
}
