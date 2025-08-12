#include <unistd.h>

// İki karakterin yerini değiştiren fonksiyon
void swap(char *x, char *y)
{
    char temp = *x;
    *x = *y;
    *y = temp;
}

// String'i alfabetik olarak sıralar (basit bubble/selection mantığı)
void sort_string(char *str)
{
    int i = 0;
    int j;

    while (str[i])
    {
        j = i + 1;
        while (str[j])
        {
            if (str[i] > str[j])
                swap(&str[i], &str[j]);
            j++;
        }
        i++;
    }
}

// String'in uzunluğunu döndürür
int str_length(char *str)
{
    int len = 0;
    while (str[len])
        len++;
    return len;
}

// Permütasyonları üreten fonksiyon (recursive)
void permute(char *str, int start)
{
    // Eğer sona geldiysek, string'i yazdır
    if (!str[start])
    {
        write(1, str, str_length(str));
        write(1, "\n", 1);
        return;
    }

    for (int i = start; str[i]; i++)
    {
        // start ile i yer değiştir
        swap(&str[start], &str[i]);

        // Sonraki harfler için aynı işlemi uygula
        permute(str, start + 1);

        // Geri al (orijinal haline dön)
        swap(&str[start], &str[i]);
    }
}

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        sort_string(argv[1]); // Önce harfleri sırala
        permute(argv[1], 0); // Permütasyonları üret
    }
    return 0;
}
