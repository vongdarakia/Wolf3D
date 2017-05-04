/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 21:36:49 by avongdar          #+#    #+#             */
/*   Updated: 2016/12/03 21:36:52 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <wchar.h>

# define USI unsigned int
# define USC unsigned char
# define USS unsigned short
# define USL unsigned long
# define USLL unsigned long long

typedef struct	s_env {
	int		num_out;
	int		flag_space;
	int		flag_alt_form;
	int		flag_left_just;
	int		flag_signed;
	int		flag_leading_zeroes;
	int		f_width;
	int		has_prcsn;
	int		prcsn_len;
	char	*len_mod;
	char	spec;
	int		is_specifier_lowercase;
	int		base;
}				t_env;

typedef struct	s_printf_func {
	char	specifier;
	void	(*print_func)(t_env *e, va_list *valist);
}				t_printf_func;

int				set_env(t_env *e, const char *str, va_list *valist);
void			call_func(t_env *e, va_list *valist);

int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strndup(const char *str, int n);
size_t			ft_strlen(const char *s);
char			*ft_strrealloc(char *n_buff, int len, int additional);

void			ft_pfputnbr(intmax_t n, int base, int is_lower);
void			ft_pfputnbr_u(uintmax_t n, unsigned int base, int is_lower);
int				ft_numlen(intmax_t n, int base);
int				ft_numlen_u(uintmax_t n, unsigned int base, t_env *e);
int				ft_atoi(const char *str);
void			ft_put_leading_zeroes(int len);

void			ft_print_c(t_env *e, va_list *valist);
void			ft_print_s(t_env *e, va_list *valist);
void			ft_print_num_signed(t_env *e, va_list *valist);
void			ft_print_num_unsigned(t_env *e, va_list *valist);
void			ft_print_num_array(t_env *e, va_list *valist);
void			ft_print_num_base(t_env *e, va_list *valist);

int				is_unsigned(char spec);
int				is_signed(char spec);
int				is_flag(char spec);
int				is_len_mod(const char *str);
int				len_mod_order(const char *mod);

int				ft_printf(const char *str, ...);

#endif
