/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:11:32 by gtskitis          #+#    #+#             */
/*   Updated: 2024/03/07 20:10:16 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_top(long int n, int sign, const char *nptr)
{
	int	len_nptr;
	int	len_long;

	if (nptr[0] == '-')
	{
		len_long = ft_strlen(LONG_INT_MIN);
		len_nptr = ft_strlen(nptr);
		if (len_nptr < len_long)
			return ((unsigned char)(n * sign) % 256);
		if (len_nptr > len_long
			|| (ft_strncmp(nptr, LONG_INT_MIN, len_nptr) > 0))
			return (-1);
		return ((n * sign) % 256);
	}
	len_long = ft_strlen(LONG_INT_MAX);
	if (nptr[0] == '+')
		nptr += 1;
	len_nptr = ft_strlen(nptr);
	if (len_nptr < len_long)
		return ((n * sign) % 256);
	else if (len_nptr > len_long
		|| (ft_strncmp(nptr, LONG_INT_MAX, len_nptr) > 0))
		return (-1);
	return ((n * sign) % 256);
}

int	ft_atoi_exit(const char *nptr)
{
	long int	num;
	int			i;
	int			sign;

	sign = 1;
	num = 0;
	i = 0;
	if (nptr[i] == '-' || nptr[i] == '+' || (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		if (nptr[i] == '-')
		{
			sign *= -1;
			i++;
		}
		else if (nptr[i] == '+')
			i++;
	}
	while (nptr[i])
	{
		if (!(nptr[i] >= '0' && nptr[i] <= '9'))
			return (-1);
		num = (num * 10) + (nptr[i] - '0');
		i++;
	}
	return (check_top(num, sign, nptr));
}

void	choose_exit(t_data *data, int exit_stat, int i)
{
	(void)data;
	if (exit_stat == -1)
	{
		ft_putstr_fd("exit\n numeric argument required\n", 2);
		data->new_exit_status = 2;
		data->is_exit = true;
		return ;
	}
	else if (i != 2)
	{
		ft_putstr_fd("exit\n too many arguments\n", 2);
		data->new_exit_status = 1;
	}
	else
	{
		ft_putstr_fd("exit\n", 1);
		data->new_exit_status = exit_stat;
		data->is_exit = true;
	}
}

void	ft_exit(t_data *data, t_cmd *cmd)
{
	char	*temp;
	int		i;
	int		exit_stat;

	i = 0;
	while (cmd -> argv[i])
		i++;
	if (i >= 2)
	{
		temp = cmd->argv[1];
		cmd -> argv[1] = ft_strtrim(cmd -> argv[1], " \f\t\v\n\r");
		if (!cmd->argv[1])
			return ;
		free(temp);
		exit_stat = ft_atoi_exit((const char *)cmd->argv[1]);
		choose_exit(data, exit_stat, i);
	}
	if (i == 1)
	{
		ft_putstr_fd("exit\n", 1);
		data->new_exit_status = data->exit_status;
		data->is_exit = true;
	}
}
