/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_wd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 13:09:43 by supersko          #+#    #+#             */
/*   Updated: 2025/04/09 13:41:10 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_get_next_wd(char *sentence, char sep)
{
	if (!(*sentence))
		sentence = NULL;
	else
		while (*sentence && *sentence != sep)
			sentence++;
	if (*sentence == sep)
		while (*sentence == sep)
			sentence++;
	return (sentence);
}
