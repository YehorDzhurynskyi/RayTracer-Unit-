/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirlight.cl                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

inline t_vec4		dirlight_to(__constant t_dirlight *dirlight)
{
	// TODO: maybe multiply by -10000.0 cause dir light is located far away
	return (dirlight->direction * -1.0f);
}

inline t_bool		dirlight_in_shadow(void)
{
	return (TRUE);
}

uchar4				dirlight_illuminate(__constant t_light *light,
__constant t_dirlight *dirlight, const t_fragment *fragment)
{
	const t_vec4 to_light = normalize(dirlight_to(dirlight));
	const uchar4 diffcolor = diffuse(light, fragment, to_light);
	const uchar4 speccolor = specular(light, fragment, to_light);
	return (color_add(diffcolor, speccolor));
}
