/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <wjun-kea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:15:39 by wjun-kea          #+#    #+#             */
/*   Updated: 2025/06/27 22:28:15 by wjun-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <string.h>
# include "../libft.h"

typedef struct s_flags
{
	bool	left_align;
	bool	zero_padding;
	bool	plus_sign;
	bool	space_sign;
	bool	alternate_form;
	int		width;
	bool	has_precision;
	int		precision;
	int		fd;
}	t_flags;

int		ft_fprintf(int fd, const char *format, ...);
char	*ft_calloc_buffer(char *data, t_flags flags);
int		ft_printchar(int c, t_flags flags);
int		ft_printstr(const char *str, t_flags flags);
int		ft_printint(int num, t_flags flags);
int		ft_printhex(unsigned int num, t_flags flags);
int		ft_printupperhex(unsigned int num, t_flags flags);
int		ft_printvoid(void *ptr, t_flags flags);
int		ft_printpercent(t_flags flags);
int		ft_printunsigned(unsigned int num, t_flags flags);
void	ft_insert_into_buffer(char *buffer, const char *data, t_flags flags);
void	ft_adjust_flags(t_flags *flags);
void	ft_fill_buffer(char *buffer, char fill_char, int start, int end);
char	*ft_itoa_base(unsigned long value, const char *base);
#endif
