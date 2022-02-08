/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 22:33:55 by acarneir          #+#    #+#             */
/*   Updated: 2022/02/07 22:13:58 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	print_error(char *msg)
{
	printf("Error\n%s\n", msg);
	exit(0);
}

int	main(int argc, char **argv)
{
	int	fd;

	if (argc == 2)
	{
		printf("argv = %s\n", argv[1]);
		if (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".ber", 4) != 0)
			print_error("The argument must be a .ber file.");
	}
	else
		print_error("Invalid number of arguments! Try again.");
	fd = open(ft_strjoin("./maps/", argv[1]), O_RDWR);
	if (fd < 0)
		print_error("File not found.");
	printf("fd = %d\n", fd);
	close(fd);
	return (0);
}
