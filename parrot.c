# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

#define update() printf("\33[H\33[J")

int timer = 55000;

static int	ft_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static void	ft_fill(int len, int offset, int n, char *res)
{
	while (len > offset)
	{
		res[len - 1] = n % 10 + 48;
		n = n / 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;
	int		offset;

	len = ft_len(n);
	offset = 0;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	if (n == -2147483648)
	{
		res[0] = '-';
		res[1] = '2';
		n = 147483648;
		offset = 2;
	}
	if (n < 0)
	{
		res[0] = '-';
		offset = 1;
		n = -n;
	}
	ft_fill(len, offset, n, res);
	res[len] = '\0';
	return (res);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (str);
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (((s1[i] > '\0') && (s1[i] == s2[i])) && (i < n - 1))
		i++;
	return (((unsigned char) s1[i]) - ((unsigned char) s2[i]));
}

char	*ft_arraysrch(char **tab, char *str_to_find)
{
	int	i;

	i = -1;
	while (tab[++i])
	{
		if (!ft_strncmp(tab[i], str_to_find, ft_strlen(str_to_find)))
			return (tab[i]);
	}
	return ("");
}

void	*ft_memset(void *b, int c, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	str = b;
	while (i < len)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (b);
}


void	*ft_calloc(size_t count, size_t size)
{
	char	*x;

	x = malloc(size * count);
	if (!x)
		return (NULL);
	ft_memset(x, 0, count * size);
	return (x);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	int fd;
	int i = 0;
	int j = 0;
	char *frames[10];
	int colors[6] = {31,33,32,36,34,35};
	char *pwd;


	pwd = ft_arraysrch(env, "PWD=") + 4;
	while (i <= 9)
	{
		frames[i] = malloc(1000 * sizeof(char));
		fd = open(ft_strjoin(pwd, ft_strjoin("/frames/", ft_strjoin(ft_itoa(i),".txt"))), O_RDONLY, 0777);
		// fd = open(ft_strjoin("./frames/", ft_strjoin(ft_itoa(i),".txt")), O_RDONLY, 0777);
		read(fd, frames[i], 1000);
		i++;
	}
	i = 0;
	while(1)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGABRT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		usleep(timer);
		update();
		printf("\033[%dm%s\033[0m",colors[j], frames[i]);

		if(i == 9)
			i = 0;
		if(j == 7)
			j = 1;
		i++;
		j++;
	}}
