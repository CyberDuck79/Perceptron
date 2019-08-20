/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perceptron.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:59:35 by fhenrion          #+#    #+#             */
/*   Updated: 2019/08/20 19:00:23 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perceptron.h"

/*
TODO :
perceptron simple avec 30 entrees (-1,1) :
 - poids de depart aleatoires. OK
 - choisir une lettre designee comme juste. OK
 - faire l'entrainement => presenter toutes les lettres. OK
 - un nombre choisit de passage ou jusque plus d'erreur.
 - seuil et sigmoide.
*/

/*fonction sigmoide
static double	sigmo(double a)
{
	double	aux = exp(a);

	return (1 / (aux + 1));
}
*/

static float	get_learning_rate(void)
{
	float	learning_rate = 1.0;

	while (learning_rate >= 1.0)
	{
		write(1, "\nEntrez le taux d'apprentissage : ", 34);
		if (!scanf("%f", &learning_rate))
			write(1, "\nErreur de type.", 16);
		if (learning_rate >= 1.0)
			write(1, "\nErreur >= 1.", 13);
	}
	return (learning_rate);
}

static int		activate(int matrix[5][5], float *weights)
{
	float	sum = 0;

	for (int y = 0; y < 5; y++)
			for (int x = 0; x < 5; x++)
				sum += matrix[x][y] * weights[x + (y*5)];
	sum += weights[25];
	// fonction d'activation : a seuil ou de Heaviside
	return (sum < 0 ? -1 : 1);
	// fonction d'activation : sigmoide
	//return (sigmo(sum) > 0.5 ? -1 : 1);
}

static void		adjust(int mtx[5][5], float *weights, float l_rate, int error)
{
	int	wi;

	for (int y = 0; y < 5; y++)
			for (int x = 0; x < 5; x++)
			{
				wi = x + (y*5);
				weights[wi] = weights[wi] + (mtx[x][y] * l_rate * error);
			}
	weights[25] = weights[25] + (l_rate * error);
}

static int		train(letter **alphabet, float *weights, int let_i, int len)
{
	static float	learning_rate = 0;
	int				error;
	int				nb_errors = 0;

	if (!learning_rate)
		learning_rate = get_learning_rate();
	for (int i = 0; i < len; i++)
	{
		error = (i == let_i ? 1 : -1) - activate(alphabet[i]->matrix, weights);
		if (error)
			nb_errors++;
		adjust(alphabet[i]->matrix, weights, learning_rate, error);
	}
	return (nb_errors);
}

// SUPERVISED LEARNING - 2D inputs classifier
void			perceptron(letter **alphabet, int let_i, int len)
{

	float	*weights = (float*)malloc(sizeof(float) * 26);
	int		try = 0;
	int		errors;

	for (int i = 0; i < 26; i++)
		weights[i] = (float)rand()/RAND_MAX;
	while ((errors = train(alphabet, weights, let_i, len)))
	{
		try++;
		printf("essai %d, nombres d'erreurs : %d\n", try, errors);
	}
	printf("SUCCES\n");
	for (int y = 0; y < 5; y++)
			for (int x = 0; x < 5; x++)
				printf("w%d : %f\n", x + (y*5), weights[x + (y*5)]);
	printf("w%d : %f\n", 25, weights[25]);
}