#include "twenty_one_sh.h"

char 	*put_backslash_to_buf(char *buf, int *i, char *s)
{
	ft_strncpy(buf + *i, s, 2);
	*i += 2;
	return (s + 2);
}

char 	*put_quote_content_to_buf(char *buf, int *i, char *s)
{
	char 	quote;

	quote = *s;
	buf[(*i)++] = *s++;
	while (*s != quote)
		if (*s == '\\')
			s = put_backslash_to_buf(buf, i, s);
		else
			buf[(*i)++] = *s++;
	buf[(*i)++] = *s++;
	return (s);
}

char	*put_str_to_buf(char *buf, int *i, char *s)
{
	while (*s)
		buf[(*i)++] = *s++;
	return (s);
}