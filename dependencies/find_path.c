/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:20:36 by ahamdy            #+#    #+#             */
/*   Updated: 2022/03/15 12:32:51 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*fd_fail_msg(char *file)
{
	char	*msg;

	if (!access(file, F_OK))
		msg = ft_strjoin("pipex : permission denied :",
				file);
	else
	{
		msg = ft_strjoin("pipex : no such file or directory :",
				file);
	}
	return (msg);
}

void	exit_cmd_msg(char *cmd, char **path)
{
	free_mem(path);
	error_exit(ft_strjoin("pipex : command not found : ",
			cmd), 127);
}

char	*cmd_path(char *tmp, char **path)
{
	free_mem(path);
	return (tmp);
}

char	**setup_path(char **envp)
{
	int	i;

	i = 0;
	i = find_path_line(envp);
	return (ft_split(&envp[i][5], ':'));
}

char	*find_path(char **envp, char *cmd)
{
	char	**path;
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	path = setup_path(envp);
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!(access(tmp2, X_OK)))
			return (cmd_path(tmp2, path));
		else
			free(tmp2);
		i++;
	}
	exit_cmd_msg(cmd, path);
	exit(1);
}
