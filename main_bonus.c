/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junykim <junykim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 19:51:59 by junykim           #+#    #+#             */
/*   Updated: 2022/07/21 13:37:38 by junykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "error_msg_bonus.h"

static void	creat_pipes(t_pipexb *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_nums - 1)
	{
		if (pipe(pipex->pipe + 2 * i) < 0)
			parent_free(pipex);
		i++;
	}
}

void	close_pipes(t_pipexb *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->pipe_nums)
		close(pipex->pipe[i]);
}

int	main(int ac, char **av, char **envp)
{
	t_pipexb	pipex;

	if (ac < is_here_doc(av[1], &pipex))
		msg_error(ERR_INPUT);
	get_infile(av, &pipex);
	get_outfile(av[ac - 1], &pipex);
	pipex.env_path = find_path(envp);
	pipex.cmd_paths = ft_split(pipex.env_path, ':');
	if (!pipex.cmd_paths)
		pipe_free(&pipex);
	pipex.cmd_nums = ac - 3 - pipex.here_doc;
	pipex.pipe_nums = 2 * (pipex.cmd_nums - 1);
	pipex.pipe = (int *)malloc(sizeof(int) * pipex.pipe_nums);
	if (!pipex.pipe)
		msg_error(ERR_ALLOC);
	creat_pipes(&pipex);
	pipex.idx = -1;
	while (++(pipex.idx) < pipex.cmd_nums)
		child(pipex, av, envp);
	close_pipes(&pipex);
	waitpid(-1, NULL, 0);
	parent_free(&pipex);
	return (0);
}
