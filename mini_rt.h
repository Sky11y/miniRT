/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:41:25 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/27 11:13:30 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

#include <unistd.h>	//open, close, read, write, exit
#include <stdlib.h>	//malloc, free
#include <stdio.h>	//printf, perror
#include <string.h> //strerror
#include <math.h>
#include <stdint.h>

#define PI 3.1415926535

typedef struct s_vec4
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
} t_vec4;


typedef struct s_vec3f
{
	float	x;
	float	y;
	float	z;
} t_vec3f;

typedef struct s_vec2
{
	uint16_t	u;
	uint16_t	v;
} t_vec2;

float	inverse_sqrt(float nbr);


#endif
