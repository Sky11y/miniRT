#include "mini_rt.h"
#include "scene_elements.h"

char	*wrap_join(char *s1, char *s2)
{
	char	*string;

	if (!s1 || !s2)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	string = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (!string)
		return (NULL);
	return (string);
}

bool	line_first(char *line, char *value, int len)
{
	int	i;

	i = 0;
	while (ft_iswhitespace(line[i]) && line[i] != '\n')
		i++;
	if (line[i] == '\n' && value[0] == '\n')
		return (true);
	if (!ft_strncmp(&line[i], value, len) && ft_iswhitespace(line[i + len]))
		return (true);
	return (false);
}

int	print_error(char *error_msg)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(error_msg, 2);
	return (1);
}
