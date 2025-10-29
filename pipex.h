/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaamari <ilaamari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 23:51:55 by ilaamari          #+#    #+#             */
/*   Updated: 2025/10/29 17:40:02 by ilaamari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
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
char	**ft_split(char const *s, char c);
void	free_array(char **arr);
void	validate_cmd(char *argv);
void	child_process(t_pipex data, char **argv, char **envp);
void	parent_process(t_pipex data, char **argv, char **envp);
void	run_pipeline(t_pipex *data, char **argv, char **envp);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
