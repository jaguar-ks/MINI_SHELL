/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_main_fncts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:59:12 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/16 10:59:12 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/mini_shell.h"

void	out(t_minishell *mini)
{
	ft_lstclear(&mini->env);
	free(mini->prompt);
	free(mini->line);
	ft_printf("exit\n", 1);
	exit(*mini->ext_st / 255);
}

char	*inisialise_prompt_2(void)
{
	char		cd[PATH_MAX];
	char		*ttl;
	int			i;

	i = 0;
	if (!getcwd(cd, PATH_MAX))
		return (ft_strjoin(ft_strdup("\001\e[31;1m\002❮\001\e[33;1;3m\002deleted "),
				ft_strdup("directory\001\e[31;1m\002❯ $➣\001\e[0m\002 ")));
	else
	{
		while (cd[i])
			i++;
		while (cd[i] != '/')
			i--;
		ttl = ft_strjoin(ft_strdup("\001\e[31;1m\002❮\001\e[33;1;3m\002"),
				ft_strjoin(ft_strdup(cd + i + 1),
					ft_strjoin(ft_strdup("\001\e[31;1m\002❯"),
						ft_strjoin(ft_strdup("❨\001\e[32;3;1m\002"),
							ft_strjoin(ft_itoa(g_ext_st),
								ft_strdup("\001\e[31;1m\002❩ $➣ \001\e[0m\002 "))))));
	}
	return (ttl);
}

char	*inisialise_prompt(void)
{
	char		cd[PATH_MAX];
	char		*ttl;
	int			i;

	i = 0;
	if (!getcwd(cd, PATH_MAX))
		return (ft_strdup("❮deleted directory❯ $➣ "));
	else
	{
		while (cd[i])
			i++;
		while (cd[i] != '/')
			i--;
		ttl = ft_strjoin(ft_strdup("❮"),
				ft_strjoin(ft_strdup(cd + i + 1),
					ft_strjoin(ft_strdup("❯"),
						ft_strjoin(ft_strdup("❨"),
							ft_strjoin(ft_itoa(g_ext_st / 256),
								ft_strdup("❩ $➣ "))))));
	}
	return (ttl);
}

void	take_cmd(t_minishell *mini)
{
	mini->cmd = NULL;
	split_cmd_line_by_space(mini);
	split_by_pp_and_rdrct(mini);
	identify_special_charcters(mini);
	identify_rdrct(mini);
	expander(mini);
	identify_cmd(mini);
	remove_quotes(mini);
	identify_flag(mini);
	identify_arg(mini);
	extract_wild_card(mini);
}
