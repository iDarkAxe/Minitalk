/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:09:46 by ppontet           #+#    #+#             */
/*   Updated: 2025/01/26 17:54:19 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_client.h"
#include "ft_printf.h"
#include <signal.h>
#include <stdlib.h>

static void		send_bit(__pid_t server_pid, char bit);
static void		send_string(__pid_t server_pid, char *string);
static void		signal_handler(int sig, siginfo_t *info, void *context);
static int		ft_atoi(const char *nptr);

// Variable globale pour la bonne reception de l'ACK
static volatile char	g_ack_received = 1;
static __pid_t			g_server_pid;

/**
 * @brief Main function of the client.
 *
 * @param argc Number of arguments.
 * @param argv Array of arguments.
 * @return int 0 if the program ends correctly, -1 otherwise.
 */
int	main(int argc, char **argv)
{
	struct sigaction	action_receive;

	if (argc < 3 || argc > 3)
	{
		ft_printf("Error\nNo argument\n");
		ft_printf("Usage: %s <PID> <SIGNAL>\n", argv[0]);
		exit(-1);
	}
	g_server_pid = ft_atoi(argv[1]);
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
	send_string(g_server_pid, argv[2]);
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
	(void)info;
	(void)context;
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

/**
 * @brief Convert string to int, and handle number
 *
 * @param nptr String to convert
 * @return int Converted number
 */
static int	ft_atoi(const char *nptr)
{
	long		number;
	long		overflow_tester;
	short int	minus_sign;

	number = 0;
	minus_sign = 0;
	while (*nptr != '\0' && (*nptr == ' ' || *nptr == '\t' || *nptr == '\n'
			|| *nptr == '\r' || *nptr == '\v' || *nptr == '\f'))
		nptr++;
	if (*nptr != '\0' && ((*nptr == '-') || (*nptr == '+')))
	{
		if (*nptr == '-')
			minus_sign = -1;
		nptr++;
	}
	while (*nptr != '\0' && *nptr >= '0' && *nptr <= '9')
	{
		overflow_tester = number;
		number = number * 10 + *nptr++ - '0';
		if (overflow_tester > number)
			return (-(!minus_sign));
	}
	if (minus_sign == -1)
		return ((int)-number);
	return ((int)number);
}
