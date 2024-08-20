/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:42:39 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/08/16 15:51:39 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	dynamic_sleep(int len)
{
	size_t	i;

	i = 0;
	if (len <= 10000)
		i = 10;
	else if (len <= 30000)
		i = 100;
	else if (len <= 60000)
		i = 300;
	else if (len <= 100000)
		i = 500;
	else if (len <= 1000000)
		i = 10000;
	return (i);
}

void	byte_to_bit(unsigned char c, int pid, int len)
{
	int	bit;
	int	time;

	bit = 0;
	while (bit < 8)
	{
		if (c & 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				return ;
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				return ;
		}
		c >>= 1;
		bit++;
		time = dynamic_sleep(len);
		usleep(time);
	}
}

void	send_text(char *str, int pid)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (str[i])
		byte_to_bit(str[i++], pid, len);
	byte_to_bit('\0', pid, len);
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*str;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		str = argv[2];
		send_text(str, pid);
	}
	else
		ft_printf("Usage: ./client <server_pid> <text to send>");
	return (0);
}
