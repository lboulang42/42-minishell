/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:43:51 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/31 11:02:25 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define CALLOC_SIZE_MAX 18446744073709551615UL

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

# define BASE_XX "0123456789abcdef"
# define BASE_X "0123456789ABCDEF"

int					prntf_putchar(char c);
int					prntf_putstr(char *str);
int					prntf_putnbr(int nbr, int *count);
int					prntf_sort(char c, va_list *args);
int					prntf_printf(const char *format, ...);
int					prntf_putnbr_u(unsigned int nbr);
int					prntf_putnbr_base(unsigned int nbr, char *base);
int					prntf_putnbr_base_p(unsigned long int nbr, char *base);

void				ft_free_tab_size(void **tab, int size);

////////*ft_atoi_itoa.c*////////
int					counter(char *str, char c);

int					ft_atoi(const char *nptr);
char				*ft_itoa(int n);

////////ft_calloc.c////////

void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);

////////ft_isalnum.c////////

int					ft_isalnum(int c);
int					ft_islower(int c);
int					ft_isupper(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);

////////ft_isascii.c////////

int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);

////////ft_len.c////////

size_t				ft_strlen(const char *s);
int					ft_tab_len(char **tab);

////////ft_lst1.c////////

t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);

////////ft_lst2.c////////

void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

////////ft_mem.c////////

void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);

////////ft_put_fd.c////////

void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);

////////ft_put.c////////

int					ft_putchar(char c);
void				ft_putendl(char *s);
void				ft_putnbr(int n);
int					ft_putstr(char *s);

////////ft_split.c////////

char				**ft_split(char const *s, char c);

////////ft_str_operation.c////////

char				*ft_strdup(const char *s);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_substr(char const *s, unsigned int start, size_t len);

////////ft_strchr.c////////

char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);

////////ft_strl.c////////

size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);

////////ft_strn.c////////

char				*ft_strnstr(const char *big, const char *little,
						size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

////////ft_strtrim.c////////

char				*ft_strtrim(char const *s1, char const *set);

void				ft_free_tab(void **tab);

//printf//

int					prnft_ft_putstr(char *s);
int					prntf_nbr(long long int nbr, char *base, int count);
int					prntf_ptr(unsigned long long ptr);
int					prntf_parse(va_list va_ptr, const char flag, int tmp,
						int counter);
int					ft_printf(const char *arg0, ...);
int					prnft_ft_putstr(char *s);
#endif
