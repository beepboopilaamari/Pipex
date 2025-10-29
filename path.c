/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaamari <ilaamari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 23:52:30 by ilaamari          #+#    #+#             */
/*   Updated: 2025/10/29 17:40:02 by ilaamari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_strdup(const char *s)
{
	char	*new;
	int		i;

	i = 0;
	while (s[i])
		i++;
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

static char	*ft_strjoin(char const *s1, char const *s2)
{
	int		sizetotal;
	char	*res;
	int		i;
	int		j;

	if (s1 && s2)
	{
		sizetotal = ft_strlen(s1) + ft_strlen(s2);
		res = malloc(sizeof(char) * (sizetotal + 1));
		if (res == NULL)
			return (NULL);
		i = 0;
		j = 0;
		while (s1[i])
			res[j++] = s1[i++];
		i = 0;
		while (s2[i])
			res[j++] = s2[i++];
		res[sizetotal] = '\0';
		return (res);
	}
	return (NULL);
}

static char	*join_path(char *path, char *cmd)
{
	char	*tmp;
	char	*exec;

	tmp = ft_strjoin(path, "/");
	exec = ft_strjoin(tmp, cmd);
	free(tmp);
	return (exec);
}

static char	*search_in_path(char *cmd, char **envp)
{
	char	**paths;
	int		i;
	char	*part_path;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4))
		i++;
	if (envp[i] == NULL)
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = join_path(paths[i], cmd);
		if (access(part_path, F_OK | X_OK) == 0)
		{
			free_array(paths);
			return (part_path);
		}
		free(part_path);
		i++;
	}
	free_array(paths);
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	*i;

	i = cmd;
	while (*i)
	{
		if (*i == '/')
		{
			if (access(cmd, F_OK | X_OK) == 0)
				return (ft_strdup(cmd));
			return (NULL);
		}
		i++;
	}
	return (search_in_path(cmd, envp));
}
