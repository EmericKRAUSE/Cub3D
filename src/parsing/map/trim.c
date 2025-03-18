/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/03/17 15:58:48 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

int	smallest_blank_gap_at_left_side(char **map)
{
	int	smallest_gap;
	int	i;

	smallest_gap = INT_MAX;
	if (!map)
		return (-1);
	while (*map)
	{
		i = 0;
		while ((*map)[i] == ' ')
			i++;
		if (i < smallest_gap)
			smallest_gap = i;
		map++;
	}
	return (smallest_gap);
}

void	shift_to_left(char ***map_addr)
{
	int		smallest_gap;
	char	**map;
	char	*line;
	int		i;

	map = *map_addr;
	smallest_gap = smallest_blank_gap_at_left_side(map);
	i = 0;
	while (map[i])
	{
		line = map[i];
		while (line[smallest_gap])
		{
			*line = line[smallest_gap];
			line++;
		}
		*line = line[smallest_gap];
		i++;
	}
	*map_addr = map;
}

void	ft_trim_right(char ***map_addr)
{
	int		i;
	int		j;
	char	**map;

	map = *map_addr;
	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		j = ft_strlen(map[i]) - 1;
		while (ft_strchr(" \n", map[i][j]))
			j--;
		map[i][j + 1] = '\0';
		i++;
	}
	*map_addr = map;
}

void	trim_map(char ***map_addr)
{
	delete_blank_lines(map_addr);
	if (*map_addr)
		shift_to_left(map_addr);
	ft_trim_right(map_addr);
}
