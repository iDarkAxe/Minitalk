/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:52:23 by ppontet           #+#    #+#             */
/*   Updated: 2025/01/24 22:00:54 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#include "ft_client.h"

static char	g_character = 0;
static char	g_bit = 0;

	// ft_printf("SIGUSR2 received from PID: %d\n", info->si_pid);
void	signal_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	g_character = (char)(g_character << 1);
	g_character = g_character | (sig == SIGUSR1);
	g_bit++;
	if (g_bit == 8)
	{
		ft_printf("%c", g_character);
		g_character = 0;
		g_bit = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	action_receive;

	action_receive.sa_sigaction = signal_handler;
	sigemptyset(&action_receive.sa_mask);
	action_receive.sa_flags = SA_RESTART | SA_SIGINFO;
	ft_printf("PID: %d\n", getpid());
	sigaction(SIGUSR1, &action_receive, NULL);
	sigaction(SIGUSR2, &action_receive, NULL);
	while (1)
		pause();
}
