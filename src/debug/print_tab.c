/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/11 15:53:18 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

void print_tab(char **tab)
{
    int i = 0;
    while (tab[i])
    {
        printf("%s\n", tab[i]);
        i++;
    }
}

void	print_game(t_game *game)
{
	printf("map:\n");
    if (game->map.tab) {
        print_tab(game->map.tab);
    }
    else {
        printf("NO MAP\n");
    }
	printf("\n");																								
	printf("north:														 %s\n", game->textures.f_names[NORTH]);
	printf("south:														 %s\n", game->textures.f_names[SOUTH]);
	printf("west:															 %s\n", game->textures.f_names[WEST]);
	printf("east:															 %s\n", game->textures.f_names[EAST]);
	printf("floor:		 %d %d %d\n", game->textures.floor.r, game->textures.floor.g, game->textures.floor.b);
	printf("ceiling: %d %d %d\n", game->textures.ceiling.r, game->textures.ceiling.g, game->textures.ceiling.b);
	printf("size: width %d height %d\n", game->map.width, game->map.height);

}
