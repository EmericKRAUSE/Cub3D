/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/11 13:37:39 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

char **dup_tab(char **tab)
{
    char **dup;
    int i;

    i = 0;
	if (!tab)
		return (NULL);
    dup = ft_calloc(sizeof(char *), (ft_tablen(tab) + 1));
    if (!dup)
        return (NULL);
    while (tab[i])
    {
        dup[i] = ft_strdup(tab[i]);
        i++;
    }
    dup[i] = NULL;
    return (dup);
}

void    set_map_point(char **map, t_point pt, char c)
{
    map[pt.y][pt.x] = c;
}
