#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

/* FONKSİYONLARINIZ BURADAN BAŞLIYOR (fonksiyon imzaları verilmiş) */


/*
 * match_space: Girdi akışından başlangıçtaki boşluk karakterlerini tüketir.
 * @f: Okunacak dosya akışı (örn. stdin).
 * Döndürür: 0 başarıda (boşluk tüketildi veya boşluk bulunamadı),
 * -1 okuma sırasında EOF veya hata oluşursa.
 */
int match_space(FILE *f)
{
	int c; // fgetc() kullanarak okunan karakteri tutacak değişken
	while ((c = fgetc(f)) != EOF) // EOF'a kadar akıştan karakter oku
	{
		if (!isspace(c)) // Eğer boşluk karakteri değilse
		{
			ungetc(c, f); // Karakteri akışa geri koy
			return 0; // Başarıyla başlangıçtaki boşlukları tüketti (veya hiç bulamadı)
		}
	}
	if (ferror(f)) // döngü EOF nedeniyle sonlandı, okuma hatalarını kontrol et
		return -1;
	// Eğer sadece EOF varsa ve hata yoksa, mümkün olan tüm boşlukları başarıyla tükettik
	return (0);
}

/*
 * match_char: Girdi akışından tek bir karakter okur ve belirtilen
 * karakterle karşılaştırır.
 * @f: Okunacak dosya akışı.
 * @c: Eşleştirilecek karakter.
 * Döndürür: 1 karakter eşleşirse ve tüketilirse,
 * 0 karakter eşleşmezse (ve geri konursa),
 * -1 EOF veya hata oluşursa.
 */
int match_char(FILE *f, char c)
{
	int c_read = fgetc(f); // girdi akışından okunan karakter
	if (c_read == EOF) // eğer okunan karakter EOF ise
	{
		if (ferror(f)) // okuma hatalarını kontrol et
			return -1;
		return 0; // Eğer sadece EOF varsa ve hata yoksa, eşleşme bulunamadı
	}
	if (c_read == c)
		return 1; // eşleşme bulundu ve tüketildi
	else
	{
		ungetc(c_read, f); // karakteri dosya akışına geri koy
		return (0);  // eşleşme bulunamadı
	}
}

/*
 * scan_char: Girdi akışından tek bir karakter okur ve onu va_list
 * aracılığıyla sağlanan char pointer'a kaydeder.
 * Başlangıçtaki boşlukları atlamaz.
 * @f: Okunacak dosya akışı.
 * @ap: Argüman pointer'ını (char *) içeren va_list.
 * Döndürür: 1 başarılı tarama durumunda,
 * 0 hiç karakter okunamazsa (örn. hemen EOF),
 * -1 hata oluşursa.
 */
int scan_char(FILE *f, va_list ap)
{
	int c = fgetc(f); // bir karakter oku
	if (c == EOF)
	{
		if (ferror(f)) // okuma hatalarını kontrol et
			return -1;
		return 0; // Eğer sadece EOF varsa ve hata yoksa, okunacak karakter yok demektir
	}
	char *c_ptr = va_arg(ap, char *); // va_list'ten char* argümanını al
	*c_ptr = (char)c; // Karakteri kaydet
	return (1); // Başarıyla bir karakter tarandı
}

/*
 * scan_int: Girdi akışından bir tamsayı okur ve onu va_list
 * aracılığıyla sağlanan int pointer'a kaydeder.
 * Başlangıçtaki boşlukların zaten match_space tarafından işlendiğini varsayar.
 * @f: Okunacak dosya akışı.
 * @ap: Argüman pointer'ını (int *) içeren va_list.
 * Döndürür: 1 başarılı tarama durumunda,
 * 0 geçerli tamsayı okunamazsa (örn. rakam bulunamazsa),
 * -1 hata oluşursa.
 * NOT! Taşmaları işlemeye gerek yok çünkü orijinal scanf'in
 * taşma durumundaki davranışı tanımsızdır.
 */
int scan_int(FILE *f, va_list ap)
{
	int c = fgetc(f); // bir karakter oku

	// Adım 0: EOF ve okuma hatalarını kontrol et
	if (c == EOF)
	{
		if (ferror(f)) // okuma hatalarını kontrol et
			return -1;
		return 0; // Eğer sadece EOF varsa ve hata yoksa, okunacak karakter yok demektir
	}

	// Adım 1: işaret işleme
	// okunan karakterin '+'/'-' işaret karakteri olup olmadığını kontrol et
	int sign = 1; // pozitif olarak başlat
	if (c == '+' || c == '-')
	{
		if (c == '-') // sadece '-' ile karşılaştığında işareti değiştir
			sign = -1;
	}
	else
		ungetc(c, f); // İşaret değil, daha sonra rakam işleme için geri koy
	
	// Adım 2: rakam işleme
	int value = 0; 
	int digits_read = 0; // kaç rakam okunduğunu takip et
	while ((c = fgetc(f)) != EOF)
	{
		if (isdigit(c))
		{
			value = value * 10 + (c - '0');
			digits_read++;
		}
		else
		{
			ungetc(c, f); // rakam değil, geri koy
			break ; // okumayı durdur
		}
	}

	// döngü sona erdi, okuma hatası nedeniyle mi kontrol et
	if (ferror(f))
		return -1;

	if (digits_read == 0) // hiç rakam okunmadı mı kontrol et
		return 0;
	
	// Adım 3: dönüştürülmüş tamsayıyı kaydet
	int *num_ptr = va_arg(ap, int *); // int * argümanını al
	*num_ptr = value * sign; // Taranan tamsayıyı kaydet

	return (1); // Başarıyla bir tamsayı tarandı
}

int scan_string(FILE *f, va_list ap)
{
	int c = fgetc(f); // bir karakter oku

	// Adım 0: EOF ve okuma hatalarını kontrol et
	if (c == EOF)
	{
		if (ferror(f)) // okuma hatalarını kontrol et
			return -1;
		return 0; // Eğer sadece EOF varsa ve hata yoksa, okunacak karakter yok demektir
	}
	ungetc(c, f); // eğer EOF değilse, geri koy

	char *s = va_arg(ap, char *);
	int char_read = 0; // kaç karakter okunduğunu takip et
	while ((c = fgetc(f)) != EOF)
	{
		if (isspace(c))
		{
			ungetc(c, f);
			break ;
		}
		*s = (char)c;
		s++;
		char_read++;
	}
	if (ferror(f)) // okuma hatalarını kontrol et
		return -1;

	if (!char_read) // Hiç boşluk olmayan karakter okunmadı
		return 0;

	*s = '\0'; // string'i null ile sonlandır
	return (1); // Başarıyla bir string tarandı
}


/* FONKSİYONLARINIZ BURADA BİTİYOR */ 



/*
 * match_conv: Format belirleyicisine göre uygun tarama fonksiyonuna yönlendirir.
 * @f: Dosya akışı.
 * @format: Dönüşüm belirleyici karakteri ('c', 'd', 's').
 * @ap: va_list.
 * Döndürür: 1 başarılı dönüşümde,
 * 0 girdi dönüşümle eşleşmezse (örn. %d için rakam yoksa),
 * -1 tarama sırasında EOF veya hata oluşursa.
 */
int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

/*
 * ft_vfscanf: Format stringini ayrıştıran ve akıştan okuyan ana fonksiyon.
 * vfscanf'a benzer.
 * @f: Okunacak dosya akışı.
 * @format: Format stringi.
 * @ap: Argümanları içeren va_list.
 * Döndürür: Başarıyla eşleştirilen ve atanan girdi öğelerinin sayısı,
 * herhangi bir veri başarıyla okunmadan önce girdi hatası oluşursa EOF.
 */
int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	
	if (ferror(f))
		return EOF;
	return nconv;
}


/* AŞAĞIDAKİ FONKSİYONDA VA_LIST'İ TANIMLAMANIZ, BAŞLATMANIZ VE TEMİZLEMENİZ GEREKİYOR */


/*
 * ft_scanf: scanf davranışını taklit eder, stdin'den formatlanmış girdi okur.
 * @format: Format stringi.
 * @...: Format belirleyicilerine karşılık gelen değişken argümanlar.
 * Döndürür: Başarıyla eşleştirilen ve atanan girdi öğelerinin sayısı,
 * herhangi bir veri başarıyla okunmadan önce girdi hatası oluşursa EOF.
 */
int ft_scanf(const char *format, ...)
{
	va_list ap; // Bir va_list değişkeni tanımla
	va_start(ap, format); // va_list'i ilk değişken argümana işaret edecek şekilde başlat
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap); // va_list'i temizle
	return ret;
}

// main() fonksiyonu SADECE TEST İÇİN!!! 

// int main()
// {
// 	int number;
// 	char character;
// 	char string[500];
// 	// ft_scanf("%d", &number);
// 	// ft_scanf("%c", &character);
// 	// ft_scanf("%s", &string);
// 	ft_scanf("%d %c %s", &number, &character, &string);
// 	printf("girdiğiniz sayı: %d\n", number);
// 	printf("girdiğiniz karakter: %c\n", character);
// 	printf("girdiğiniz string: %s\n", string);
// 	return 0;
// }

int main (void)
{
	int a;
	char c;
	char s[100]; // ✅ String için bellek ayır!

	printf("Girdi formatı: sayı, karakter, string (örn: 42, A, merhaba)\n");
	printf("Giriş: ");
	
	int result = ft_scanf("%d, %c, %s", &a, &c, s); // ✅ s, &s değil!
	
	printf("Okunan değe sayısı: %d\n", result);
	printf("Sayı: %d\n", a);
	printf("Karakter: %c\n", c);
	printf("String: %s\n", s);

	return 0;
}