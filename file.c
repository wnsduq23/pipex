/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junykim <junykim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:40:15 by junykim           #+#    #+#             */
/*   Updated: 2022/07/21 17:54:40 by junykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "error_msg.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	get_infile(char **av, t_pipexb *pipex)
{
	if (pipex->here_doc)
		here_doc(av[2], pipex);
	else
	{
		pipex->infile = open(av[1], O_RDONLY);
		if (pipex->infile < 0)
			msg_error(ERR_INFILE);
	}
}

void	get_outfile(char *av, t_pipexb *pipex)
{
	if (pipex->here_doc)
		pipex->outfile = open(av, O_WRONLY | O_CREAT | O_APPEND, 00644);
	else
		pipex->outfile = open(av, O_CREAT | O_RDWR | O_TRUNC, 00644);
	if (pipex->outfile < 0)
		msg_error(ERR_OUTFILE);
}
