# CPP07 — Şablonlar (templates) çalışma notları

**Genel fikir:** Şablon, tipi parametre olan bir kod kalıbıdır. Derleyici şablonu
kullandığın her tip için gerçek kodu kendisi üretir (*instantiation / örnekleme*).
Bunun için şablonun **gövdesini görmesi** gerekir. O yüzden gövde header'da (ya da
header'ın sonunda include edilen `.tpp`'de) durur. Subject'teki "header'da gövde
yasak" kuralının istisnası budur.

Derleme/test (her klasörde): `make && ./whatever` (ex00), `./iter` (ex01), `./array` (ex02);
sızıntı kontrolü: `valgrind --leak-check=full ./array`.

---

## ex00 — swap / min / max (`whatever.hpp`)

`swap`, `min` ve `max` global namespace'te duran şablon fonksiyonlar. `min`/`max`
`const T &` alır ve `const T &` döndürür. `a < b` (max'te `a > b`) doğru değilse `b`
döner, yani değerler eşitse **ikinci** parametre döner. main'de eşitlik durumu
adreslerle gösteriliyor (`&::min(x, y) == &y`).

**Kavramlar:** `template <typename T>`, tip çıkarımı (deduction), açık tip argümanı
(`::max<float>(...)`), iki argümanın aynı tipte olması zorunlu.

**Olası sorular**
1. *Neden `::swap` diye çağrılıyor?* → Global namespace'teki bizim şablonumuz çağrılsın
   diye. `std::string` argümanlarında ADL, `std::swap`/`std::min`'i de aday yapar.
   Denendi: `min(c, d)` "ambiguous" hatası veriyor, `swap(c, d)` ise sessizce
   `std::swap`'i çağırıyor.
2. *`::max(1, 2.5)` derlenir mi?* → Hayır. T bir yerde `int`, diğer yerde `double`
   çıkıyor. `::max<double>(1, 2.5)` yazarsan derlenir.
3. *Neden const referans?* → Kopya yok (büyük tiplerde ucuz) ve geçici değerler
   (`::min(3, 4)`) de bağlanabiliyor.
4. *T'nin hangi özellikleri olmalı?* → swap için kopyalanabilir ve atanabilir olmalı,
   min/max için `<` ve `>` tanımlı olmalı.
5. *Gövde header'da, bu kurala aykırı değil mi?* → Fonksiyon şablonları istisna.
   Derleyici örneklemek için gövdeyi görmeli.

---

## ex01 — iter (`iter.hpp`)

`iter(array, length, func)` dizinin her elemanında `func(array[i])`'yi çağırır. İki
overload var: `T *` değiştirilebilir diziler için, `const T *` const diziler için. `F`
ayrı bir şablon parametresi olduğundan normal fonksiyon, `print<int>` gibi bir şablon
örneği ya da değerle alan bir fonksiyon verilebilir.

**Kavramlar:** `print<int>` = `print` şablonunun `int` için örneklenmiş hali (tek,
somut bir fonksiyon). Bu yüzden `F` çıkarılabilir. Overload seçimi şöyle işler:
const olmayan dizi → `T *` sürümü seçilir (tam eşleşme). const dizi → `const T *`
sürümü seçilir (daha özel şablon). Aslında tek `T *` sürümü de yeterdi (T = `const int`
çıkarılır). İkinci sürüm niyeti açıkça gösteriyor.

**Olası sorular**
1. *const diziye değiştiren fonksiyon (`increment<int>`) verirsen?* → Derleme hatası
   alırsın: `const int`, `int &`'e bağlanamaz. main'de yorum satırı olarak duruyor.
2. *Neden `print` değil de `print<int>`?* → `print` bir şablon. Hangi örneğin
   geçirileceği belli değilse `F` çıkarılamaz ve kod derlenmez.
3. *Uzunluk neden `const size_t`?* → Subject "const değer" istiyor. `size_t` negatif
   olamayan, boyut için kullanılan doğal tip.
4. *Fonksiyon `const T &` mi `T &` mi almalı?* → İkisi de çalışır. Okuyan fonksiyon
   (print) `const T &` alır, değiştiren fonksiyon (increment) `T &` alır.
5. *Functor (operator() olan nesne) verilebilir mi?* → Evet. `func(array[i])`
   yazılabildiği sürece `F` her şey olabilir.
6. *length 0 olursa?* → Döngü hiç dönmez, fonksiyon hiç çağrılmaz.

---

## ex02 — Array<T> (`Array.hpp` + `Array.tpp`)

Sınıf şablonu iki üye tutar: `data_` (`new[]` ile ayrılır) ve `size_`. Boş kurucu
`data_ = NULL`, `size_ = 0` yapar. `Array(n)` kurucusu `new T[n]()` kullanır: sondaki
`()` her elemanı varsayılan değerle başlatır (`int` → 0, `string` → ""). Kopya kurucu
ve atama operatörü **derin kopya** yapar: yeni bellek ayırıp elemanları tek tek
kopyalar. `operator[]` sınır dışında `OutOfBoundsException` atar. Bu sınıf
`std::exception`'dan türeyen iç içe bir sınıftır ve `what()`'ı override eder.

**Kavramlar:** OCF (4 fonksiyon), derin ve sığ kopya, self-assignment kontrolü,
const ve const olmayan `operator[]`, `size() const`, bildirim `.hpp`'de ve gövde
`.tpp`'de.

**Olası sorular**
1. *Gövde neden `.cpp`'de değil de `.tpp`'de?* → `.cpp` ayrı derlenince `Array<int>`
   için kod üretilmez ve linker "undefined reference" hatası verir. `.tpp` sadece
   düzen içindir. Header'ın sonunda include edildiği için derleyici gövdeyi görür.
2. *`new T[n]()` ile `new T[n]` farkı?* → `()` değer-başlatma yapar ve `int`'ler 0
   olur. `()` olmazsa değerler çöp olur (subject'teki `new int()` ipucu).
3. *Kopya kurucuyu yazmasaydın?* → Derleyicinin yazdığı kurucu sığ kopya yapar: sadece
   pointer kopyalanır. İki nesne aynı belleği paylaşır, birini değiştirmek diğerini de
   değiştirir ve yıkıcılar aynı belleği iki kez siler (double free).
4. *Neden iki `operator[]`?* → const nesnede (örn. `const Array<int> &` parametre)
   sadece const sürüm çağrılabilir ve `const T &` döndürür, yani okuma yapılır. const
   olmayan sürüm `T &` döndürür ve yazmaya izin verir.
5. *`numbers[-2]` nasıl yakalanıyor?* → index tipi `unsigned int`. -2 çok büyük bir
   sayıya (4294967294) döner, `index >= size_` olur ve exception atılır.
6. *operator='de `this != &other` neden var?* → `a = a` yazıldığında önce kendi
   belleğimizi silersek kopyalanacak veriyi kaybederiz. Bu kodda ayrıca önce yeni
   bellek ayrılıyor. Böylece `new` hata atarsa nesne eski haliyle kalır.
7. *T'den ne isteniyor?* → `new T[n]` için varsayılan kurucusu, kopya için de atama
   operatörü olmalı.

**Not:** Subject'le gelen `cpp07/main.cpp` `rand`/`srand` kullanıyor ama `<cstdlib>`
include etmiyor. `Array.hpp` NULL için zaten `<cstdlib>` include ettiğinden bu main
de derleniyor: `c++ -Wall -Wextra -Werror -std=c++98 -I. ../main.cpp` (ex02 içinde).
