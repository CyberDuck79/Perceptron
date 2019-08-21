/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_train.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 16:27:44 by fhenrion          #+#    #+#             */
/*   Updated: 2019/08/21 17:23:09 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perceptron.h"
#include <fcntl.h>

static float	get_learning_rate(void)
{
	float	learning_rate = 1.0;

	while (learning_rate >= 1.0)
	{
		write(1, "Entrez le taux d'apprentissage : ", 34);
		scanf("%f", &learning_rate);
		if (learning_rate >= 1.0)
			write(1, "\nErreur.", 8);
	}
	return (learning_rate);
}

static int		valid_line(char *buffer)
{
	for (int i = 0; i < 5; i++)
		if (!(buffer[i] == '1' || buffer[i] == ' '))
			return (0);
	return (1);
}

static letter	**parse_alphabet(int fd)
{
	letter	**alphabet;
	char	buffer[5];
	int		a = 0;

	alphabet = (letter**)malloc(sizeof(letter*) * 26);
	while (read(fd, &buffer, 1))
	{
		if (buffer[0] != '>')
			return (NULL);
		else
		{
			alphabet[a] = (letter*)malloc(sizeof(letter));
			read(fd, &alphabet[a]->letter, 1);
			for (int i = 0; i < 5; i++)
			{
				read(fd, &buffer, 1);
				read(fd, &buffer, 5);
				if (valid_line(buffer))
					for (int j = 0; j < 5; j++)
						alphabet[a]->matrix[i][j] = (buffer[j] == '1' ? 1 : 0);
				else
					return (NULL);
			}
			read(fd, &buffer, 2);
			a++;
		}
	}
	return (alphabet);
}

int		main(void)
{
	int		fd;
	int		let_i = 0;
	float	l_rate;
	letter	**alphabet;

	fd = open("alphabet.data", O_RDONLY);
	if (fd == -1) {
		perror("open failed");
		exit(1);
	}
	if(!(alphabet = parse_alphabet(fd)))
	{
		close(fd);
		perror("error in file");
		exit(1);
	}
	close(fd);
	if (alphabet)
	{
		l_rate = get_learning_rate();
		fd = open("export.data", O_WRONLY | O_CREAT, 0644);
		if (fd == -1)
		{
			perror("open failed");
			exit(1);
		}
		if (dup2(fd, 1) == -1)
		{
			perror("dup2 failed"); 
			exit(1);
		}
		for (char c = 'A'; c <= 'Z'; c++)
			train_perceptron(alphabet, let_i++, l_rate);
		close(fd);
	}
	return (0);
}