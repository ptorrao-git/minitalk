/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:43:19 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/07/29 12:40:23 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	banner(void)
{
	ft_printf("\n");
	ft_printf(R "██████╗ ████████╗ █████╗ ██████╗ ██████╗  █████╗  █████╗ \n");
	ft_printf(R "██╔══██╗╚══██╔══╝██╔══██╗██╔══██╗██╔══██╗██╔══██╗██╔══██╗\n");
	ft_printf(R "██████╔╝   ██║   ██║  ██║██████╔╝██████╔╝███████║██║  ██║\n");
	ft_printf(R "██╔═══╝    ██║   ██║  ██║██╔══██╗██╔══██╗██╔══██║██║  ██║\n");
	ft_printf(R "██║        ██║   ╚█████╔╝██║  ██║██║  ██║██║  ██║╚█████╔╝\n");
	ft_printf(R "╚═╝        ╚═╝    ╚════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚════╝ \n");
	ft_printf("                                                           \n");
	ft_printf(G "    ███████╗███████╗██████╗ ██╗   ██╗███████╗██████╗     \n");
	ft_printf(G "    ██╔════╝██╔════╝██╔══██╗██║   ██║██╔════╝██╔══██╗    \n");
	ft_printf(G "    ███████╗█████╗  ██████╔╝██║   ██║█████╗  ██████╔╝    \n");
	ft_printf(G "    ╚════██║██╔══╝  ██╔══██╗╚██╗ ██╔╝██╔══╝  ██╔══██╗    \n");
	ft_printf(G "    ███████║███████╗██║  ██║ ╚████╔╝ ███████╗██║  ██║    \n");
	ft_printf(G "    ╚══════╝╚══════╝╚═╝  ╚═╝  ╚═══╝  ╚══════╝╚═╝  ╚═╝    \n");
	ft_printf(E "                                                         \n");
}

char	*ft_cjoin(char *str, char c)
{
	char	*new_str;
	int		i;
	int		size;

	if (!str)
	{
		str = malloc(sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '\0';
	}
	size = ft_strlen(str);
	new_str = (char *)malloc(sizeof(char) * (size + 2));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i++] = c;
	new_str[i] = '\0';
	free(str);
	return (new_str);
}

void	handle_signal(int signal)
{
	static char	*str = NULL;
	static int	c = 0;
	static int	bit = 0;

	if (signal == SIGUSR1)
		c = c | (1 << bit);
	bit += 1;
	if (bit == 8)
	{
		if (c == '\0')
		{
			ft_printf("%s\n", str);
			free(str);
			str = NULL;
		}
		else
			str = ft_cjoin(str, c);
		bit = 0;
		c = 0;
	}
}

int	main(void)
{
	int	pid;

	pid = getpid();
	banner();
	ft_printf("PID: %d\n", pid);
	while (1)
	{
		signal(SIGUSR1, handle_signal);
		signal(SIGUSR2, handle_signal);
	}
}
