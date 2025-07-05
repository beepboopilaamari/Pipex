/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaamari <ilaamari@42nice.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 23:51:55 by ilaamari          #+#    #+#             */
/*   Updated: 2025/07/05 23:51:55 by ilaamari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		tube[2];
	int		infile;
	int		outfile;
}	t_pipex;

void	error_exit(char *msg);
void	execute(char *argv, char **envp);
char	*find_path(char *cmd, char **envp);
char	**split(char const *s, char c);
void	free_array(char **arr);
void	validate_cmd(char *argv);
void	child_process(t_pipex data, char **argv, char **envp);
void	parent_process(t_pipex data, char **argv, char **envp);
void	run_pipeline(t_pipex *data, char **argv, char **envp);

#endif
