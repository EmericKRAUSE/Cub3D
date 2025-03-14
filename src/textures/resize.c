/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/14 18:46:30 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

uint8_t get_pixel(mlx_texture_t *texture, uint32_t x, uint32_t y)
{
    if (x >= texture->width || y >= texture->height)
        return (0);
    return (texture->pixels[y * texture->bytes_per_pixel + x * texture->bytes_per_pixel]);
}

/* resize a line texture  (should be used with texture_line returned value) */
mlx_texture_t texture_resize_line(mlx_texture_t *texture, int32_t scaled_height)
{
    mlx_texture_t	resized_line;
    int step;
    float step_size;

    resized_line.width = 1;
    resized_line.height = scaled_height;
    resized_line.bytes_per_pixel = texture->bytes_per_pixel;
    resized_line.pixels = malloc(scaled_height * texture->bytes_per_pixel);
    step_size = scaled_height / (float)texture->height;
    step = 0;
    while (step < scaled_height)
    {
        resized_line.pixels[step] = get_pixel(texture, 0, step / step_size);
        step++;
    }
    return (resized_line);
}

/* return the line texture into a single pixel texture */
mlx_texture_t texture_line(mlx_texture_t *texture, float hit_ratio)
{
    mlx_texture_t line_texture;
    uint8_t next_pixel;
    uint32_t i_height;

    line_texture.width = 1;
    line_texture.height = texture->height;
    line_texture.bytes_per_pixel = texture->bytes_per_pixel;
    line_texture.pixels = malloc(texture->height * texture->bytes_per_pixel);
    i_height = 0;
    if (hit_ratio < 0 || hit_ratio > 1)
    {
        fprintf(stderr, "Invalid hit ratio: %f\n", hit_ratio);
    }
    while (i_height < texture->height)
    {
        next_pixel = get_pixel(texture, hit_ratio * texture->width, i_height);
        line_texture.pixels[i_height] = texture->pixels[next_pixel];
        i_height++;
    }
    return (line_texture);
}