/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlakchai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 08:44:34 by tlakchai          #+#    #+#             */
/*   Updated: 2023/11/28 09:47:37 by tlakchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minitalk_client.h"

void	send_bit(int pid, char byte)
{
	int				i;
	unsigned char	tmp_byte;

	i = 8;
	tmp_byte = byte;
	while (i-- > 0)
	{
		tmp_byte = byte >> i;
		if (tmp_byte % 2 == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(100);
	}
}

void	send_message(int pid, char *message)
{
	size_t	i;

	i = 0;
	while (message[i])
		send_bit(pid, message[i++]);
	send_bit(pid, '\0');
}

int	main(int argc, char *argv[])
{
	int	pid;

	if (argc != 3)
	{
		ft_printf("Usage: ./client [PID] [message]\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_printf("Invalid PID\n");
		return (1);
	}
	send_message(pid, argv[2]);
	return (0);
}
