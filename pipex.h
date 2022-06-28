/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junykim <junykim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:08:01 by junykim           #+#    #+#             */
/*   Updated: 2022/06/28 16:12:06 by junykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
/* to write, read, close, access, pipe, dup, dup2, execve, fork */
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>

/* malloc, free, exit */
# include <stdlib.h>

/* open */
# include <fcntl.h>

/* waitpid, wait */
# include <sys/wait.h>

/* strerror */
# include <string.h>

/* perror */
# include <stdio.h>

/* ft_strjoin , ft_strncmp */
# include "libft/libft.h"

typedef struct s_pipex
{
	int		fd[2];
	char	*command;
	char	infile;
	char	outfile;
	char	**cmd_args;
	char	**cmds;
	char	*cmd_path;
	int		pid1;
	int		pid2;
}			t_pipex;

/* util.c */
void	msg_error(char *s);

/* main.c */
void	open_files(t_pipex *pipex, int ac, char **av);

/* pipex.c */
char	*find_path(char **envp);
char	*get_cmd(char *cmd, char **paths);

/* child.c */
void	first_child(t_pipex pipex, char **av, char **envp);
void	second_child(t_pipex pipex, char **av, char **envp);

/* free.c */
void	close_pipe(t_pipex *pipex);
void	parent_free(t_pipex *pipex);
void	child_free(t_pipex *pipex);

#endif
