/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junykim <junykim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 22:17:12 by junykim           #+#    #+#             */
/*   Updated: 2022/06/28 16:04:11 by junykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "error_msg.h"
#include <fcntl.h>

/** extern char	**environ; // save env */

// pid > 0 -> parent procssor , pid = 0 -> child processor
char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	open_files(t_pipex *pipex, int ac, char **av)
{
	pipex->infile = open(av[1], O_RDONLY);
	if (pipex->infile == -1)
		msg_error(ERR_ALLOC);
	pipex->outfile = open(av[ac - 1], O_RDWR | O_TRUNC | O_CREAT, 00644);
	if (pipex->outfile == -1)
		msg_error(ERR_ALLOC);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac < 5)
		msg_error(ERR_ARG_NUM);
	open_files(&pipex, ac, av);
	if (pipe(pipex.fd) == -1)
		msg_error(ERR_ALLOC);
	pipex.cmd_path = find_path(envp);
	pipex.cmds = ft_split(pipex.cmd_path, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		msg_error(ERR_FORK);
	else if (pipex.pid1 == 0)
		first_child(pipex, av, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		msg_error(ERR_FORK);
	else if (pipex.pid2 == 0)
		second_child(pipex, av, envp);
	close_pipe(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	parent_free(&pipex);
	return (0);
}
