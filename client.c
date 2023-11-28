/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlakchai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 08:44:34 by tlakchai          #+#    #+#             */
/*   Updated: 2023/11/28 11:19:11 by tlakchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minitalk_client.h"

void	exit_error(char *message)
{
	ft_printf("%s\n", message);
	exit(1);
}

void	send_bit(int pid, char byte)
{
	int				i;
	int				status;
	unsigned char	tmp_byte;

	i = 8;
	tmp_byte = byte;
	status = 0;
	while (i-- > 0)
	{
		tmp_byte = byte >> i;
		if (tmp_byte % 2 == 0)
			status = kill(pid, SIGUSR2);
		else
			status = kill(pid, SIGUSR1);
		usleep(100);
	}
	if (status < 0)
		exit_error("Error: Invalid PID");
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
	send_message(pid, argv[2]);
	return (0);
}
