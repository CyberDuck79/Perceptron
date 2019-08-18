/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   train_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 13:17:24 by fhenrion          #+#    #+#             */
/*   Updated: 2019/08/18 14:04:11 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perceptron.h"

void	initialize_train_set(float **train_set)
{
	train_set[0][0] = 10;
	train_set[0][1] = 1;
	train_set[0][2] = -1;
	train_set[1][0] = 12;
	train_set[1][1] = 9;
	train_set[1][2] = -1;
	train_set[2][0] = 7;
	train_set[2][1] = 18;
	train_set[2][2] = -1;
	train_set[3][0] = 9;
	train_set[3][1] = 2;
	train_set[3][2] = -1;
	train_set[4][0] = 7;
	train_set[4][1] = 9;
	train_set[4][2] = -1;
	train_set[5][0] = 4;
	train_set[5][1] = 18;
	train_set[5][2] = -1;
	train_set[6][0] = 6;
	train_set[6][1] = 1;
	train_set[6][2] = -1;
	train_set[7][0] = 9;
	train_set[7][1] = 9;
	train_set[7][2] = -1;
	train_set[8][0] = 5;
	train_set[8][1] = 1;
	train_set[8][2] = -1;
	train_set[9][0] = 1;
	train_set[9][1] = 5;
	train_set[9][2] = -1;
	train_set[10][0] = 25;
	train_set[10][1] = 20;
	train_set[10][2] = 1;
	train_set[11][0] = 45;
	train_set[11][1] = 21;
	train_set[11][2] = 1;
	train_set[12][0] = 37;
	train_set[12][1] = 22;
	train_set[12][2] = 1;
	train_set[13][0] = 22;
	train_set[13][1] = 38;
	train_set[13][2] = 1;
	train_set[14][0] = 29;
	train_set[14][1] = 31;
	train_set[14][2] = 1;
	train_set[15][0] = 42;
	train_set[15][1] = 24;
	train_set[15][2] = 1;
	train_set[16][0] = 37;
	train_set[16][1] = 37;
	train_set[16][2] = 1;
	train_set[17][0] = 26;
	train_set[17][1] = 41;
	train_set[17][2] = 1;
	train_set[18][0] = 41;
	train_set[18][1] = 26;
	train_set[18][2] = 1;
	train_set[19][0] = 42;
	train_set[19][1] = 42;
	train_set[19][2] = 1;
	train_set[20][0] = 2;
	train_set[20][1] = 20;
	train_set[20][2] = -1;
	train_set[21][0] = 5;
	train_set[21][1] = 21;
	train_set[21][2] = -1;
	train_set[22][0] = 7;
	train_set[22][1] = 22;
	train_set[22][2] = -1;
	train_set[23][0] = 2;
	train_set[23][1] = 38;
	train_set[23][2] = -1;
	train_set[24][0] = 9;
	train_set[24][1] = 31;
	train_set[24][2] = -1;
	train_set[25][0] = 2;
	train_set[25][1] = 24;
	train_set[25][2] = -1;
	train_set[26][0] = 37;
	train_set[26][1] = 7;
	train_set[26][2] = 1;
	train_set[27][0] = 26;
	train_set[27][1] = 1;
	train_set[27][2] = 1;
	train_set[28][0] = 41;
	train_set[28][1] = 6;
	train_set[28][2] = 1;
	train_set[29][0] = 42;
	train_set[29][1] = 2;
	train_set[29][2] = 1;
}