/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   train_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 13:17:24 by fhenrion          #+#    #+#             */
/*   Updated: 2019/08/19 14:41:20 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perceptron.h"

void	initialize_train_set(float **train_set, int *desired)
{
	for (int i = 0; i < 40; i++)
		train_set[i] = (float*)malloc(sizeof(float) * 2);
	train_set[0][0] = 10;
	train_set[0][1] = 1;
	desired[0] = 0;
	train_set[1][0] = 12;
	train_set[1][1] = 9;
	desired[1] = 0;
	train_set[2][0] = 7;
	train_set[2][1] = 18;
	desired[2] = 0;
	train_set[3][0] = 9;
	train_set[3][1] = 2;
	desired[3] = 0;
	train_set[4][0] = 7;
	train_set[4][1] = 9;
	desired[4] = 0;
	train_set[5][0] = 4;
	train_set[5][1] = 18;
	desired[5] = 0;
	train_set[6][0] = 6;
	train_set[6][1] = 1;
	desired[6] = 0;
	train_set[7][0] = 9;
	train_set[7][1] = 9;
	desired[7] = 0;
	train_set[8][0] = 5;
	train_set[8][1] = 1;
	desired[8] = 0;
	train_set[9][0] = 1;
	train_set[9][1] = 5;
	desired[9] = 0;
	train_set[10][0] = 25;
	train_set[10][1] = 20;
	desired[10] = 1;
	train_set[11][0] = 45;
	train_set[11][1] = 21;
	desired[11] = 1;
	train_set[12][0] = 37;
	train_set[12][1] = 22;
	desired[12] = 1;
	train_set[13][0] = 22;
	train_set[13][1] = 38;
	desired[13] = 1;
	train_set[14][0] = 29;
	train_set[14][1] = 31;
	desired[14] = 1;
	train_set[15][0] = 42;
	train_set[15][1] = 24;
	desired[15] = 1;
	train_set[16][0] = 37;
	train_set[16][1] = 37;
	desired[16] = 1;
	train_set[17][0] = 26;
	train_set[17][1] = 41;
	desired[17] = 1;
	train_set[18][0] = 41;
	train_set[18][1] = 26;
	desired[18] = 1;
	train_set[19][0] = 42;
	train_set[19][1] = 42;
	desired[19] = 1;
	train_set[20][0] = 2;
	train_set[20][1] = 20;
	desired[20] = 0;
	train_set[21][0] = 5;
	train_set[21][1] = 21;
	desired[21] = 0;
	train_set[22][0] = 7;
	train_set[22][1] = 22;
	desired[22] = 0;
	train_set[23][0] = 2;
	train_set[23][1] = 38;
	desired[23] = 0;
	train_set[24][0] = 9;
	train_set[24][1] = 31;
	desired[24] = 0;
	train_set[25][0] = 2;
	train_set[25][1] = 24;
	desired[25] = 0;
	train_set[26][0] = 37;
	train_set[26][1] = 7;
	desired[26] = 1;
	train_set[27][0] = 26;
	train_set[27][1] = 1;
	desired[27] = 1;
	train_set[28][0] = 41;
	train_set[28][1] = 6;
	desired[28] = 1;
	train_set[29][0] = 42;
	train_set[29][1] = 2;
	desired[29] = 1;
	train_set[30][0] = 10;
	train_set[30][1] = 91;
	desired[30] = 0;
	train_set[31][0] = 12;
	train_set[31][1] = 99;
	desired[31] = 0;
	train_set[32][0] = 7;
	train_set[32][1] = 98;
	desired[32] = 0;
	train_set[33][0] = 9;
	train_set[33][1] = 92;
	desired[33] = 0;
	train_set[34][0] = 7;
	train_set[34][1] = 89;
	desired[34] = 0;
	train_set[35][0] = 49;
	train_set[35][1] = 18;
	desired[35] = 1;
	train_set[36][0] = 96;
	train_set[36][1] = 1;
	desired[36] = 1;
	train_set[37][0] = 99;
	train_set[37][1] = 9;
	desired[37] = 1;
	train_set[38][0] = 95;
	train_set[38][1] = 1;
	desired[38] = 1;
	train_set[39][0] = 91;
	train_set[39][1] = 5;
	desired[39] = 1;
}