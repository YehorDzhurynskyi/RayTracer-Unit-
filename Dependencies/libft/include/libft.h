/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 17:03:18 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/27 14:17:58 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>

typedef unsigned char	t_byte;

typedef int				t_bool;

# define TRUE 1
# define FALSE 0

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

/*
**PART1
*/

void				*ft_memset(void	*b, int c, size_t len);
void				ft_bzero(void *b, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strnchr(const char *s, int c, int n);
char				*ft_strchrn(const char *s, int c, int n);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strnstr(const char *big, const char *little, size_t l);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *s);
double				ft_atod(const char *s);
unsigned int		ft_hex_atoui(const char *s);
char				*ft_hex_uitoa(unsigned int n,
		t_bool append_prefix, t_bool uppercase);
char				*ft_hex_ulltoa(unsigned long long n,
		t_bool append_prefix, t_bool uppercase);
char				*ft_octal_uitoa(unsigned int n, t_bool append_prefix);
char				*ft_octal_ulltoa(unsigned long long n,
		t_bool append_prefix);
char				*ft_uitoa(unsigned int n);
char				*ft_ulltoa(unsigned long long n);
char				*ft_lltoa(long long n);
char				*ft_ldtoa(long double n, unsigned precision);
char				*ft_binary_ulltoa(unsigned long long n);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_ishex(int c);
int					ft_isws(char c);
int					ft_toupper(int c);
int					ft_tolower(int c);

/*
** PART2
*/

void				ft_iswap(int *a, int *b);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_itoa_cat(char *dest, size_t size, int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
int					get_next_line(int fd, char **line);
int					ft_printf(const char *format, ...);
int					ft_printf_fd(int fd, const char *format, ...);

/*
**BONUS
*/

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *));

/*
**EXTRA
*/

char				*ft_str_format(const char *format, ...);
void				*ft_lstreduce(t_list *lst, void *(*f)
		(const void *, const void *));
void				ft_strreplallchr(char *src, char from, char to);
char				*ft_strreplallstr(char const *s, char const *from,
		char const *to);
int					mini(int *arr, size_t size);
int					maxi(int *arr, size_t size);
float				minf(float *arr, size_t size);
float				maxf(float *arr, size_t size);
float				minf_filter(float *arr, size_t size,
		t_bool (*filter)(float v, unsigned int idx));
float				maxf_filter(float *arr, size_t size,
		t_bool (*filter)(float v, unsigned int idx));
size_t				ft_count_num_length(unsigned long long n, unsigned base);

#endif
