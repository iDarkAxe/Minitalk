/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:09:46 by ppontet           #+#    #+#             */
/*   Updated: 2025/01/24 22:08:16 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_client.h"
#include "ft_printf.h"
#include <signal.h>
// A SUPPRIMER
#include <stdlib.h>

int				find_pid(void);
int				ft_atoi(const char *nptr);

// Variable globale pour la bonne reception de l'ACK
static char		g_ack_received = 1;
static __pid_t	g_server_pid;

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (sig == SIGUSR1 && info->si_pid == g_server_pid)
		g_ack_received = 1;
	else
		exit(1);
}

void	send_bit(__pid_t server_pid, char bit)
{
	int	elapsed;

	elapsed = 0;
	if (bit)
		kill(server_pid, SIGUSR1);
	else
		kill(server_pid, SIGUSR2);
	while (!g_ack_received)
	{
		usleep(1000);
		elapsed += 1000;
		if (elapsed >= ACK_TIMEOUT)
		{
			ft_printf("Error: No acknowledgment received in time\n");
			exit(-1);
		}
	}
}

void	send_string(__pid_t server_pid, char *string)
{
	size_t	index;
	char	bit;

	index = 0;
	while (string[index] != '\0')
	{
		bit = 0;
		while (bit < 8)
		{
			g_ack_received = 0;
			send_bit(server_pid, (string[index] & (128 >> bit)) != 0);
			bit++;
		}
		index++;
	}
	bit = 0;
	while (bit < 8)
	{
		g_ack_received = 0;
		send_bit(server_pid, 0);
		bit++;
	}
}

int	main(int argc, char **argv)
{
	char				*string;
	struct sigaction	action_receive;

	if (argc < 2 || argc > 3)
	{
		ft_printf("Error\nNo argument\n");
		ft_printf("Usage: %s <PID> <SIGNAL>\n", argv[0]);
		exit(-1);
	}
	if (argc == 2)
	{
		g_server_pid = find_pid();
		string = argv[1];
	}
	else
	{
		g_server_pid = ft_atoi(argv[1]);
		string = argv[2];
	}
	if (g_server_pid == 0)
	{
		ft_printf("Error\nInvalid PID\n");
		exit(-1);
	}
	action_receive.sa_sigaction = signal_handler;
	sigemptyset(&action_receive.sa_mask);
	action_receive.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGUSR1, &action_receive, NULL);
	send_string(g_server_pid, string);
	return (0);
}
// ft_printf("Message sent successfully\n");
