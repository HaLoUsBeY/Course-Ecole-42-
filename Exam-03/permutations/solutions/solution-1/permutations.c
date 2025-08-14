#include <unistd.h>
#include <stdlib.h>

int ft_strlen(char *s) {
    int i = 0;
    while (s[i])
        i++;
    return i;
}

void ft_strcpy(char *dst, char *src) {
    int i = 0;
    while (src[i]) {
        dst[i] = src[i];
        i++;
    }
    dst[i] = 0;
}

void ft_sort(char *t, int s) {
    int i = 0;
    while (i < s - 1) {
        int j = 0;
        while (j < s - i - 1) {
            if (t[j] > t[j + 1]) {
                char tmp = t[j];
                t[j] = t[j + 1];
                t[j + 1] = tmp;
            }
            j++;
        }
        i++;
    }
}

void ft_solve(char *t, char *t2, int *used, int s, int x) {
    if (x == s) {
        write(1, t2, s);
        write(1, "\n", 1);
        return;
    }
    int i = 0;
    while (i < s) {
        if (!used[i]) {
            used[i] = 1;
            t2[x] = t[i];
            ft_solve(t, t2, used, s, x + 1);
            used[i] = 0;
        }
        i++;
    }
}

int main(int ac, char **ar) {
    if (ac != 2)
        return 1;
    int s = ft_strlen(ar[1]);
    if (s == 0)
        return 0;
    char *t = malloc(s + 1);
    char *t2 = malloc(s + 1);
    int *used = calloc(s, sizeof(int));
    if (!t || !t2 || !used)
        return 1;
    ft_strcpy(t, ar[1]);
    ft_sort(t, s);
    ft_solve(t, t2, used, s, 0);
    free(t);
    free(t2);
    free(used);
    return 0;
}