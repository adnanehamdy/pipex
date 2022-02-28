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

int	open_file(char *c)
{
	int	fd;

	fd = open(c, O_CREAT | O_RDWR, 0777);
	if (fd == -1)
		error_exit();
	return (fd);
}

int	fork_it(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_exit();
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

char	*find_path(char **envp, char *cmd)
{
	char	**path;
	char	*tmp;
	char	*tmp2;
	int		i;

	i = find_path_line(envp);
	path = ft_split(&envp[i][5], ':');
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!(access(tmp2, X_OK)))
		{
			free_mem(path);
			return (tmp2);
		}
		else
			free(tmp2);
		i++;
	}
	free_mem(path);
	error_exit();
	exit(1);
}

char	**split_cmd(char *cmd)
{
	char	**command;

	command = ft_split(cmd, ' ');
	if (!command)
		error_exit();
	return (command);
}
