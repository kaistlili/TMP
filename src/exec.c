/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 16:02:36 by ptruffau          #+#    #+#             */
/*   Updated: 2018/12/03 13:38:41 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_cmd(t_command *cmd)
{
	static t_builtin array[7] = {ft_echo, change_dir, setenv_wrapper
			, ft_unsetenv, ft_env, ft_exit,NULL};
	static	char	*builtins[] = {"echo","cd", "setenv"
			, "unsetenv","env", "exit", NULL};
	int i;

	if (cmd->args[0] == NULL)
		return (0);
	cmd->process_env = lst_to_tab(*g_environ, 0);
	if ((cmd->process_env == NULL) 
		|| (expand_tokens(cmd->args) == MEMERR))
		return (MEMERR);
	if (cmd->args[0] == NULL)
		return (0);
	if  ((i = ft_cmptab(builtins, cmd->args[0])) != -1)
		return(array[i](cmd));
	else
		return (spawn_bin(cmd)); 
	return (0);
}

int		exec_loop(t_command *command_lst)
{
	t_command	*tmp;

	tmp = command_lst;
	if ((tmp != NULL) && (tmp->args != NULL))
	{
		while (tmp != NULL) 
		{
			if ((execute_cmd(tmp)) == MEMERR)
			{
				free_cmdlst(command_lst);
				return (MEMERR);
			}
			tmp = tmp->next;
		}
	}
	return (0);
}