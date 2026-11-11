#include "life.h"

/* (x, y) tahtada ve canli mi? disari = olu */
int canli(char *t, int w, int h, int x, int y)
{
	if (x < 0 || y < 0 || x >= w || y >= h)
		return 0;
	return t[y * w + x];
}

int komsu(char *t, int w, int h, int x, int y)
{
	int n = 0;
	for (int dy = -1; dy <= 1; dy++)
		for (int dx = -1; dx <= 1; dx++)
			if (dx || dy)
				n += canli(t, w, h, x + dx, y + dy);
	return n;
}

int main(int argc, char **argv)
{
	if (argc != 4)
		return 1;
	int w = atoi(argv[1]);
	int h = atoi(argv[2]);
	int it = atoi(argv[3]);
	char *t = calloc(w * h, 1);
	char *y2 = calloc(w * h, 1);
	if (!t || !y2)
		return 1;

	/* 1) kalem: wasd hareket, x ciz/kaldir */
	int x = 0, y = 0, ciz = 0;
	char c;
	while (read(0, &c, 1) > 0)
	{
		if (c == 'w' && y > 0) y--;
		else if (c == 's' && y < h - 1) y++;
		else if (c == 'a' && x > 0) x--;
		else if (c == 'd' && x < w - 1) x++;
		else if (c == 'x') ciz = !ciz;
		if (ciz)
			t[y * w + x] = 1;
	}

	/* 2) simulasyon: yeni tahtayi y2'ye yaz, sonra yer degistir */
	while (it-- > 0)
	{
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
			{
				int n = komsu(t, w, h, j, i);
				y2[i * w + j] = (n == 3 || (n == 2 && t[i * w + j]));
			}
		char *tmp = t; t = y2; y2 = tmp;
	}

	/* 3) yazdir */
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
			putchar(t[i * w + j] ? 'O' : ' ');
		putchar('\n');
	}
	free(t);
	free(y2);
	return 0;
}
