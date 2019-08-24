/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   train_perceptron.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:59:35 by fhenrion          #+#    #+#             */
/*   Updated: 2019/08/24 10:17:18 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perceptron.h"

/*
TODO :
perceptron simple avec 30 entrees (-1,1) :
 - poids de depart aleatoires. OK
 - choisir une lettre designee comme juste. OK
 - faire l'entrainement => presenter toutes les lettres. OK
 - un nombre choisit de passage ou jusque plus d'erreur. -> plus d'erreur OK
 - seuil et sigmoide. -> seuil OK
 - faire passage de test avec plus ou moins d'entropie.
 - faire export des poids pour chaque lettres vers un fichier. OK
 - faire une fonction prenant une lettre et reconnaissant la lettre. OK
 - menage / rationalisation / factorisation !!!
*/

//fonction sigmoide
static double	sigmo(double a)
{
	if (a < -20.0)
	{
		return 0.0;
	}
	else if (a > 20.0)
	{
		return 1.0;
	}
	return (1.0 / (1.0 + exp(-a)));
}


static int		activate(int **matrix, float *weights)
{
	float	sum = 0;

	for (int y = 0; y < X; y++)
			for (int x = 0; X < 5; x++)
				sum += matrix[x][y] * weights[x + (y*5)];
	sum += weights[X*X];
	// fonction d'activation : a seuil ou de Heaviside
	//return (sum < 0 ? 0 : 1);
	// fonction d'activation : sigmoide
	return (sigmo(sum) > 0.5 ? 1 : 0);
}

static void		adjust(int **mtx, float *weights, float l_rate, int error)
{
	int	wi;

	for (int y = 0; y < X; y++)
		for (int x = 0; x < X; x++)
		{
			wi = x + (y*5);
			weights[wi] = weights[wi] + (mtx[x][y] * l_rate * error);
		}
	weights[X*X] = weights[X*X] + (l_rate * error);
}

static int		train(letter **alpha, float *weights, int let_i, float l_rate)
{
	float			error;
	int				nb_errors = 0;

	for (int i = 0; i < N; i++)
	{
		error = (i == let_i ? 1 : 0) - activate(alpha[i]->matrix, weights);
		if (error)
			nb_errors++;
		adjust(alpha[i]->matrix, weights, l_rate, error);
	}
	return (nb_errors);
}

void			train_perceptron(letter **alphabet, int let_i, float l_rate)
{
	float	*weights = (float*)malloc(sizeof(float) * (X*X)+1);
	int		try = 0;

	for (int i = 0; i < (X*X)+1; i++)
		weights[i] = (float)rand()/RAND_MAX;
	while (train(alphabet, weights, let_i, l_rate) && try < 100)
		try++;
	printf(">%c\n", alphabet[let_i]->letter);
	for (int y = 0; y < X; y++)
			for (int x = 0; x < X; x++)
				printf("%-+12f\n", weights[x + (y*5)]);
	printf("%-+12f\n\n", weights[X*X]);
}