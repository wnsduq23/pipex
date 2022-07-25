/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junykim <junykim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:38:59 by junykim           #+#    #+#             */
/*   Updated: 2022/07/21 17:55:12 by junykim          ###   ########.fr       */
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

/* open, unlink */
# include <fcntl.h>

/* waitpid, wait */
# include <sys/wait.h>

/* strerror */
# include <string.h>

/*to perror*/
# include <stdio.h>

/* to get_next_line */
# include "libft/libft.h"

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_pipexb
{
	int			infile;
	int			outfile;
	char		*env_path;
	char		**cmd_paths;
	char		*cmd;
	char		**cmd_args;
	t_bool		here_doc;
	pid_t		pid;
	int			cmd_nums;
	int			pipe_nums;
	int			*pipe;
	int			idx;
}	t_pipexb;

/* main.c */
void	close_pipes(t_pipexb *pipex);

/* pipex.c */
void	child(t_pipexb pipex, char **av, char **envp);

/* free.c */
void	parent_free(t_pipexb *pipex);
void	child_free(t_pipexb *pipex);
void	pipe_free(t_pipexb *pipex);

/* files.c */
char	*find_path(char **envp);
void	get_infile(char **av, t_pipexb *pipex);
void	get_outfile(char *av, t_pipexb *pipex);

/* here_doc.c */
int		is_here_doc(char *arg, t_pipexb *pipex);
void	here_doc(char *av, t_pipexb *pipex);

/* error.c */
void	msg_error(char *err);
void	msg_pipe(char *arg);
int		msg(char *err);

#endif
