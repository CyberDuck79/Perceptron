/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perceptron.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 16:39:13 by fhenrion          #+#    #+#             */
/*   Updated: 2019/08/18 15:15:10 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "perceptron.h"

// SUPERVISED LEARNING - 2D inputs classifier
int		main(void)
{
	float	**train_set;
	float	*weights;
	float	sum = 0;
	int		*desired;
	int		error = 0;
	int		result = 0;
	int		success = 0;
	int		fails = 0;
	int		try = 0;

	train_set = (float**)malloc(sizeof(float*) * 40);
	weights = (float*)malloc(sizeof(float) * 3);
	desired = (int*)malloc(sizeof(int) * 40);
	for (int i = 0; i < 40; i++)
		train_set[i] = (float*)malloc(sizeof(float) * 2);
	initialize_train_set(train_set, desired);
	weights[0] = (float)rand()/RAND_MAX;
	weights[1] = (float)rand()/RAND_MAX;
	weights[2] = (float)rand()/RAND_MAX;

	while (success < 40)
	{
		success = 0;
		fails = 0;
		try++;
		printf("\033[0;33m########### TRY NUMBER : %d\033[0m\n", try);
		for (int j = 0; j < 40; j++)
		{
			sum = 0;
			for (int i = 0; i < 2; i++)
					sum += train_set[j][i] * weights[i];
			sum += 1 * weights[2];
			result = sum < 0 ? -1 : 1;
			error = desired[j] - result;
			if (!error)
				success++;
			else
				fails++;
			weights[0] = weights[0] + (error * train_set[j][0]);
			weights[1] = weights[1] + (error * train_set[j][1]);
			weights[2] = weights[2] + error;
		}
		printf("\033[0;31m########### ERRORS     : %d\033[0m\n", fails);
	}
	printf("\033[0;32m########### SUCCESS\033[0m\n");
	return (0);
}
