/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junykim <junykim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 20:08:38 by junykim           #+#    #+#             */
/*   Updated: 2022/11/01 23:01:32 by junykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "error_msg_bonus.h"

static char	*get_cmd(char **paths, char *cmd)
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

static void	sub_dup2(int zero, int first)
{
	dup2(zero, 0);
	close(zero);
	dup2(first, 1);
	close(first);
}

void	child(t_pipexb *p, char **av, char **envp)
{
	p->pid = fork();
	if (!p->pid)
	{
		if (p->idx == 0)
			sub_dup2(p->infile, p->pipe[1]);
		else if (p->idx == p->cmd_nums - 1)
			sub_dup2(p->pipe[2 * p->idx - 2], p->outfile);
		else
			sub_dup2(p->pipe[2 * p->idx - 2], p->pipe[2 * p->idx + 1]);
		close_pipes(p);
		p->cmd_args = ft_split(av[2 + p->here_doc + p->idx], ' ');
		p->cmd = get_cmd(p->cmd_paths, p->cmd_args[0]);
		if (!p->cmd)
		{
			child_free(p);
			msg_error(ERR_CMD);
		}
		execve(p->cmd, p->cmd_args, envp);
		child_free(p);
		exit(0);
	}
}
