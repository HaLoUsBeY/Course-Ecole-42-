#include "bsq.h"

int en_kucuk(int a, int b, int c)
{
	if (b < a) a = b;
	if (c < a) a = c;
	return a;
}

/* satirlari ve dp'yi serbest birak, sonuc dondur */
int temizle(char **s, int n, int *dp, int sonuc)
{
	for (int i = 0; i < n; i++)
		free(s[i]);
	free(s);
	free(dp);
	return sonuc;
}

int bsq(FILE *f)
{
	int n;
	char bos, eng, dolu;
	char *line = NULL;
	size_t cap = 0;

	/* 1) ilk satir: "9 . o x" ve hemen ardindan '\n' */
	if (fscanf(f, "%d %c %c %c", &n, &bos, &eng, &dolu) != 4 || n <= 0
		|| bos == eng || bos == dolu || eng == dolu
		|| getline(&line, &cap, f) != 1)
	{
		free(line);
		return -1;
	}

	/* 2) n satiri oku, dogrula ('\n' ile bitmeli, ayni boy, sadece bos/eng) */
	char **s = calloc(n, sizeof(char *));
	int w = -1;
	for (int i = 0; i < n; i++)
	{
		int len = getline(&line, &cap, f);
		if (len <= 1 || line[len - 1] != '\n' || (w != -1 && len - 1 != w))
		{
			free(line);
			return temizle(s, n, NULL, -1);
		}
		w = len - 1;
		line[w] = '\0';
		for (int j = 0; j < w; j++)
			if (line[j] != bos && line[j] != eng)
			{
				free(line);
				return temizle(s, n, NULL, -1);
			}
		s[i] = line;
		line = NULL;
		cap = 0;
	}
	free(line);

	/* 3) dp: o hucrede biten en buyuk kare = min(sol, ust, sol-ust) + 1 */
	int *dp = malloc(sizeof(int) * n * w);
	int best = 0, bi = 0, bj = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < w; j++)
		{
			int k = i * w + j;
			if (s[i][j] == eng)
				dp[k] = 0;
			else if (i == 0 || j == 0)
				dp[k] = 1;
			else
				dp[k] = en_kucuk(dp[k - 1], dp[k - w], dp[k - w - 1]) + 1;
			if (dp[k] > best)      /* > : esitlikte ilk bulunan (ust, sonra sol) kalir */
			{
				best = dp[k];
				bi = i;
				bj = j;
			}
		}

	/* 4) kareyi doldur, yazdir */
	for (int i = bi - best + 1; i <= bi; i++)
		for (int j = bj - best + 1; j <= bj; j++)
			s[i][j] = dolu;
	for (int i = 0; i < n; i++)
		fprintf(stdout, "%s\n", s[i]);
	return temizle(s, n, dp, 0);
}

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		if (bsq(stdin) == -1)
			fprintf(stderr, "map error\n");
		return 0;
	}
	for (int i = 1; i < argc; i++)
	{
		FILE *f = fopen(argv[i], "r");
		if (!f || bsq(f) == -1)
			fprintf(stderr, "map error\n");
		if (f)
			fclose(f);
		if (i < argc - 1)
			fprintf(stdout, "\n");
	}
	return 0;
}
