/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 11:41:48 by wjun-kea          #+#    #+#             */
/*   Updated: 2025/07/16 06:32:25 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <stdbool.h>
# include "get_next_line/get_next_line.h"
# include "ft_fprintf/ft_fprintf.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
size_t		ft_strlen(const char *str);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t n);
int			ft_strlcpy(char *dst, const char *src, size_t size);
int			ft_strlcat(char *dst, const char *src, size_t dstsize);
int			ft_tolower(int c);
int			ft_toupper(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *str1, const char *str2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *str1, const void *str2, size_t n);
char		*ft_strnstr(const char *str1, const char *str2, size_t len);
int			ft_atoi(const char *nptr);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//extra

int			ft_isxdigit(int c);
char		*ft_strndup(const char *s, size_t n);
char		*ft_strncpy(char *dest, const char *src, size_t n);
long		ft_strtol(const char *str, char **endptr, int base);
void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);
char		*ft_strtok(char *str, const char *delim);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_isspace(int c);
char		*ft_strcat(char *dest, const char *src);
char		*ft_strstr(const char *haystack, const char *needle);
char		*ft_strcpy(char *dest, const char *src);
long long	ft_atoll(const char *nptr);
size_t		ft_arrlen(char **array);
size_t		ft_intarrlen(int *arr);
int			*ft_atoiarr_cln(char **temparr, int len);
int			*ft_atoiarr_errcln(char **temparr, int len);
long long	ft_atoierr(const char *str);
void		ft_free_2d(char **arr, size_t count);
void		ft_free_int_2d(int **arr, size_t count);
void		ft_safefree(void **ptr);

#endif
