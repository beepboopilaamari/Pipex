/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaamari <ilaamari@42nice.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 23:52:39 by ilaamari          #+#    #+#             */
/*   Updated: 2025/07/05 23:52:39 by ilaamari         ###   ########.fr       */
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
	cmd = split(argv, ' ');
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
