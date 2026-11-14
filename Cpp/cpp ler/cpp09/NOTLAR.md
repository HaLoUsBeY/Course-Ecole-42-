# CPP09 — Çalışma Notları (STL)

Modül kuralı: her alıştırmada en az bir container (ex02'de en az iki), **bir alıştırmada kullanılan container sonrakilerde kullanılamaz.**

| Alıştırma | Program | Container |
|---|---|---|
| ex00 | `btc` | `std::map` |
| ex01 | `RPN` | `std::stack` (altında `std::list`) |
| ex02 | `PmergeMe` | `std::vector` + `std::deque` |

Ortak: her sınıf OCF (varsayılan kurucu, kopya kurucu, `operator=`, yıkıcı), başlıklarda include guard ve gövde yok, `c++ -Wall -Wextra -Werror -std=c++98`, Makefile yeniden bağlamaz (ikinci `make` → "Nothing to be done").

---

## ex00 — Bitcoin Exchange (`./btc input.txt`)

**Ne yapıyor:** `data.csv` dosyasını `std::map<std::string, double>` (tarih → fiyat) içine yüklüyor. Sonra girdi dosyasını satır satır okuyor: `"tarih | değer"` biçimini, tarihi (YYYY-MM-DD, gerçek takvim, artık yıl) ve değeri (0–1000 arası düz sayı) doğruluyor. Ardından `değer * o tarihteki fiyat` yazıyor. Tarih veritabanında yoksa **bir önceki (küçük) tarih** kullanılıyor.

**Neden map:** Anahtara göre hep sıralı (kırmızı-siyah ağaç), arama O(log n). `lower_bound` ile "en yakın küçük tarih" birkaç satırda bulunuyor.

**Kilit kavramlar:** `lower_bound(date)` → anahtarı `>= date` olan ilk eleman. Eşit değilse `--it`. `it == begin()` ise daha eski veri yok. Tarihler string olarak karşılaştırılabiliyor, çünkü `YYYY-MM-DD` sıfır dolgulu: sözlük sırası = zaman sırası.

**Kararlar:**
- Hata mesajları `std::cout`'a gidiyor. Subject'in genel kuralı "aksi belirtilmedikçe standart çıktı" diyor; ex00'da stderr denmiyor (ex01/ex02'de deniyor). Böylece çıktı sırası da korunuyor.
- İlk satır `date | value` ise atlanıyor, boş satırlar sessizce geçiliyor, satır sonundaki `\r` siliniyor.
- Veritabanındaki ilk tarihten (2009-01-02) önceki tarih → `Error: no data before => ...`.
- Boş dosya ya da klasör → `Error: empty or unreadable file.`
- `std::setprecision(10)`: yoksa `1000 * 47115.93` sonucu `4.71159e+07` olarak basılıyor.

**Olası sorular:**
1. *Neden map, vector değil?* → Sıralı anahtar ve `lower_bound` hazır. Vector'de sıralamayı ve aramayı kendim yazmam gerekirdi.
2. *`2012-01-15` veritabanında yok, ne olur?* → `lower_bound` 2012-01-17'yi verir, eşit değil → `--it` → 2012-01-14 kullanılır.
3. *Artık yıl kuralı?* → 4'e bölünür ve 100'e bölünmez, **ya da** 400'e bölünür. 2012-02-29 geçerli; 2013-02-29 ve 1900-02-29 geçersiz.
4. *`2147483648` neden "too large", taşma olmuyor mu?* → Önce yalnız rakam/nokta mı diye bakılıyor, sonra `strtod` ile double'a çevriliyor. Double'da taşma yok, sonra `> 1000` kontrolü yapılıyor.
5. *`1e2`, `abc`, `1.2.3` ne olur?* → `parseNumber` yalnızca [işaret] rakam [. rakam] kabul ediyor → `bad input`.
6. *Bu programda başka container var mı?* → Hayır, yalnızca map (std::string container sayılmaz).

---

## ex01 — RPN (`./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"`)

**Ne yapıyor:** İfadeyi boşluklara göre parçalıyor (`istringstream >> token`). Her token tek karakter olmalı: rakamsa yığına itiliyor; `+ - * /` ise yığından iki sayı çekilip sonuç geri itiliyor. Sonda yığında tam **bir** sayı kalmalı. Her hata `std::runtime_error("Error")` fırlatıyor, `main` bunu `std::cerr`'e yazıyor.

**Neden stack:** RPN'de operatör her zaman **son girmiş iki** sayıya uygulanır; bu tam olarak LIFO.

**Önemli ayrıntı:** `std::stack` bir *container adaptörü*. Varsayılan olarak altta `std::deque` kullanır. Deque ex02'de lazım olduğu için `std::stack<long, std::list<long> >` yazdım. C++98'de `> >` arasında boşluk şart, yoksa `>>` operatörü sanılır.

**Olası sorular:**
1. *"8 2 -" neden 6, -6 değil?* → Önce çekilen sayı **sağdaki** işlenen: `right = top; pop; left = top; pop; left - right`.
2. *Hangi durumlar Error?* → Tek karakter olmayan token (`12`, `-1`, `1.5`), bilinmeyen karakter (`(`, `%`), operatör geldiğinde yığında 2'den az sayı, sıfıra bölme, sonda yığında 1'den farklı sayıda eleman, int taşması.
3. *Neden `long`?* → Ara sonuçlar int sınırını aşarsa yakalamak için. Hesap long'da (64 bit) yapılıyor, sonra `INT_MIN..INT_MAX` kontrolü. `9 9 * ... *` (10 tane 9) → Error.
4. *Sonuç neden 10'dan büyük olabiliyor?* → Kural yalnız girdi sayıları için (< 10). Ara sonuç ve sonuç serbest.
5. *Parantez?* → Desteklenmiyor, subject istemiyor. `"(1 + 1)"` → Error.
6. *`"11+"` gibi boşluksuz ifade?* → Token'lar boşlukla ayrılmalı, `11+` tek token → Error.

---

## ex02 — PmergeMe (`./PmergeMe 3 5 9 7 4`)

**Ne yapıyor:** Pozitif tam sayıları hem `std::vector<int>` hem `std::deque<int>` içinde **Ford–Johnson (merge-insertion)** ile sıralıyor. İki sürüm ayrı fonksiyonlar (subject "generic fonksiyon kullanma" öneriyor). Çıktı: `Before:`, `After:`, sonra iki süre satırı. Süreye **veriyi container'a yükleme + sıralama** dahil, ekrana yazdırma hariç. Süre `std::clock()` ile ölçülüyor (C++98 standardı, işlemci zamanı). Linux'ta çözünürlük 1 µs olduğu için ondalıklar `.00000`.

**Neden vector + deque:** İkisi de rastgele erişimli, yani ikili aramada `chain[mid]` O(1). İkisi de ex00/ex01'de kullanılmadı. Deque bellekte bloklar halinde durduğu için erişim ve ortaya ekleme vector'den yavaş; süre farkı buradan geliyor (3000 sayıda ≈ 1.2 ms ve ≈ 5 ms).

**Neden değerler değil indeksler sıralanıyor?** Aynı sayı birden çok kez olabilir (subject v3.3 tekrarları açıkça istiyor). Her elemanın kimliği `vec_` içindeki indeksi. Karşılaştırma `vec_[indeks]` ile yapılıyor. `partner[büyük] = küçük` tablosu sayesinde eşler hiç karışmıyor.

**Girdi kararları:** Yalnız rakamlardan oluşan ve `int`'e sığan sayılar kabul ediliyor. `-1`, `+5`, `abc`, `1.5`, `2147483648` → `Error` (stderr). **0 kabul ediliyor**: ex00'daki "positive ... between 0 and 1000" ifadesi subject'in 0'ı pozitif saydığını gösteriyor. Değerlendirici isterse `toNumber`'a `if (number == 0) throw ...` eklemek tek satır. Tekrarlar kabul ve korunuyor. `"3 5 9"` gibi tek argümanda birden çok sayı da kabul (istringstream ile bölünüyor).

### Algoritma (her özyineleme seviyesinde)
1. **Eşle:** Elemanları ikişer al, her çiftte bir karşılaştırma yap. Büyük → `bigs`, küçük → onun eşi. Sayı tekse sondaki eşsiz kalır.
2. **Özyineleme:** `bigs`'i aynı fonksiyonla sırala.
3. **Ana zincir:** `[b1, a1, a2, ..., am]` (a = sıralı büyükler, b = eşleri). `b1 ≤ a1` olduğu için başa karşılaştırmasız konur.
4. **Ekle:** Kalan `b2, b3, ...` (ve eşsiz eleman) **Jacobsthal sırasıyla**, ikili aramayla eklenir. `b_k` için arama yalnızca **`a_k`'nın solunda** yapılır, çünkü `b_k ≤ a_k`. Eşsiz eleman için bütün zincir aranır.

**Jacobsthal sayıları:** J(0)=0, J(1)=1, J(n)=J(n-1)+2·J(n-2) → 0, 1, 1, 3, 5, 11, 21, 43, 85…
Ekleme sırası: **b3 b2 | b5 b4 | b11 b10 … b6 | b21 … b12 | …** (her grup kendi sınırından geriye doğru).
**Neden?** Bu gruplarla her `b_k`'nın arama aralığı en fazla `2^t − 1` eleman olur. Böylece ikili arama tam `t` karşılaştırma yapar, hiç boşa karşılaştırma yapılmaz. Toplam karşılaştırma Knuth'un F(n) sınırına eşit. Test ettim: n=21 için en kötü 66, n=22 için 71; F(n) hiç aşılmadı.

**Küçük optimizasyon:** Grup içinde k azaldıkça `a_k` zincirde hep daha solda kalır. Bu yüzden `a_k`'nın yerini her seferinde baştan aramak yerine, bir önceki bulunduğu yerden (`right`) sola doğru aramaya devam ediyoruz. Bu arama indeks karşılaştırır, sayıları karşılaştırmaz. 3000 sayıda süreyi ~11 ms'den ~1.2 ms'ye indirdi.

### 7 sayılık örnek: `5 2 8 1 9 3 6`
1. Çiftler: (5,2) (8,1) (9,3), eşsiz: **6** → bigs = [5, 8, 9]. (3 karşılaştırma)
2. bigs özyinelemeli sıralanır → [5, 8, 9]. (Kendi içinde: (5,8) çifti, 9 eşsiz; 9 ikili aramayla eklenir.)
3. a1=5 (b1=2), a2=8 (b2=1), a3=9 (b3=3), b4=6 (eşi yok).
   Ana zincir: **[2, 5, 8, 9]**
4. Jacobsthal sırası: b3, b2, sonra b4.
   - b3=3 → a3=9'un solunda ara: [2,5,8] → **[2, 3, 5, 8, 9]**
   - b2=1 → a2=8'in solunda ara: [2,3,5] → **[1, 2, 3, 5, 8, 9]**
   - b4=6 → eşi yok, tüm zincirde ara → **[1, 2, 3, 5, 6, 8, 9]** ✔

En kötü durumda toplam karşılaştırma 13 = F(7). Bunu `./PmergeMe 5 2 8 1 9 3 6` ile kendin gör.

**Olası sorular:**
1. *Ford–Johnson'un merge sort / insertion sort'tan farkı?* → Amaç **karşılaştırma sayısını** en aza indirmek. Çiftleme, büyükleri özyinelemeli sıralama ve Jacobsthal sırasıyla sınırlı ikili ekleme yapılır.
2. *Jacobsthal sırası neden?* → Her ekleme `2^t − 1` elemanlık aralığa düşer → ikili arama tam t karşılaştırma, israf yok.
3. *Tekrar eden sayılar nasıl çalışıyor?* → İndeks sıralandığı için her eleman benzersiz. Eşit değerler sorun çıkarmaz.
4. *Neden iki ayrı fonksiyon (vector/deque)?* → Subject generic fonksiyondan kaçınmayı öneriyor. Ayrıca her container'ın kendi davranışı ölçülsün.
5. *Süreye ne dahil?* → argv'yi container'a doldurma + sıralama. Doğrulama ve `Before:` yazdırma ölçüm dışında (önce bir kez doğrulanıyor).
6. *Karmaşıklık?* → Karşılaştırma O(n log n), optimuma çok yakın. Ama vector/deque'nun ortasına ekleme O(n) olduğundan toplam veri kaydırma O(n²). Bu, dizide yapılan her ekleme sıralamasında böyle.

### Test komutları (WSL)
```bash
./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
./PmergeMe `shuf -r -i 1-20 -n 3000 | tr "\n" " "`     # tekrarlı
./PmergeMe "-1" "2"                                  # Error
# sıralı mı?
ARR=`shuf -i 1-100000 -n 3000 | tr "\n" " "`
[ "$(./PmergeMe $ARR | sed -n 2p | cut -d' ' -f2-)" = "$(echo $ARR | tr ' ' '\n' | sort -n | tr '\n' ' ' | sed 's/ $//')" ] && echo SIRALI
```
