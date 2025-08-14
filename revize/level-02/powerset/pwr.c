#include <stdio.h>
#include <stdlib.h>

/*
** Alt kümeyi ekrana yazdırır.
** Eğer size == 0 ise boş satır basar.
*/
static void print_subset(int *subset, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (i > 0)
            printf(" ");
        printf("%d", subset[i]);
    }
    printf("\n");
}

/*
** Rekürsif olarak alt kümeleri oluşturur.
** - target: hedef toplam
** - set: ana küme
** - size: ana kümenin boyutu
** - subset: alt küme için geçici dizi
** - index: subset'in şu anki uzunluğu
** - pos: set'teki şu anki pozisyon
** - sum: alt kümenin şu anki toplamı
*/
static void find_subsets(int target, int *set, int size,
                         int *subset, int index, int pos, int sum)
{
    // Bütün elemanlar kontrol edildi
    if (pos == size)
    {
        if (sum == target)
            print_subset(subset, index);
        return;
    }
    // Elemanı dahil et
    subset[index] = set[pos];
    find_subsets(target, set, size, subset, index + 1, pos + 1, sum + set[pos]);
    // Elemanı dahil etme
    find_subsets(target, set, size, subset, index, pos + 1, sum);
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return (0); // Eksik argüman

    int target = atoi(argv[1]);
    int size = argc - 2;

    // Bellek ayırma
    int *set = NULL;
    int *subset = NULL;
    if (size > 0)
    {
        set = malloc(sizeof(int) * size);
        subset = malloc(sizeof(int) * size);
        if (!set || !subset)
        {
            free(set);
            free(subset);
            return (1); // malloc hatası
        }
        for (int i = 0; i < size; i++)
            set[i] = atoi(argv[i + 2]);
    }

    // Alt kümeleri bul
    find_subsets(target, set, size, subset, 0, 0, 0);

    free(set);
    free(subset);
    return (0);
}
