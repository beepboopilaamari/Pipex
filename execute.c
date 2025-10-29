/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaamari <ilaamari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 23:52:39 by ilaamari          #+#    #+#             */
/*   Updated: 2025/10/29 17:41:23 by ilaamari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_cmd_error(char **cmd, char *path)
{
	if (!path)
	{
		perror(cmd[0]);
		free_array(cmd);
		exit(127);
	}
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	validate_cmd(argv);
	cmd = ft_split(argv, ' ');
	if (!cmd || !cmd[0])
	{
		free_array(cmd);
		exit(127);
	}
	path = find_path(cmd[0], envp);
	handle_cmd_error(cmd, path);
	if (execve(path, cmd, envp) == -1)
	{
		perror("execve");
		free_array(cmd);
		free(path);
		exit(127);
	}
}

void	validate_cmd(char *argv)
{
	if (!argv || argv[0] == '\0')
	{
		write(STDERR_FILENO, "command not found: \n", 20);
		exit(127);
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
