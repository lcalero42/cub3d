/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_door_handling_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:59:19 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/30 17:30:22 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// Initialize doors: Each door is closed at start
void init_door_system(t_data *data)
{
    int x, y, door_index;

    door_index = 0;
    data->door_count = 0;
    for (y = 0; y < data->grid.height && door_index < MAX_DOORS; y++)
    {
        for (x = 0; x < data->grid.width && door_index < MAX_DOORS; x++)
        {
            if (data->grid.grid[y][x] == '2')
            {
                data->doors[door_index].x = x;
                data->doors[door_index].y = y;
                data->doors[door_index].state = DOOR_CLOSED;
                data->doors[door_index].last_interaction_time = 0;
                door_index++;
            }
        }
    }
    data->door_count = door_index;
    data->last_door_interaction = 0;
}

// Search for a door at a specific grid location
t_door *find_door_at(t_data *data, int x, int y)
{
    for (int i = 0; i < data->door_count; i++)
        if (data->doors[i].x == x && data->doors[i].y == y)
            return &data->doors[i];
    return NULL;
}

// Open/close a door instantly when space is pressed
void check_door_interaction(t_data *data, int keycode)
{
    t_ray middle_ray;
    int map_x, map_y;
    t_door *door;
    long long current_time;

    if (keycode != XK_space)
        return;
    current_time = get_current_time();
    middle_ray = data->rays[WINDOW_WIDTH / 2];
    map_x = (int)middle_ray.map_pos.x;
    map_y = (int)middle_ray.map_pos.y;
    int dx = (int)(data->player.position.x + cos(data->player.angle));
    int dy = (int)(data->player.position.y + sin(data->player.angle));
    if (data->grid.grid[dy][dx] == '2')
    {
        door = find_door_at(data, dx, dy);
        if (door)
        {
            toggle_door(door);
            data->last_door_interaction = current_time;
        }
    }
}

// Instantly toggle door state and texture (no progress logic!)
void toggle_door(t_door *door)
{
    if (door->state == DOOR_CLOSED)
        door->state = DOOR_OPEN;
    else
        door->state = DOOR_CLOSED;
}

// Return the relevant texture for closed/open door
t_texture_info get_door_texture(t_data *data, t_door *door)
{
    if (door->state == DOOR_CLOSED)
        return data->door_closed.info;
    else
        return data->door_opened.info;
}

// Only blocks ray if the door is closed – no animation logic
int should_door_block_ray(t_door *door)
{
    return (door->state == DOOR_CLOSED);
}
