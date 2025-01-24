/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:19 by ppontet           #+#    #+#             */
/*   Updated: 2024/12/29 23:47:35 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *the_string);

/**
 * @brief Len of string
 *
 * @param the_string String to be measured
 * @return size_t len of the string
 */
size_t	ft_strlen(const char *the_string)
{
	size_t	count;

	count = 0;
	while (the_string[count] != '\0')
		count++;
	return (count);
}
