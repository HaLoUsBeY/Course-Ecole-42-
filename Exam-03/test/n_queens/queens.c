#include <stdio.h>
#include <stdlib.h>

int *pos; // pos[x] = x sütunundaki vezirin satır (y) pozisyonu
int N;

int abs2(int n) { return n < 0 ? -n : n; }

// (y, x) pozisyonu güvenli mi kontrol et
int safe(int y, int x)
{
	for (int i = 0; i < x; i++)
		if (pos[i] == y || abs2(pos[i] - y) == abs2(i - x))
			return 0;
	return 1;
}

// Çözümü ekrana yazdır
void print_sol(void)
{
	for (int i = 0; i < N; i++)
		printf("%d%c", pos[i], (i == N - 1) ? '\n' : ' ');
}

// x sütunundan başlayarak çöz
void solve(int x)
{
	if (x == N) { print_sol(); return; }
	for (int y = 0; y < N; y++)
		if (safe(y, x))
		{
			pos[x] = y;
			solve(x + 1);
		}
}

int main(int ac, char **av)
{
	if (ac != 2) return 0;
	N = atoi(av[1]);
	if (N <= 3) return 0;
	pos = malloc(sizeof(int) * N);
	solve(0);
	free(pos);
}
