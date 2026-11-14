# CPP06 — C++ Casts: Çalışma Notları

Modülün ek kuralı: her egzersizde dönüşüm **belirli bir cast** ile yapılmalı ve savunmada sorulur.
Bu çözümde: **ex00 → static_cast**, **ex01 → reinterpret_cast**, **ex02 → dynamic_cast**.

## Dört C++ cast'i

| Cast | Ne yapar | Ne zaman |
|---|---|---|
| `static_cast<T>(x)` | Derleme zamanında kontrol edilen "mantıklı" dönüşüm | Sayısal tipler arası (char/int/float/double), `void*` → `T*`, kalıtımda upcast. Downcast'te **kontrol yok**. |
| `dynamic_cast<T>(x)` | Çalışma zamanında (RTTI) gerçek tipi kontrol eder | Polimorfik sınıflarda (en az bir `virtual`) güvenli downcast. Pointer'da başarısızsa `NULL`, referansta `std::bad_cast` fırlatır. |
| `reinterpret_cast<T>(x)` | Bitlere dokunmadan tipi yeniden yorumlar | Pointer ↔ tam sayı, ilgisiz pointer tipleri. En tehlikelisi, taşınabilir değil. |
| `const_cast<T>(x)` | Yalnızca `const`/`volatile` ekler veya kaldırır | Const olmayan API'ye const veri vermek. Gerçekten const olan nesneyi değiştirmek UB. (Bu modülde kullanılmadı.) |

- **C tarzı cast** `(int)x`: sırayla const/static/reinterpret cast'lerinden tutanı dener; ne yaptığı belli değil, kodda aranması zor. C++ cast'leri niyeti açıkça gösterir.
- **Örtük (implicit) dönüşüm**: derleyicinin kendiliğinden yaptığı (int → double gibi). **Açık (explicit)**: cast ile bizim yazdığımız.
- **Upcast**: türetilmiş → taban (her zaman güvenli). **Downcast**: taban → türetilmiş (kontrol gerekir → `dynamic_cast`).

---

## ex00 — ScalarConverter (`./convert <literal>`)

Girdi önce küçük fonksiyonlarla sırayla test edilir: `isCharLiteral` → `isIntLiteral` → `isFloatLiteral` → `isDoubleLiteral`. Tespit edilen tipe `strtol`/`strtod` ile çevrilir (C++98'de `strtof`/`stoi` yok), sonra diğer üç tipe **`static_cast`** ile açıkça çevrilip yazdırılır. Cast'ten **önce** değer aralığa sığıyor mu bakılır; sığmıyorsa `impossible`. Sınıfta tek static metot var (`convert`); yardımcılar `.cpp` içinde `static` (dosyaya özel) fonksiyonlar.

Verdiğim kararlar:
- char aralığı **0–127 (ASCII)**: dışı `impossible`, yazdırılamayan (0, 127, 1.5 → 1) `Non displayable`.
- `'a'` ve tırnaksız tek karakter `a` char sayılır (kabuk `'a'`'nın tırnaklarını siler). Tek rakam `5` ise int.
- int'e sığmayan tam sayı (`2147483648`) ve float'a sığmayan float literal **double gibi** işlenir. double'a bile sığmayan → dördü de `impossible`.
- Geçersiz girdi (`abc`, `""`, `42f`, `1e5`) → dördü de `impossible` (subject yalnız ondalık gösterim istiyor).
- Tam sayı değerli sayılara `.0` eklenir (`42.0f`); diğerleri float 6, double 15 anlamlı basamakla yazılır (`numeric_limits<T>::digits10`). Girdi float ise double satırı da float hassasiyetiyle (6 basamak) yazılır: `42.42f` → `double: 42.42`. Aksi halde float 42.42'yi tam tutamadığı için double'a çevirince `42.4199981689453` görünürdü (evo'da sorulursa bunu anlat).

Hızlı test:
```sh
for a in 0 nan 42.0f a "'a'" -42 2147483648 -inff +inff +inf 127 300 1.5 abc ""; do echo "== $a"; ./convert "$a"; done
```

Olası sorular:
1. **Sınıf neden/nasıl örneklenemez?** Saklayacak verisi yok, sadece static metot var. Kurucular, yıkıcı ve `operator=` private → dışarıdan nesne oluşturulamaz.
2. **Hangi cast, neden?** `static_cast`: sayısal tipler arası dönüşüm derleme zamanında bilinir ve güvenlidir; `reinterpret_cast` burada anlamsız (bitleri yorumlar, değeri çevirmez).
3. **nan'ı nasıl tespit ettin, neden char/int'e çevrilemez?** `d != d` sadece NaN için doğrudur. NaN bir sayı olmadığı için tam sayı karşılığı yok → `impossible`.
4. **Neden aralığı cast'ten önce kontrol ediyorsun?** Sığmayan bir kayan noktalıyı int'e çevirmek tanımsız davranış; önce kontrol, sonra cast.
5. **`2147483648` ve `-inff` ne verir?** İlki: char/int impossible, float `2147483648.0f`, double `2147483648.0`. İkincisi: char/int impossible, float `-inff`, double `-inf`.
6. **Yardımcı fonksiyonlar neden sınıfta değil?** Subject "yalnızca tek static metot" diyor; `.cpp`'deki `static` fonksiyonlar başka dosyadan görünmez (internal linkage).

---

## ex01 — Serializer (`./serializer`)

`serialize` bir `Data*`'yi `uintptr_t`'ye, `deserialize` geri `Data*`'ye **`reinterpret_cast`** ile çevirir; bitler aynen kalır, yalnızca tip yorumu değişir. `Data` boş olmayan basit bir struct (`id`, `name`, `score`). Test: `deserialize(serialize(p)) == p`; ayrıca geri dönen pointer üzerinden yapılan değişiklik orijinal nesnede görünür (aynı adres).

Olası sorular:
1. **Neden `reinterpret_cast`? `static_cast` olmaz mı?** `static_cast` pointer ↔ tam sayı dönüşümüne izin vermez, derlenmez. Bu dönüşüm yalnızca bitleri yeniden yorumlamaktır.
2. **`uintptr_t` nedir?** `<stdint.h>`'deki, bir pointer'ı kayıpsız tutabilecek kadar büyük işaretsiz tam sayı tipi. `int`/`unsigned int` 64 bit sistemde adresi kesebilir.
3. **Veri gerçekten kopyalanıyor mu?** Hayır, sadece adres sayıya çevriliyor. Nesne silinirse geri dönen pointer geçersiz (dangling) olur.
4. **Serializer neden örneklenemez?** Subject "hiçbir şekilde" diyor: OCF üyeleri private, metotlar static.
5. **Data neden struct ve OCF yok?** Yalnız public veri üyeleri olan basit bir yapı; derleyicinin ürettiği kopya kurucu/atama doğru çalışır (pointer veya elle yönetilen kaynak yok).

---

## ex02 — Identify real type (`./identify`)

`Base` sadece public sanal yıkıcıya sahip; bu onu **polimorfik** yapar ve `dynamic_cast`'in çalışma zamanında gerçek tipi sorgulamasını sağlar. `A`, `B`, `C` boş, `Base`'den public türetilmiş. `generate()` `std::rand() % 3` ile rastgele birini `new` ile oluşturur (`srand` main'de bir kez). `identify(Base*)` sırayla `dynamic_cast<A*>` … dener, `NULL` değilse o tiptir. `identify(Base&)` içinde pointer yok: `dynamic_cast<A&>` başarısızsa `std::bad_cast` fırlatır; `<typeinfo>` yasak olduğundan taban sınıfı `std::exception&` ile yakalanır.

Olası sorular:
1. **`dynamic_cast` neden `virtual` gerektirir?** Gerçek tip bilgisi (RTTI) vtable üzerinden tutulur; polimorfik olmayan tipte `dynamic_cast` downcast'i derlenmez.
2. **Pointer ve referans sürümü başarısızlıkta nasıl farklı?** Pointer → `NULL` döner. Referans `NULL` olamaz → exception fırlatır.
3. **`std::bad_cast`'i neden doğrudan yakalamadın?** Tanımı `<typeinfo>`'da, o başlık yasak. `bad_cast` `std::exception`'dan türediği için `catch (const std::exception&)` onu yakalar.
4. **Base'in yıkıcısı neden virtual?** `delete basePtr` yapınca türetilmiş sınıfın yıkıcısı da çağrılsın (aksi UB); ayrıca sınıfı polimorfik yapar.
5. **`static_cast` kullansaydın?** Kontrol yapmaz; `static_cast<A*>(p)` her zaman "başarılı" görünür, yanlış tipte kullanmak UB. Hep "A" basardı.
6. **`srand` neden `generate` içinde değil?** Aynı saniyede tekrar tekrar `srand(time(NULL))` çağırmak aynı sayıyı verir; tohum bir kez atılır.
