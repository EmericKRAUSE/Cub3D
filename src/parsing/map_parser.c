#include <cube3d.h>

int	get_map_width(int fd)
{
	ssize_t byte_read;
	char buffer;
	int	x;
	int	tmp_x;
	
	x = 0;
	tmp_x = 0;
	while ((byte_read = read(fd, &buffer, 1)) > 0)
	{
		if (buffer == '\n')
		{
			if (x < tmp_x)
				x = tmp_x;
			tmp_x = 0;
		}
		else
			tmp_x++;
	}
	if (x < tmp_x)
		x = tmp_x;
	if (byte_read == -1)
		return (-1);
	return (x);
}

int	get_map_height(int fd)
{
	ssize_t byte_read;
	char buffer;
	int	y;
	
	byte_read = -1;
	y = 0;
	while ((byte_read = read(fd, &buffer, 1)) > 0)
	{
		if (buffer == '\n')
			y++;
	}
	if (byte_read == -1)
		return (-1);
	y++;
	return (y);
}

int	get_map_size(t_map *map, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	map->width = get_map_width(fd);
	close (fd);
	
	fd = open(filename, O_RDONLY);
	map->height = get_map_height(fd);
	close (fd);
	
	if (map->width == -1 || map->height == -1)
		return (-1);
	
	return (1);
}

void    free_map(t_map *map)
{
    int y;

    y = 0;
    while (y < map->height)
        free(map->tab[y++]);
    free (map->tab);
}

int alloc_map(t_map *map)
{
    int y;

    y = 0;
    map->tab = malloc(sizeof(char *) * (map->height + 1));
    if (!map->tab)
        return (-1);
    while (y < map->height)
    {
        map->tab[y] = malloc(sizeof(char) * (map->width + 1));
        if (!map->tab[y])
        {
            free_map(map);
            return (-1);
        }
        y++;
    }
	return (1);
}

int fill_map(t_map *map, char *filename)
{
	ssize_t byte_read;
	char buffer;
    int fd;
    int x;
	int	y;
	
    fd = open(filename, O_RDONLY);
	byte_read = -1;
	y = 0;
    x = 0;
	while ((byte_read = read(fd, &buffer, 1)) > 0)
	{
        if (buffer == '\n')
		{
			map->tab[y][x] = '\0';
			y++;
			x = 0;
		}
		else
		{
			map->tab[y][x] = buffer;
			x++;
		}
	}
	close(fd);
	return (1);
}

int map_parser(t_map *map, char *filename)
{
    if (get_map_size(map, filename) == -1)
        return (-1);
    if (alloc_map(map) == -1)
    	return (-1);
    if (fill_map(map, filename) == -1)
        return (-1);
    return (1);
}
