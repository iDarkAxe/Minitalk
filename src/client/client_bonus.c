/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:09:46 by ppontet           #+#    #+#             */
/*   Updated: 2025/01/25 13:05:04 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_client_bonus.h"
#include "ft_printf.h"
#include <signal.h>
#include <stdlib.h>

static void		send_bit(__pid_t server_pid, char bit);
static void		send_string(__pid_t server_pid, char *string);
static void		signal_handler(int sig, siginfo_t *info, void *context);

// Variable globale pour la bonne reception de l'ACK
static char		g_ack_received = 1;
static __pid_t	g_server_pid;

/**
 * @brief Main function of the client.
 * Modified to use the find_server_pid function.
 *
 * @param argc Number of arguments.
 * @param argv Array of arguments.
 * @return int 0 if the program ends correctly, -1 otherwise.
 */
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
	string = NULL;
	g_server_pid = find_server_pid(argc, argv, &string, &g_server_pid);
	if (g_server_pid == 0)
	{
		ft_printf("Error\nInvalid PID\n");
		exit(-1);
	}
	action_receive.sa_sigaction = signal_handler;
	sigemptyset(&action_receive.sa_mask);
	action_receive.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGUSR1, &action_receive, NULL);
	sigaction(SIGUSR2, &action_receive, NULL);
	send_string(g_server_pid, string);
	return (0);
}

/**
 * @brief Signal handler for SIGUSR1 and SIGUSR2.
 * SIGUSR1 will set the ACK flag to 1.
 * It's used to acknowledge the reception of a bit by server.
 * SIGUSR2 will wait for 100 us (microseconds).
 * It's for letting server time to process the full character sent.
 *
 * @param sig Signal received.
 * @param info Information about the signal.
 * @param context Context of the signal.
 */
static void	signal_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (sig == SIGUSR1 && info->si_pid == g_server_pid)
		g_ack_received = 1;
	else if (sig == SIGUSR2 && info->si_pid == g_server_pid)
		usleep(100);
	else
		exit(1);
}

/**
 * @brief Send bits to the server.
 * If the bit is 1, it will send a SIGUSR1 signal.
 * Otherwise, it will send a SIGUSR2 signal.
 * It will wait for an acknowledgment from the server.
 * If no acknowledgment is received in time, the program will exit.
 *
 * @param server_pid Server PID.
 * @param bit Bit to send.
 */
static void	send_bit(__pid_t server_pid, char bit)
{
	int	elapsed;

	elapsed = 0;
	if (bit)
		kill(server_pid, SIGUSR1);
	else
		kill(server_pid, SIGUSR2);
	usleep(5);
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

/**
 * @brief Send a string to the server.
 * Each character will be sent as 8 bits.
 * It will send a '\0' bit after the last character
 * to indicate the end of the string.
 *
 * @param server_pid Server PID.
 * @param string String to send.
 */
static void	send_string(__pid_t server_pid, char *string)
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
