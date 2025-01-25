/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:52:23 by ppontet           #+#    #+#             */
/*   Updated: 2025/01/25 13:07:41 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"
#include "ft_printf.h"
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * @brief Strjoin for single character to concatenate.
 *
 * @param s Existing string.
 * @param c Character to add.
 * @return char* New string with character added.
 */
static char	*ft_strjoin_char(char *s, char c)
{
	char	*new_str;
	size_t	len;
	size_t	i;

	len = 0;
	if (s)
		while (s[len])
			len++;
	new_str = malloc(len + 2);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(s);
	return (new_str);
}

/**
 * @brief When a signal is received, the signal handler will be called.
 * SIGUSR1 and SIGUSR2 will be received as a 1 bit.
 * A character will be built from the bits received.
 * An ACK signal will be sent back to the client for each bit received.
 * A WAIT signal will be sent back to the client for each character received.
 * When a full string is built, it will be printed.
 * 
 * @param sig Signal received (SIGUSR1 or SIGUSR2).
 * @param info Information about the signal.
 * @param context Context of the signal (not used).
 */
void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static char	bit_count;
	static char	character;
	static char	*g_ptr;

	(void)context;
	character = (char)(character << 1);
	if (sig == SIGUSR1)
		character = character | 1;
	bit_count++;
	if (bit_count == 8)
	{
		kill(info->si_pid, SIGUSR2);
		g_ptr = ft_strjoin_char(g_ptr, character);
		if (g_ptr == NULL)
			exit(-1);
		if (character == '\0')
		{
			ft_printf("%s", g_ptr);
			free(g_ptr);
			g_ptr = NULL;
		}
		character = 0;
		bit_count = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

/**
 * @brief Main function for the server.
 * Signal handler is set up to receive signals from the client.
 * The server will print the received string.
 * Should be run before the client.
 * Is waiting for signals to be received indefinitely.
 * 
 * @return int No return value.
 */
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
