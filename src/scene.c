/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "ft.h"
#include <stdlib.h>
#include "error.h"
#include "geometry.h"
#include "light.h"

t_scene	*scene_alloc(void)
{
	t_scene	*scene;

	scene = (t_scene*)malloc(sizeof(t_scene));
	check_mem_alloc(scene);
	scene->cam = camera_create();
	scene->geometry = alst_create(6);
	check_mem_alloc(scene->geometry);
	scene->light = alst_create(6);
	check_mem_alloc(scene->light);
	return (scene);
}

void	scene_cleanup(t_scene **scene)
{
	alst_clear((*scene)->light, (void (*)(void**))light_cleanup);
	alst_del(&(*scene)->light);
	alst_clear((*scene)->geometry, (void (*)(void**))geometry_cleanup);
	alst_del(&(*scene)->geometry);
	ft_memdel((void**)scene);
}
