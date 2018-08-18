/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.cl                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

const sampler_t sampler = CLK_NORMALIZED_COORDS_TRUE | CLK_ADDRESS_REPEAT | CLK_FILTER_LINEAR;

static t_scalar	my_rand2(int x, int y)
{
	int n = x + y * 57;
	n = (n << 13) ^ n;
	return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}

static t_scalar	my_rand(t_scalar x, t_scalar y)
{
	uint2 randoms = (uint2)(x * 256, y * 128);
	uint seed = randoms.x + 15731;
	uint t = seed ^ (seed << 11);
	uint result = randoms.y ^ (randoms.y >> 19) ^ (t ^ (t >> 8));
	return ((result % 1024) / 1024.0f);
}

static t_rcolor	perlin_texture_map(__constant t_texture *texture, t_scalar u, t_scalar v)
{
	__constant t_perlin_texture *perlin_tex = (__constant t_perlin_texture*)(texture + 1);
	int			size = perlin_tex->size;
	t_scalar	value = 0.0f;
	t_scalar	initialSize = (t_scalar)(size * 2.0f);

	while(size >= 1)
	{
		value += my_rand(u / size, v / size) * size;
		size /= 2.0f;
	}
	return(value / initialSize);
}

static t_rcolor	wave_texture_map(t_scalar u, t_scalar v)
{
	t_rcolor	res;
	res.x = cos(u * 2.0f * M_PI);
	res.y = sin(v * 2.0f * M_PI);
	res.z = 1.0f;
	res.a = 0.0f;
	return (normalize(res));
}

static t_rcolor	chess_texture_map(__constant t_texture *texture, t_scalar u, t_scalar v)
{
	__constant t_chess_texture *chess_tex = (__constant t_chess_texture*)(texture + 1);
	int a = (int)round(v) & 1;
	int b = (int)round(u) & 1;
	return (color2rcolor(a ^ b ? chess_tex->color1 : chess_tex->color2));
}

static t_rcolor	climage_texture_map(__read_only image2d_array_t textures,
__constant t_texture *texture, t_scalar u, t_scalar v)
{
	__constant t_climage_texture *climage_tex = (__constant t_climage_texture*)(texture + 1);
	t_vec4 col = read_imagef(textures, sampler, (float4)(u, v, (float)climage_tex->tex_index, 0.0f));
	col.x = 0.0f;
	return (col.wzyx);
}

t_rcolor		texture_map(const t_scene_buffers *buffers, __read_only image2d_array_t textures,
t_address tex_addr, t_scalar u, t_scalar v)
{
	__constant t_texture *texture = (__constant t_texture*)(buffers->texturebuffer + tex_addr);
	u = u * texture->scale + texture->u_offset;
	v = v * texture->scale + texture->v_offset;
	if (texture->texture_type == CHESS)
		return (chess_texture_map(texture, u, v));
	else if (texture->texture_type == CLIMAGE)
		return (climage_texture_map(textures, texture, u, v));
	else if (texture->texture_type == PERLIN)
	{
		t_rcolor perlin = perlin_texture_map(texture, u, v);
		perlin.a = 0.0f;
		return (perlin);
	}
	else if (texture->texture_type == WAVE)
		return (wave_texture_map(u, v));
	return (0.0f);
}

t_vec4			normal_map(const t_vec4 normal, const t_vec4 new_normal)
{
	t_vec4 r = normalize((t_vec4)(normal.x, normal.y - 0.0001f, normal.z - 0.0002f, 0.0f));
	const t_vec4 w = normalize(cross(normal, r));
	r = normalize(cross(w, normal));
	const t_mat4x4 basis = (t_mat4x4)(
		r.x, w.x, normal.x, 0.0f,
		r.y, w.y, normal.y, 0.0f,
		r.z, w.z, normal.z, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	);
	return (mat4x4_mult_vec4(basis, new_normal));
}
