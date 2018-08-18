/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define EQN_EPS		1.0E-30
#define IsZero(x)	((x) > -EQN_EPS && (x) < EQN_EPS)

t_vec3	mat4x4_mult_vec3(const t_mat4x4 mat, const t_vec3 vec)
{
	t_vec3	res;
	res.x = mat.s0 * vec.x + mat.s1 * vec.y + mat.s2 * vec.z;
	res.y = mat.s4 * vec.x + mat.s5 * vec.y + mat.s6 * vec.z;
	res.z = mat.s8 * vec.x + mat.s9 * vec.y + mat.sa * vec.z;
	return (res);
}

t_vec4	mat4x4_mult_vec4(const t_mat4x4 mat, const t_vec4 vec)
{
	t_vec4	res;
	res.x = mat.s0 * vec.x + mat.s1 * vec.y + mat.s2 * vec.z + mat.s3 * vec.w;
	res.y = mat.s4 * vec.x + mat.s5 * vec.y + mat.s6 * vec.z + mat.s7 * vec.w;
	res.z = mat.s8 * vec.x + mat.s9 * vec.y + mat.sa * vec.z + mat.sb * vec.w;
	res.w = mat.sc * vec.x + mat.sd * vec.y + mat.se * vec.z + mat.sf * vec.w;
	return (res);
}

t_vec3	reflect3(const t_vec3 incident, const t_vec3 normal)
{
	return (reflect4((t_vec4){incident, 0.0f}, (t_vec4){normal, 0.0f}).xyz);
}

t_vec4	reflect4(const t_vec4 incident, const t_vec4 normal)
{
	return (normalize(incident - (normal * (2.0f * dot(incident, normal)))));
}

t_vec3	refract3(t_vec3 incident, t_vec3 normal, t_scalar ior)
{
	return (refract4((t_vec4){incident, 0.0f}, (t_vec4){normal, 0.0f}, ior).xyz);
}

t_vec4	refract4(t_vec4 incident, t_vec4 normal, t_scalar ior)
{
	t_scalar	cosi = dot(incident, normal);
	t_scalar	snell;
	if (cosi < 0)
	{
		cosi = -cosi;
		snell = 1.0f / ior; // here 1.0f is ior of vacuum
	}
	else
	{
		normal = -normal;
		snell = ior;
	}
	t_scalar	k = 1 - snell * snell * (1 - cosi * cosi); 
	return (normalize(k < 0 ? 0 : snell * incident + (snell * cosi - sqrt(k)) * normal));
}

t_scalar	fresnel(const t_vec4 *incident, const t_vec4 *normal, const t_scalar ior)
{
	t_scalar	cosi = dot(*incident, *normal);
	t_scalar	etai = 1.0f;
	t_scalar	etat = ior;
	if (cosi > 0)
	{
		t_scalar	temp;

		temp = etai;
		etai = etat;
		etat = temp;
	}
	// Compute sini using Snell's law
	const t_scalar	dc = 1 - cosi * cosi;
	const t_scalar	sint = etai / etat * sqrt(dc < 0.0f ? 0.0f : dc);
	// Total internal reflection
	if (sint >= 1) {
		return (1.0f);
	}
	const t_scalar	ds = 1 - sint * sint;
	t_scalar cost = sqrt(ds < 0.0f ? 0.0f : ds);
	cosi = fabs(cosi); 
	const t_scalar Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost)); 
	const t_scalar Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost)); 
	return (1.0f - (Rs * Rs + Rp * Rp) / 2.0f);
}

typedef	struct			s_equation
{
	bool				flag;
	float				aa;
	float				pp;
	float				rr;
	float				q2;
	float				c;
	float				b;
	float				br;
	float				discr;
	float				real1;
	float				real2;
	float				im1;
	float				im2;
	float2				l;
}						t_equation;

static void sort(float3 *ua, float2 *l)
{
	if (fabs((*ua)[0]) > fabs((*ua)[1]) && fabs((*ua)[0]) > fabs((*ua)[2]))
	{
		(*l)[0] = (*ua)[0];
		(*l)[1] = fabs((*ua)[1]) > fabs((*ua)[2]) ? (*ua)[1] : (*ua)[2];
	}
	else if (fabs((*ua)[1]) > fabs((*ua)[0]) && fabs((*ua)[1]) > fabs((*ua)[2]))
	{
		(*l)[0] = (*ua)[1];
		(*l)[1] = fabs((*ua)[0]) > fabs((*ua)[2]) ? (*ua)[0] : (*ua)[2];
	}
	else
	{
		(*l)[0] = (*ua)[2];
		(*l)[1] = fabs((*ua)[0]) > fabs((*ua)[1]) ? (*ua)[0] : (*ua)[1];
	}
}

static void negative_discr_solution(t_equation *e)
{
	float		n;
	float		bq3;
	float		beta;
	float		a3;
	float3 	ua;

	n = sqrt(e->b);
	bq3 = n * n * n;
	beta = (e->br / bq3 < 1.0f) ? acos(e->br / bq3) : 0.0f;
	a3 = -2.0f * n;
	ua[0] = a3 * cos(beta / 3.0f) - e->c / 3.0f;
	ua[1] = a3 * cos((beta + 2.0f * M_PI) / 3.0f) - e->c / 3.0f;
	ua[2] = a3 * cos((beta - 2.0f * M_PI) / 3.0f) - e->c / 3.0f;
	e->flag = false;
	sort(&ua, &(e->l));
	if (e->l[0] >= 0.0f)
	{
		e->real1 = sqrt(e->l[0]);
		e->im1 = 0.0f;
	}
	else
	{
		e->im1 = sqrt(-e->l[0]);
		e->real1 = 0.0f;
	}
	if (e->l[1] >= 0.0f)
	{
		e->im2 = 0.0f;
		e->real2 = sqrt(e->l[1]);
	}
	else
	{
		e->real2 = 0.0f;
		e->im2 = sqrt(-e->l[1]);
	}
}
 static void positive_discr_solution(t_equation *e)
{
	t_scalar	n;
	t_scalar	a3;
	t_vec3		ua;
	t_scalar	n2;
	t_scalar	u2;

 	n = (e->br < 0.0f) ? -1.0f : 1.0f;
	a3 = -n * cbrt(fabs(e->br) + sqrt(e->discr));
	ua[0] = a3 + e->b / a3 - e->c / 3.0f;
	ua[1] = -0.5f * ((a3 * a3 + e->b) / a3) - e->c / 3.0f;
	ua[2] = -(sqrt(3.0f) / 2.0f) * fabs(a3 - (e->b / a3));
	e->flag = true;
	n2 = sqrt(sqrt(ua[1] * ua[1] + ua[2] * ua[2]));
	u2 = atan2(ua[2], ua[1]);
	e->real1 = n2 * cos(u2 * 0.5f);
	e->im1 = n2 * sin(u2 * 0.5f);
	e->real2 = e->real1;
	e->im2 = -e->im1;
}
 static int	fourth_degree_equation(t_scalar t[4], t_scalar a[4])
{
	t_scalar	res;
	t_scalar	im_re1;
	t_scalar	im_re2;
	t_scalar	komp;
	t_equation	e;

 	e.aa = a[0] * a[0];
	e.pp = a[1] - 0.375f * e.aa;
	e.rr = a[3] - 0.25f * (a[0] * a[2] - 0.25f * e.aa * (a[1] - 0.1875f * e.aa));
	e.q2 = a[2] - 0.5f * a[0] * (a[1] - 0.25f * e.aa);
	e.c = 0.5f * e.pp;
	e.aa = 0.25f * (0.25f * e.pp * e.pp - e.rr);
	e.b = e.c * e.c / 9.0f - e.aa / 3.0f;
	e.br = e.c * e.c * e.c / 27.0f - e.c * e.aa / 6.0f - (0.125f * e.q2 * 0.125f * e.q2) / 2.0f;
	e.discr = ((e.br * e.br) - (e.b * e.b * e.b));
	if (e.discr < 0.0f)
		negative_discr_solution(&e);
	else
		positive_discr_solution(&e);
	im_re1 = e.im1 * e.im1 + e.real1 * e.real1;
	im_re2 = e.im2 * e.im2 + e.real2 * e.real2;
	komp = e.im1 * e.im2 - e.real1 * e.real2;
	res = e.q2 * 0.125f * komp / im_re1 / im_re2;
	(t)[0] = e.real1 + e.real2 + res - a[0] * 0.25f;
	(t)[1] = -e.real1 - e.real2 + res - a[0] * 0.25f;
	(t)[2] = -e.real1 + e.real2 - res - a[0] * 0.25f;
	(t)[3] = e.real1 - e.real2 - res - a[0] * 0.25f;
	if (!e.flag && e.l[0] >= 0.0f && e.l[1] >= 0.0f)
		return (4);
	else if (!e.flag)
		return (0);
	else
		return (2);
}
