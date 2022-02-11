/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:23:30 by acarneir          #+#    #+#             */
/*   Updated: 2022/02/10 22:26:50 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	is_map_rectangular(t_game *game)
{
	int	row;
	int	len;

	row = 0;
	len = ft_strlen(game->map.matrix[row]);
	while (game->map.matrix[row])
	{
		// printf("row = %d len = %d->%s<-\n", row, (int)ft_strlen(game->map.matrix[row]),  game->map.matrix[row]);
		// if(len != (int)ft_strlen(game->map.matrix[row]))
		{
			len = -1;
			break ;
		}
		row++;
	}
	if (len == -1)
	{
		free_map(game->map.matrix);
		print_error("Map must be rectangular");
	}
}

void	check_map(t_game *game)
{
	is_map_rectangular(game);
}
