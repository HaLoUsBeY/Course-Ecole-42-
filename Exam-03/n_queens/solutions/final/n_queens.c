#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int *board;         // board[col] = col sütunundaki vezirin satır pozisyonu
int board_size;     // tahtanın boyutu (n)

// Mevcut çözümü yazdır
void print_solution(void)
{
    int i;
    
    for (i = 0; i < board_size; i++)
    {
        // i sütunundaki vezirin satır pozisyonunu yazdır
        fprintf(stdout, "%d", board[i]);
        
        // Sayılar arasına boşluk ekle, sonuncudan sonra hariç
        if (i < board_size - 1)
            fprintf(stdout, " ");
    }
    fprintf(stdout, "\n");
}

// orijinal abs() fonksiyonuna izin verilmediği için yerine geçen fonksiyon
int ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return n;
}

// Bir veziri (row, col) pozisyonuna yerleştirmenin güvenli olup olmadığını kontrol et
int is_safe(int row, int col)
{
	// Daha önce yerleştirilen tüm vezirleri kontrol et (0'dan col-1'e kadar sütunlar)
	// i: sütun iteratörü
	for (int i = 0; i < col; i++)
	{
		if (board[i] == row) // vezirler aynı satırda mı kontrol et
			return 0;
		
		// Çapraz saldırıları kontrol et
        // Eğer satır farkı sütun farkına eşitse,
        // aynı çapraz üzerindedirler
		if (ft_abs(board[i] - row) == ft_abs(i - col))
			return 0;
	}
	return 1;
}

void solve(int col)
{
	// temel durum kontrolü: eğer tüm sütunlara vezir yerleştirdiysek
	if (col == board_size)
	{
		print_solution();
		return ;
	}
	// Mevcut sütunun her satırına vezir yerleştirmeyi dene
	for (int row = 0; row < board_size; row++)
	{
		// Mevcut sütunun her satırına vezir yerleştirmeyi dene
		if (is_safe(row, col))
		{
			// Veziri bu pozisyona yerleştir
			board[col] = row;
			// Sonraki sütun için rekürsif olarak çöz
			solve(col + 1);
			// Geri izleme (veziri kaldır) - bir sonraki iterasyonda üzerine yazdığımız
            // için ya da fonksiyon döndüğünde dolaylı olarak gerçekleşir
		}
	}
}

int main(int ac, char **av)
{
	// yanlış argc durumunu işle
	if (ac != 2)
	{
		write(1, "\n", 1);
		return 0;
	}
	int n = atoi(av[1]);
	// geçersiz girdileri işle: negatif sayılar, çözülemeyen boyutlar
	if (n <= 3)
	{
		write(1, "\n", 1);
		return 0;
	}
	board_size = n; // global değişkeni ayarla
	board = malloc(sizeof(int) * board_size);
	if (!board)
		return 1;
	// 0. sütundan çözmeye başla
	solve(0);
	free(board);
	return 0;
}