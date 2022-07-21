/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junykim <junykim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:37:04 by junykim           #+#    #+#             */
/*   Updated: 2022/07/21 17:37:06 by junykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

void	msg_error(char *s)
{
	perror(s);
	exit(1);
}
