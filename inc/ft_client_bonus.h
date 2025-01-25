/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:21:14 by ppontet           #+#    #+#             */
/*   Updated: 2025/01/25 13:04:57 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CLIENT_BONUS_H
# define FT_CLIENT_BONUS_H

# define ACK_TIMEOUT 10000

# include <signal.h>

int	ft_atoi(const char *nptr);
// BONUS PART
int	find_server_pid(int argc, char **argv, char **string, pid_t *g_server_pid);

#endif
