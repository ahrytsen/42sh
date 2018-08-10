#include "twenty_one_sh.h"

char	*get_brace_seq(char **s, t_list **lst);
char	*put_str_to_buf(char *buf, int *i, char *s, char c);
char 	*put_backslash_to_buf(char *buf, int *i, char *s);
char 	*put_quote_content_to_buf(char *buf, int *i, char *s);

void		print_lst(t_list *lst)
{
	while (lst)
	{
		ft_printf("%s ", lst->content);
		lst = lst->next;
	}
	ft_printf("\n");
}

char 	*skip_quotes(char *s)
{
	char 	c;

	c = *s;
	while (*++s)
		if (*s == '\\')
			++s;
		else if (*s == c)
			break ;
	return (s);
}

char	*check_braces(char *s)
{
	while (*++s)
		if (*s == '\\')
			++s;
		else if (*s && ft_strchr("\"'`", *s))
			s = skip_quotes(s);
		else if (*s == '}')
			break ;
		else if (*s == '{')
			s = check_braces(s);
	return (s);
}

int		check_comma(char *s)
{
	int		comma;

	comma = 0;
	while (*++s)
		if (*s == ',')
			comma = 1;
		else if (*s == '\\')
			++s;
		else if (*s && ft_strchr("\"'`", *s))
			s = skip_quotes(s);
		else if (*s == '}')
			break ;
		else if (*s == '{')
			s = check_braces(s);
	return (comma);
}

void	del_node(void *content, size_t size)
{
	(void)size;
	free(content);
}

t_list	*expand_braces(char *s, int i, char *buf)
{
	t_list	*vals;
	t_list	*tmp;
	t_list	*ret;
	int 	j;

	ret = NULL;
	while (*s)
		if (*s == '\\')
			s = put_backslash_to_buf(buf, &i, s);
		else if (*s && ft_strchr("\"'`", *s))
			s = put_quote_content_to_buf(buf, &i, s);
		else if (*s == '{' && *check_braces(s) == '}')
		{
			vals = NULL;
			s = get_brace_seq(&s, &vals);
			if (!(tmp = vals))
			{
				buf[i++] = *s++;
				continue ;
			}
			while (vals->next)
			{
				j = i;
				put_str_to_buf(buf, &j, vals->content, 0);
				ft_lstadd_end(&ret, expand_braces(s, j, buf));
				ft_bzero(buf + i, ft_strlen(buf + i));
				vals = vals->next;
			}
			put_str_to_buf(buf, &i, vals->content, 0);
			ft_lstdel(&tmp, (void (*)(void *, size_t))free);
		}
		else
			buf[i++] = *s++;
	ft_lstpush_back(&ret, buf, i + 1);
	return (ret);
}

int 	main(int ac, char **av)
{
	if (!av[1])
	{
		char buf[500];
		//	char *s = "{1,I{30..45}P}";
//		char *s = "sadasd{+++++++,1,YY,2,ab,---}98098";
		char *s = "$(ls -l {lol,kek}){1..3}";
//		char *s = "{1,2,f{3,4,5{0..3},\\6}hy}";
		t_list *lst = NULL;
		ft_bzero(buf, 500);
//		expand_braces(s, 0, buf, &lst, 0);
//		print_lst(lst);
		print_lst((lst = expand_braces(s, 0, buf)));
		ft_lstdel(&lst, (void (*)(void *, size_t))free);
		system("leaks gsh");

	}
	else
	{
		char buf[ft_strlen(av[1]) + 1];
		ft_bzero(buf, ft_strlen(av[1]) + 1);
		print_lst(expand_braces(av[1], 0, buf));
	}
	return (0);
}
