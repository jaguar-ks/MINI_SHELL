/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:17:06 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/24 21:11:32 by faksouss         ###   ########.fr       */
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
		ttl = ft_strjoin(ft_strdup("("), ft_strdup(cd + i + 1));
		r = ft_strjoin(ttl, ft_strdup(")~> "));
	}
	return (r);
}

char	*print_type(int tp)
{
	if (tp == PP)
		return ("pipe");
	else if (tp == WRD)
		return ("word");
	else if (tp == QTS)
		return ("quots");
	else if (tp == INPT)
		return ("input");
	else if (tp == HEREDOC)
		return ("herdoc");
	else if (tp == APND)
		return ("apand");
	else if (tp == TRNC)
		return ("trunc");
	else if (tp == VRB)
		return ("variable");
	else if (tp == FLG)
		return ("flag");
	else if (tp == SP)
		return ("space");
	return ("indefind");
}

/*************TESTING*************/

/*********************************/

void	take_cmd(t_minishell *mini)
{
	t_list	*tmp;

	split_cmd_line_by_space(mini);
	// expander(mini);
	split_by_pp_and_rdrct(mini);
	tmp = mini->cmd;
	while (tmp)
	{
		printf("->[%s] [%s]\n", tmp->pt, print_type(tmp->wt));
		tmp = tmp->next;
	}
}

void	mini_shell(t_minishell *mini)
{
	// t_list	*tmp;

	mini->prompt = inisialise_prompt();
	mini->line = readline(mini->prompt);
	free(mini->prompt);
	if (!mini->line)
		out(mini);
	add_history(mini->line);
	mini->ext_st = check_syntax(mini->line);
	if (mini->ext_st == 256)
		printf("sysntax error afrida\n");
	else if (mini->ext_st == -1)
		printf("empty line afrida\n");
	else
		take_cmd(mini);
	free(mini->line);
	// tmp = mini->cmd;
	// while (mini->cmd)
	// {
	// 	printf("->[%s] [%s]\n", mini->cmd->pt, print_type(mini->cmd->wt));
	// 	mini->cmd = mini->cmd->next;
	// }
	// ft_lstclear(&tmp);
	system("leaks mini");
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
