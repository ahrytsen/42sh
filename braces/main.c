#include <stdbool.h>
#include "twenty_one_sh.h"

t_list		*regex(char *pattern);

void		print_lst(t_list *lst)
{
	while (lst)
	{
		ft_printf("%s\n", lst->content);
		lst = lst->next;
	}
}

//char 	*strchr_unquoted()

char 	*skip_quotes(char *s)
{
	char 	c;

	c = *s;
	while (++*s)
		if (*s == '\\')
			++s;
		else if (*s == c)
			return (s);
}

bool	check_braces(char *braces)
{
//	while ()
	return (1);
}

t_list	*get_brace_seq(char *s)
{
	char 	**vals;
	t_list	*vals_lst;

	vals_lst = NULL;
	vals = ft_strsplit(s, ',');
	while (*vals)
	{
		ft_lstpush_back(&vals_lst, *vals, ft_strlen(*vals) + 1);
		++vals;
	}
	return (vals_lst);
}

t_list	*expand_braces(t_list *toks, char *braces)
{

}

int 	main(int ac, char **av)
{
	int 	i;
	int 	j;
	t_list	*toks = ft_lstnew("{1,2}{3,4}", ft_strlen("{1,2}{3,4}"));

	print_lst(toks);
	ft_printf("\n---------------------------\n\n");
	while (*(char *)(toks->content))
	{
		if (*toks->content == '{')

	}



}