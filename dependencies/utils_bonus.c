/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 11:18:04 by ahamdy            #+#    #+#             */
/*   Updated: 2022/03/11 11:08:53 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	open_fd_bonus(char *c, int here_doc)
{
	int	fd;

	fd = open(c, O_RDONLY);
	if (fd == -1 && !here_doc)
	{
		ft_putstr(ft_strjoin("pipex : no such file or directory ", c));
		dup2(fd, 0);
		close(fd);
	}
	else if (fd == -1 && here_doc)
	{
		fd = open(c, O_CREAT | O_RDWR, O_TRUNC, 0644);
		if (fd == -1)
			error_exit(ft_strjoin("pipex: no such file or directory: ", c),
				127);
	}
	return (fd);
}
