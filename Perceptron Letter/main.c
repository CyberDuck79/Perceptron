/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 16:27:44 by fhenrion          #+#    #+#             */
/*   Updated: 2019/08/20 18:53:07 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perceptron.h"
#include <fcntl.h>



static int		get_train_letter(letter **alphabet, int len)
{
	char	c = 0;
	int		valid_input = 0;

	while (!valid_input)
	{
		write(1, "\nLettre d'entrainement : ", 25);
		if (!(valid_input = scanf("%c", &c)))
			write(1, "\nErreur de type.", 16);
	}
	for (int i = 0; i < len; i++)
		if (c == alphabet[i]->letter)
			return (i);
	return (-1);
}

static int		valid_line(char *buffer)
{
	for (int i = 0; i < 5; i++)
		if (!(buffer[i] == '1' || buffer[i] == ' '))
			return (0);
	return (1);
}

static letter	**parse_alphabet(int fd, int len)
{
	letter	**alphabet;
	char	buffer[5];
	int		a = 0;

	alphabet = (letter**)malloc(sizeof(letter*) * len);
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

static int		count_letter(int fd)
{
	int		len = 0;
	char	c;

	while (read(fd, &c, 1))
		if (c == '>')
			len++;
	return (len);
}

int		main(int argc, char **argv)
{
	int		fd;
	int		len;
	int		let_i;
	letter	**alphabet = NULL;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		len = count_letter(fd);
		close(fd);
		fd = open(argv[1], O_RDONLY);
		alphabet = parse_alphabet(fd, len);
		close(fd);
		alphabet ? write(1, "fichier lue\n", 12) : write(1, "erreur\n", 7);
	}
	if (alphabet)
	{
		let_i = get_train_letter(alphabet, len);
		if (let_i >= 0)
			perceptron(alphabet, let_i, len);
		else
			write(1, "erreur\n", 7);
	}
	return (0);
}