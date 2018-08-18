#include "ft_expansions.h"

//char 		*check_class(char *pattern)
//{
//	int 				i;
//	static const char	*class[] = {"[:alnum:]", "[:alpha:]", "[:ascii:]",
//							"[:blank:]","[:cntrl:]", "[:digit:]", "[:graph:]",
//							"[:lower:]", "[:print:]", "[:punct:]", "[:space:]",
//							"[:upper:]", "[:word:]", "[:xdigit:]", NULL};
//
//	i = -1;
//	while (class[++i])
//		if (ft_strnequ(class[i], pattern, ft_strlen(class[i])))
//			return (pattern + ft_strlen(class[i]) - 1);
//	return (0);
//}

char 		*check_class(char *pattern)
{
	char 	quote;

	while (*pattern)
	{
		if (*pattern == ':' && *(pattern + 1) == ']')
			return (*(pattern + 2) ? pattern + 1 : pattern);
		else if (*pattern == '\\')
			++pattern;
		else if (*pattern == '\'' || *pattern == '"')
		{
			quote = *pattern++;
			while (*pattern != quote)
				++pattern;
		}
		++pattern;
	}
	return (0);
}


static char	*check_brackets(char *pattern)
{
	char 	quote;
	char 	*tmp;

	pattern += *pattern == '^' || *pattern == '!' ? 1 : 0;
	pattern += *pattern == ']' ? 1 : 0;
	while (*pattern)
	{
		if (*pattern == ']')
			return (pattern);
		else if (*pattern == '[' && *(pattern + 1) == ':' &&
				(tmp = check_class(pattern)))
				pattern = tmp;
		else if (*pattern == '\\')
			++pattern;
		else if (*pattern == '\'' || *pattern == '"')
		{
			quote = *pattern++;
			while (*pattern != quote)
				++pattern;
		}
		++pattern;
	}
	return (0);
}

int 	check_class_vals(char *buf, char *buf_q, int *i, char c)
{
	int 						j;
	static const t_char_class	class[] = {{"[:alnum:]", ft_isalnum},
			{"[:alpha:]", ft_isalpha}, {"[:ascii:]", ft_isascii},
			{"[:blank:]", ft_isblank}, {"[:cntrl:]", ft_iscntrl},
			{"[:digit:]", ft_isdigit}, {"[:graph:]", ft_isgraph},
			{"[:lower:]", ft_islower}, {"[:print:]", ft_isprint},
			{"[:punct:]", ft_ispunct}, {"[:space:]", ft_iswhitespace},
			{"[:upper:]", ft_isupper}, {"[:word:]", ft_isword},
			{"[:xdigit:]", ft_isxdigit}, {NULL, NULL}};

	j = -1;
	while (class[++j].name)
		if (ft_strnequ(class[j].name, buf + *i, ft_strlen(class[j].name)) &&
			!ft_strnchr(buf_q + *i, 1, (int)ft_strlen(class[j].name)))
		{
			*i += ft_strlen(class[j].name) - 1;
			return (class[j].func(c));
		}
	return (0);
}

int 	check_vals(char *buf, char *buf_q, char *brackets_end, char *str)
{
	int		eq;
	int 	i;
	char 	j;

	eq = (*buf == '!' || *buf == '^') && !*buf_q ? 0 : 1;
	buf += eq ? 0 : 1;
	i = -1;
	while (buf[++i])
	{
		if (buf[i] == '[' && buf[i + 1] == ':' && !buf_q[i] && !buf_q[i + 1])
		{
			if (check_class_vals(buf, buf_q, &i, *str))
				return (eq ? ft_regex_str(brackets_end + 1, str + 1, 0) : 0);
		}
		else if (buf[i + 1] == '-' && buf[i + 2] && !buf_q[i + 1])
		{
			j = buf[i] - 1;
			i += 2;
			while (++j <= buf[i])
				if (j == *str)
					return (eq ? ft_regex_str(brackets_end + 1, str + 1, 0) : 0);
		}
		else if (buf[i] == *str)
			return (eq ? ft_regex_str(brackets_end + 1, str + 1, 0) : 0);
	}
	return (eq ? 0 : ft_regex_str(brackets_end + 1, str + 1, 0));
}

void	get_vals(char *pattern, char *buf, char *buf_q, char *brackets_end)
{
	char 	quote;
	int 	i;

	quote = 0;
	i = 0;
	while (pattern != brackets_end)
	{
		if (*pattern == '\\' && !quote && pattern++)
			buf_q[i] = 1;
		else if ((*pattern == '\'' || *pattern == '"') && !buf_q[i] && !quote)
			quote = *pattern++;
		else if ((*pattern == '\'' || *pattern == '"') && quote && !buf_q[i]
				&& pattern++)
			quote = 0;
		else
		{
			buf[i] = *pattern++;
			if (quote && !buf_q[i])
				buf_q[i] = 1;
			++i;
		}
	}
}

int			ft_regex_brackets(char *pattern, char *str, char q)
{
	char 	*brackets_end;
	char	buf[ft_strlen(pattern) + 1];
	char	buf_q[ft_strlen(pattern) + 1];


	if ((brackets_end = check_brackets(pattern)))
	{
		ft_bzero(buf, sizeof(buf));
		ft_bzero(buf_q, sizeof(buf));
		get_vals(pattern, buf, buf_q, brackets_end);
		return (check_vals(buf, buf_q, brackets_end, str));
	}
	else if (*(pattern + 1) != ']')
		return (0);
	else if (*pattern == *str)
		return (ft_regex_str(pattern + 1, str + 1, q));
	return (0);
}