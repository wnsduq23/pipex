/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junykim <junykim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:08:01 by junykim           #+#    #+#             */
/*   Updated: 2022/05/24 22:54:26 by junykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h> // is it right cuz perror?
# include "libft/libft.h"

typedef struct s_pipex
{
	int		fd[2];
	char	*command;
	char	infile;
	char	outfile;
	char	**cmd_args;//right?
	char	**cmds;
	char	*cmd_path;
	int		pid1;
	int		pid2;
}			t_pipex;

void	ft_error(char *s);
void	open_files(t_pipex *pipex, int ac, char **av);
char	*find_path(char **envp);
char	*get_cmd(char *cmd, char **paths);
void	first_child(t_pipex pipex, char **av, char **envp);
void	second_child(t_pipex pipex, char **av, char **envp);
// have to make ft
void	close_pipe(t_pipex *pipex);
void	parent_free(t_pipex *pipex);
void	child_free(t_pipex *pipex);
#endif
