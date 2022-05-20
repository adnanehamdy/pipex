/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:48:20 by ahamdy            #+#    #+#             */
/*   Updated: 2022/02/24 17:48:20 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	find_char(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	fork_it(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_exit("error can't fork", 1);
	return (pid);
}

void	free_mem(char **path)
{
	int	i;

	i = 0;
	while (path[i])
		free(path[i++]);
	free(path);
}

char	**split_cmd(char *cmd)
{
	char	**command;

	command = ft_split(cmd, ' ');
	if (!command)
		error_exit("not enought memory", 1);
	return (command);
}
