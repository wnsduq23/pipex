/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junykim <junykim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:40:47 by junykim           #+#    #+#             */
/*   Updated: 2022/07/21 17:54:46 by junykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "error_msg.h"

int	is_here_doc(char *arg, t_pipexb *pipex)
{
	if (arg && !ft_strncmp("here_doc", arg, 9))
	{
		pipex->here_doc = TRUE;
		return (6);
	}
	else
	{
		pipex->here_doc = FALSE;
		return (5);
	}
}

void	here_doc(char *av, t_pipexb *p)
{
	int		file;
	char	*buf;

	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (file < 0)
		msg_error(ERR_INFILE);
	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		buf = get_next_line(0);
		if (buf <= 0)
			exit(1);
		if (!ft_strncmp(av, buf, ft_strlen(av)))
			break ;
		write(file, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	close(file);
	p->infile = open(".heredoc_tmp", O_RDONLY);
	if (p->infile < 0)
	{
		unlink(".heredoc_tmp");
		msg_error(ERR_HEREDOC);
	}
}
