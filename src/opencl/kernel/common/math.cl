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
	return (k < 0 ? 0 : snell * incident + (snell * cosi - sqrt(k)) * normal);
}

int		solve_quadric(t_scalar c[3], t_scalar s[2])
{
	t_scalar p, q, D;
	/* normal form: x^2 + px + q = 0 */
	p = c[1] / (2 * c[2]);
	q = c[0] / c[2];
	D = p * p - q;
	if (IsZero(D))
	{
		s[0] = -p;
		return 1;
	}
	else if (D < 0)
		return 0;
	else
	{
		const t_scalar sqrt_D = sqrt(D);
		s[0] = sqrt_D - p;
		s[1] = -sqrt_D - p;
		return 2;
	}
}

int		solve_cubic(t_scalar c[4], t_scalar s[3])
{
	int			i, num;
	t_scalar	sub;
	t_scalar	A, B, C;
	t_scalar	sq_A, p, q;
	t_scalar	cb_p, D;

	/* normal form: x^3 + Ax^2 + Bx + C = 0 */

	A = c[2] / c[3];
	B = c[1] / c[3];
	C = c[0] / c[3];

	/*  substitute x = y - A/3 to eliminate quadric term:
	x^3 +px + q = 0 */

	sq_A = A * A;
	p = 1.0f / 3.0f * (- 1.0f / 3.0f * sq_A + B);
	q = 1.0f / 2.0f * (2.0f / 27.0f * A * sq_A - 1.0f / 3.0f * A * B + C);

	/* use Cardano's formula */

	cb_p = p * p * p;
	D = q * q + cb_p;

	if (IsZero(D))
	{
		if (IsZero(q)) /* one triple solution */
		{
			s[0] = 0;
			num = 1;
		}
		else /* one single and one t_scalar solution */
		{
			t_scalar u = cbrt(-q);
			s[0] = 2.0f * u;
			s[1] = -u;
			num = 2;
		}
	}
	else if (D < 0) /* Casus irreducibilis: three real solutions */
	{
		const t_scalar phi = 1.0f / 3.0f * acos(-q / sqrt(-cb_p));
		const t_scalar t = 2.0f * sqrt(-p);

		s[0] = t * cos(phi);
		s[1] = -t * cos(phi + M_PI / 3.0f);
		s[2] = -t * cos(phi - M_PI / 3.0f);
		num = 3;
	}
	else /* one real solution */
	{
		const t_scalar sqrt_D = sqrt(D);
		const t_scalar u = cbrt(sqrt_D - q);
		const t_scalar v = - cbrt(sqrt_D + q);

		s[0] = u + v;
		num = 1;
	}

	/* resubstitute */

	sub = 1.0f / 3.0f * A;

	for (i = 0; i < num; ++i)
		s[i] -= sub;
	return num;
}

int		solve_quartic(t_scalar c[5], t_scalar s[4])
{
	t_scalar	coeffs[ 4 ];
	t_scalar	z, u, v, sub;
	t_scalar	A, B, C, D;
	t_scalar	sq_A, p, q, r;
	int			i, num;

	/* normal form: x^4 + Ax^3 + Bx^2 + Cx + D = 0 */

	A = c[3] / c[4];
	B = c[2] / c[4];
	C = c[1] / c[4];
	D = c[0] / c[4];

	/*  substitute x = y - A/4 to eliminate cubic term:
	x^4 + px^2 + qx + r = 0 */

	sq_A = A * A;
	p = -3.0f / 8.0f * sq_A + B;
	q = 1.0f / 8.0f * sq_A * A - 1.0f / 2.0f * A * B + C;
	r = - 3.0f / 256.0f * sq_A * sq_A + 1.0f / 16.0f * sq_A * B - 1.0f / 4.0f * A * C + D;

	if (IsZero(r))
	{
	/* no absolute term: y(y^3 + py + q) = 0 */

		coeffs[0] = q;
		coeffs[1] = p;
		coeffs[2] = 0;
		coeffs[3] = 1;

		num = solve_cubic(coeffs, s);

		s[num++] = 0;
	}
	else
	{
		/* solve the resolvent cubic ... */

		coeffs[0] = 1.0f / 2.0f * r * p - 1.0f / 8.0f * q * q;
		coeffs[1] = -r;
		coeffs[2] = -1.0f / 2.0f * p;
		coeffs[3] = 1.0f;

		(void) solve_cubic(coeffs, s);

		/* ... and take the one real solution ... */

		z = s[0];

		/* ... to build two quadric equations */

		u = z * z - r;
		v = 2.0f * z - p;

		if (IsZero(u))
			u = 0.0f;
		else if (u > 0.0f)
			u = sqrt(u);
		else
			return 0;

		if (IsZero(v))
			v = 0.0f;
		else if (v > 0.0f)
			v = sqrt(v);
		else
			return 0;

		coeffs[0] = z - u;
		coeffs[1] = q < 0.0f ? -v : v;
		coeffs[2] = 1.0f;

		num = solve_quadric(coeffs, s);

		coeffs[0]= z + u;
		coeffs[1] = q < 0.0f ? v : -v;
		coeffs[2] = 1.0f;

		num += solve_quadric(coeffs, s + num);
	}

	/* resubstitute */

	sub = 1.0f / 4.0f * A;

	for (i = 0; i < num; ++i)
		s[i] -= sub;
	return num;
}
