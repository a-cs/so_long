/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 20:38:28 by acarneir          #+#    #+#             */
/*   Updated: 2022/02/09 22:28:59 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	open_fd(char **argv)
{
	int		fd;
	char	*path;

	path = ft_strjoin("./maps/", argv[1]);
	fd = open(path, O_RDWR);
	free(path);
	return (fd);
}

void	check_args(int argc, char **argv)
{
	int		fd;

	if (argc == 2)
	{
		if (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".ber", 4) != 0)
			print_error("The argument must be a .ber file.");
	}
	else
		print_error("Invalid number of arguments! Try again.");
	fd = open_fd(argv);
	if (fd < 0)
		print_error("File not found.");
	close(fd);
}
