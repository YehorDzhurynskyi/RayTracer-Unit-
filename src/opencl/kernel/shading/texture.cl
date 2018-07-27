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
