/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaamari <ilaamari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 23:52:05 by ilaamari          #+#    #+#             */
/*   Updated: 2025/11/03 18:58:32 by ilaamari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(t_pipex data, char **argv, char **envp)
{
	data.infile = open(argv[1], O_RDONLY, 0777);
	if (data.infile == -1)
	{
		perror(argv[1]);
		exit(1);
	}
	dup2(data.tube[1], STDOUT_FILENO);
	dup2(data.infile, STDIN_FILENO);
	close(data.tube[0]);
	close(data.infile);
	execute(argv[2], envp);
}

void	parent_process(t_pipex data, char **argv, char **envp)
{
	data.outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data.outfile == -1)
	{
		perror(argv[4]);
		exit(1);
	}
	dup2(data.tube[0], STDIN_FILENO);
	dup2(data.outfile, STDOUT_FILENO);
	close(data.tube[1]);
	close(data.outfile);
	execute(argv[3], envp);
}

void	run_pipeline(t_pipex *data, char **argv, char **envp)
{
	int	status;

	if (pipe(data->tube) == -1)
		error_exit("pipe failed");
	data->pid1 = fork();
	if (data->pid1 == -1)
		error_exit("fork failed");
	if (data->pid1 == 0)
		child_process(*data, argv, envp);
	data->pid2 = fork();
	if (data->pid2 == -1)
		error_exit("fork failed");
	if (data->pid2 == 0)
		parent_process(*data, argv, envp);
	close(data->tube[0]);
	close(data->tube[1]);
	waitpid(data->pid1, NULL, 0);
	waitpid(data->pid2, &status, 0);
	exit((status >> 8) & 255);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	if (argc == 5)
		run_pipeline(&data, argv, envp);
	else
	{
		write(STDERR_FILENO, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 37);
		exit(1);
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
