/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:38:28 by ahamdy            #+#    #+#             */
/*   Updated: 2022/02/24 17:38:28 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	duplicate_fd(int *fd, int file)
{
	close(fd[0]);
	dup2(file, 0);
	close(file);
	dup2(fd[1], 1);
	close(fd[1]);
}

void	error_exit(void)
{
	perror("error");
	exit(1);
}

int	open_fd(char *c)
{
	int	fd;

	fd = open(c, O_RDONLY);
	if (fd == -1)
		error_exit();
	return (fd);
}

void	duplicate_bonus(int *fd)
{
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
}

void	duplicate_file(int *fd, int file)
{
	close(fd[1]);
	dup2(file, 1);
	dup2(fd[0], 0);
	close(file);
	close(fd[0]);
}
