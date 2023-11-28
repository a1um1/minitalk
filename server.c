/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlakchai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 04:59:23 by tlakchai          #+#    #+#             */
/*   Updated: 2023/11/28 11:17:01 by tlakchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minitalk_server.h"

void	exit_error(char *message)
{
	ft_printf("%s\n", message);
	exit(1);
}

void	signal_handler(int signum)
{
	static unsigned char	current_char = 0;
	static int				bit_index = 0;
	int						status;

	status = 0;
	current_char |= (signum == SIGUSR1);
	if (++bit_index == 8)
	{
		if (current_char == '\0')
			status = ft_printf("\n");
		else
			status = ft_printf("%c", current_char);
		bit_index = 0;
		current_char = 0;
	}
	else
		current_char <<= 1;
	if (status < 0)
		exit_error("Error: ft_printf failed");
}

int	main(void)
{
	ft_printf(" MiniTalk Server - PID %d \n", getpid());
	signal(SIGUSR2, signal_handler);
	signal(SIGUSR1, signal_handler);
	while (1)
		pause();
	return (0);
}
