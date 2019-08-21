/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_reco.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 11:42:08 by fhenrion          #+#    #+#             */
/*   Updated: 2019/08/21 15:58:13 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perceptron.h"
#include <fcntl.h>

static int		valid_line(char *buffer)
{
	for (int i = 0; i < 5; i++)
		if (!(buffer[i] == '1' || buffer[i] == ' '))
			return (0);
	return (1);
}

static int		**parse_letter(int fd)
{
	char	buffer[5];
	int		**matrix;

	matrix = (int**)malloc(sizeof(int*) * 5);
	for (int i = 0; i < 5; i++)
	{
		matrix[i] = (int*)malloc(sizeof(int) * 5);
		read(fd, &buffer, 5);
		if (valid_line(buffer))
			for (int j = 0; j < 5; j++)
				matrix[i][j] = (buffer[j] == '1' ? 1 : 0);
		else
			return (NULL);
		read(fd, &buffer, 1);
	}
	return (matrix);
}

static weights	**parse_weights(int fd)
{
	char	buffer[12];
	weights	**alphabet;
	int		a = 0;

	alphabet = (weights**)malloc(sizeof(weights*) * 26);
	while (read(fd, &buffer, 1))
	{
		if (buffer[0] != '>')
			return (NULL);
		else
		{
			alphabet[a] = (weights*)malloc(sizeof(weights));
			alphabet[a]->weights = (float*)malloc(sizeof(float) * 26);
			read(fd, &alphabet[a]->letter, 1);
			for (int i = 0; i < 26; i++)
			{
				read(fd, &buffer, 1);
				read(fd, &buffer, 12);
				if(!(alphabet[a]->weights[i] = atof(buffer)))
					return (NULL);
			}
			read(fd, &buffer, 2);
			a++;
		}
	}
	return (alphabet);
}

int			main(void)
{
	int		fd;
	int		**matrix;
	weights	**alphabet;

	fd = open("test.data", O_RDONLY);
	if (fd == -1)
	{
		perror("open failed");
		exit(1);
	}
	if (!(matrix = parse_letter(fd)))
	{
		perror("error in file test");
		exit(1);
	}
	close(fd);
	fd = open("export.data", O_RDONLY);
	if (fd == -1)
	{
		perror("open failed");
		exit(1);
	}
	if (!(alphabet = parse_weights(fd)))
	{
		perror("error in file export");
		exit(1);
	}
	close(fd);
	reco_perceptron(alphabet, matrix);
	return (0);
}