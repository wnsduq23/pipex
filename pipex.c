/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junykim <junykim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 22:17:12 by junykim           #+#    #+#             */
/*   Updated: 2022/05/20 18:17:31 by junykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "error_message.h"

int main(int ac, char **av)
{
	int		fd[2];
	pid_t	pid;
	
	if (ac < 2)
		ft_error();
	if (pipe(fd) == -1)
		ft_error();
	pid = fork();
	if (pid > 0) // pid is parent processor
	{

	}
	else if (pid == 0) // pid is child processor
	{
		exit(0);
	}
	else
	{
		perror("fork Fail!	\n");
		return (-1);
	}
	return (0);
}
