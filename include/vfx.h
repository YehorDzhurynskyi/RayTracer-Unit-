/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vfx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VFX_H
# define VFX_H

# define BW_ID				0
# define SEPIA_ID			1
# define BLUR_ID			2
# define CARTOON_ID			3

# define BW_MASK			(1 << BW_ID)
# define SEPIA_MASK			(1 << SEPIA_ID)
# define BLUR_MASK			(1 << BLUR_ID)
# define CARTOON_MASK		(1 << CARTOON_ID)

# define BW_ENABLED(mask)		(mask & BW_MASK)
# define SEPIA_ENABLED(mask)	(mask & SEPIA_MASK)
# define BLUR_ENABLED(mask)		(mask & BLUR_MASK)
# define CARTOON_ENABLED(mask)	(mask & CARTOON_MASK)

typedef int	t_vfx_mask;

void	vfx_toggle_bw(void);
void	vfx_toggle_sepia(void);
void	vfx_toggle_blur(void);
void	vfx_toggle_cartoon(void);

#endif
