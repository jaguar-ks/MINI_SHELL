/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:48:38 by mfouadi           #+#    #+#             */
/*   Updated: 2023/04/10 23:41:34 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char *find_cmd(char **path, char *cmd)
{
	char *tmp;
	char *tmp1;

	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		perror("minishell");
		exit(127);
	}
	while (path && *path)
	{
		tmp = ft_strjoin(*path, "/");
		tmp1 = ft_strjoin(tmp, cmd);
		if (access(tmp1, F_OK | X_OK) == 0)
			return (tmp1);
		free(tmp1);
		path++;
	}
	perror("minishell");
	exit(127);
	return (NULL);
}

char	*get_cmd_path(t_minishell *mini, char *cmd)
{
	char **path;
	t_list *tmp;

	path = NULL;
	tmp = mini->env;
	while (tmp)
	{
		if (tmp->acs)
			if (ft_strncmp(tmp->pt, "PATH=", 5) == 0)
			{
				path = ft_split(tmp->pt+5, ':');
				break;
			}
		tmp = tmp->next;
	}
	if (!path)
	{
		perror("minishell:"); *mini->ext_st = 127; exit(127);
	}
	return (find_cmd(path, cmd));
}

char	**convert_env(t_list *env)
{
	char **env_d;
	t_list *tmp;
	int i;
	env_d = NULL;
	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	env_d = (char **)malloc(sizeof(char *) * (i + 1));
	env_d[i] = NULL;
	tmp = env;
	int j = 0;
	i = 0;
	while (tmp)
	{
		i = ft_strlen(tmp->pt);
		env_d[j] = (char *)malloc(i + 1);
		env_d[j][i] = '\0';
		ft_memcpy(env_d[j], tmp->pt, i);
		tmp = tmp->next;
		j++;
	}
	return (env_d);
}
