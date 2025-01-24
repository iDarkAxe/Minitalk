/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:52:23 by ppontet           #+#    #+#             */
/*   Updated: 2025/01/24 19:18:52 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
// ???

void	sig_receive(int code);

static char	character = 0;
static char	bit = 0;

void signal_handler(int sig, siginfo_t *info, void *context)
{
    (void)context; // On ignore le contexte pour cet exemple

    if (sig == SIGUSR1)
        printf("SIGUSR1 received from PID: %d\n", info->si_pid);
    else if (sig == SIGUSR2)
        printf("SIGUSR2 received from PID: %d\n", info->si_pid);
}

void	sig_receive(int code)
{
	character = (char)(character << 1);
	character = character | (code == SIGUSR1);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", character);
		character = 0;
		bit = 0;
	}
}

int	main(void)
{
	struct sigaction	action_receive;

	action_receive.sa_handler = sig_receive;
	action_receive.sa_sigaction = signal_handler;
	sigemptyset(&action_receive.sa_mask);
	action_receive.sa_flags = 0;
	ft_printf("PID: %d\n", getpid());
	sigaction(SIGUSR1, &action_receive, NULL);
	sigaction(SIGUSR2, &action_receive, NULL);
	while (1)
		pause();
}
