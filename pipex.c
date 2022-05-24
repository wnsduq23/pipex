/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junykim <junykim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 22:35:10 by junykim           #+#    #+#             */
/*   Updated: 2022/05/24 22:48:01 by junykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *get_cmd(char *cmd, char **paths)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	first_child(t_pipex pipex, char **av, char **envp)
{
	dup2(pipex.fd[1], 1);
	close(pipex.fd[0]);
	dup2(pipex.infile, 0);
	pipex.cmd_args = ft_split(av[2], ' ');
	pipex.command = get_cmd(pipex.cmd_args[0], pipex.cmds);
	if (!pipex.command)
	{
		child_free(&pipex);
		ft_error("first command not found");
		exit(1);
	}
	execve(pipex.command, pipex.cmd_args, envp);
}

void	second_child(t_pipex pipex, char **av, char **envp)
{
	dup2(pipex.fd[0], 0);
	close(pipex.fd[1]);
	dup2(pipex.outfile, 1);
	pipex.cmd_args = ft_split(av[3], ' ');
	pipex.command = get_cmd(pipex.cmd_args[0], pipex.cmds);
	if (!pipex.command)
	{
		child_free(&pipex);
		ft_error("second command not found");
		exit(1);
	}
	execve(pipex.command, pipex.cmd_args, envp);
}
