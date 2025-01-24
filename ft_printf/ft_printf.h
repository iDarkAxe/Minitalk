/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:33:31 by ppontet           #+#    #+#             */
/*   Updated: 2024/12/29 23:42:05 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);

// STR related functions
size_t	ft_strlen(const char *the_string);

// PRINT related functions
ssize_t	ft_putchar_fd(char c, int fd);
ssize_t	ft_putstr_fd(char *s, int fd);
ssize_t	ft_putnbr_fd(long long n, int fd);
ssize_t	ft_putnbr_hex(unsigned int nbr, char height);
ssize_t	ft_putnbr_base(unsigned long nbr, char *base);
ssize_t	ft_putpointer_fd(unsigned long ptr);

#endif
