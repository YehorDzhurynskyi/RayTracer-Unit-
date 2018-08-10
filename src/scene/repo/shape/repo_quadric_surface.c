/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repo_quadric_surface.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"
#include <math.h>

t_quadric_surface	deserialize_quadric_surface(const t_cson *cson)
{
	t_quadric_surface	quadric_surface;
	const t_cson		*coefs_cson;

	coefs_cson = cson_valueof(cson, CSON_COEFS_KEY);
	// quadric_surface.coefs.s0 = cson_get_real(cson_at(coefs_cson, 0));
	// quadric_surface.coefs.s1 = cson_get_real(cson_at(coefs_cson, 3));
	// quadric_surface.coefs.s2 = cson_get_real(cson_at(coefs_cson, 5));
	// quadric_surface.coefs.s3 = cson_get_real(cson_at(coefs_cson, 6));

	// quadric_surface.coefs.s4 = cson_get_real(cson_at(coefs_cson, 3));
	// quadric_surface.coefs.s5 = cson_get_real(cson_at(coefs_cson, 1));
	// quadric_surface.coefs.s6 = cson_get_real(cson_at(coefs_cson, 4));
	// quadric_surface.coefs.s7 = cson_get_real(cson_at(coefs_cson, 7));

	// quadric_surface.coefs.s8 = cson_get_real(cson_at(coefs_cson, 5));
	// quadric_surface.coefs.s9 = cson_get_real(cson_at(coefs_cson, 4));
	// quadric_surface.coefs.sa = cson_get_real(cson_at(coefs_cson, 2));
	// quadric_surface.coefs.sb = cson_get_real(cson_at(coefs_cson, 8));

	// quadric_surface.coefs.sc = cson_get_real(cson_at(coefs_cson, 6));
	// quadric_surface.coefs.sd = cson_get_real(cson_at(coefs_cson, 7));
	// quadric_surface.coefs.se = cson_get_real(cson_at(coefs_cson, 8));
	// quadric_surface.coefs.sf = cson_get_real(cson_at(coefs_cson, 9));
	quadric_surface.coefs.s0 = cson_get_real(cson_at(coefs_cson, 0));
	quadric_surface.coefs.s1 = cson_get_real(cson_at(coefs_cson, 1));
	quadric_surface.coefs.s2 = cson_get_real(cson_at(coefs_cson, 2));
	quadric_surface.coefs.s3 = cson_get_real(cson_at(coefs_cson, 3));

	quadric_surface.coefs.s4 = cson_get_real(cson_at(coefs_cson, 1));
	quadric_surface.coefs.s5 = cson_get_real(cson_at(coefs_cson, 4));
	quadric_surface.coefs.s6 = cson_get_real(cson_at(coefs_cson, 5));
	quadric_surface.coefs.s7 = cson_get_real(cson_at(coefs_cson, 6));

	quadric_surface.coefs.s8 = cson_get_real(cson_at(coefs_cson, 2));
	quadric_surface.coefs.s9 = cson_get_real(cson_at(coefs_cson, 5));
	quadric_surface.coefs.sa = cson_get_real(cson_at(coefs_cson, 7));
	quadric_surface.coefs.sb = cson_get_real(cson_at(coefs_cson, 8));

	quadric_surface.coefs.sc = cson_get_real(cson_at(coefs_cson, 3));
	quadric_surface.coefs.sd = cson_get_real(cson_at(coefs_cson, 6));
	quadric_surface.coefs.se = cson_get_real(cson_at(coefs_cson, 8));
	quadric_surface.coefs.sf = cson_get_real(cson_at(coefs_cson, 9));
	return (quadric_surface);
}
