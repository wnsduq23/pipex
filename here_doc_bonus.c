/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junykim <junykim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 19:44:37 by junykim           #+#    #+#             */
/*   Updated: 2022/06/28 15:57:26 by junykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "error_msg_bonus.h"

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
		write(1, "Pipe heredoc>", 14);
		buf = get_next_line(0);
		if (buf <= 0)
			exit(1);
		if (!ft_strncmp(av, buf, ft_strlen(av) + 1))
			break ;
		write(file, buf, ft_strlen(buf));
		write(file, "\n", 1);// 어차피 gnl이 개행문자를 포함한 한줄이라 필요없나? 
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
