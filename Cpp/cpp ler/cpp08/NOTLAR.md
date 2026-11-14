# CPP08 — Çalışma notları

Modülün amacı: **STL container + iterator + algorithm** kullanmak. Kendi döngünü yazmak yerine
`std::find`, `std::sort`, `std::min_element`, `std::max_element`, `insert(pos, first, last)` gibi
hazır araçları kullan. Subject: "kullanmazsan çok kötü not alırsın".

- Derleme: `make` → `ex00`, `ex01`, `ex02` (subject'teki örnek `./ex01` adını kullanıyor).
- Şablon gövdeleri `.tpp` dosyasında, `.hpp`'nin sonunda `#include` ediliyor (header'da gövde yok kuralı şablonlar için geçerli değil, ama düzen için ayırdık).
- Kontrol: `make && make` (ikincisi "Nothing to be done"), `valgrind --leak-check=full ./exNN`.

---

## ex00 — easyfind

**Ne / nasıl:** `easyfind(T &container, int value)` bir function template. İçinde `std::find(begin, end, value)`
çağrılıyor; sonuç `end()` ise `std::runtime_error` fırlatılıyor, değilse ilk eşleşmenin iterator'u dönüyor.
const container için ikinci bir overload `const_iterator` döndürüyor. main'de vector, list, deque, bulunan /
bulunmayan, boş ve const container test ediliyor.

**Kavramlar:** container (vector/list/deque), iterator, `[begin, end)` aralığı, `std::find` (doğrusal arama, O(n)),
`typename T::iterator` (bağımlı isim), template'in her `T` için ayrı örneklenmesi.

**Olası sorular:**
1. *Neden `typename T::iterator`?* — `T::iterator` T'ye bağlı bir isim; derleyici onun tür mü değişken mi olduğunu bilemez, `typename` "bu bir tür" der.
2. *Bulunamazsa neden exception?* — Subject ikisine de izin veriyor. `std::find` gibi `end()` döndürmek de olurdu; exception seçtim çünkü çağıran kontrol etmeyi unutup `end()`'i dereference edemez.
3. *Neden template tanımı header/.tpp'de, .cpp'de değil?* — Derleyici `easyfind<std::vector<int> >` gibi örneği üretmek için gövdeyi görmeli; ayrı .cpp'de olsaydı link hatası alırdık.
4. *`std::map` ile çalışır mı?* — Hayır: elemanları `std::pair`, int ile karşılaştırılamaz. Subject associative container istemiyor.
5. *Dönen iterator ile ne yapılabilir?* — Değeri okuyup değiştirebilirsin (`*easyfind(v, 30) = 33;`), `std::distance` ile indeksini bulabilirsin.
6. *Karmaşıklık?* — O(n); sıralı container olsa bile `std::find` baştan sona bakar.

---

## ex01 — Span

**Ne / nasıl:** `Span` en fazla `N` (unsigned int) sayı tutar: `max_` + `std::vector<int> numbers_`.
`addNumber` doluysa `std::out_of_range` fırlatır. `shortestSpan`: kopyayı `std::sort` ile sırala, yan yana
farkların en küçüğü. `longestSpan`: `max_element - min_element`. `addRange(first, last)` bir member template:
önce sığıp sığmadığını `std::distance` ile kontrol eder, sonra `numbers_.insert(end, first, last)`.

**Kavramlar:** `std::vector`, `std::sort` (O(n log n), random-access iterator ister), `std::min_element` /
`std::max_element`, iterator aralığı, member template, `std::exception` türevleri (`out_of_range`, `logic_error`),
taşma (overflow), OCF (vector kendi kopyasını yaptığı için derin kopya otomatik).

**Olası sorular:**
1. *En kısa mesafeyi nasıl buluyorsun?* — Sıralı dizide en yakın iki sayı mutlaka yan yanadır; tek geçişte komşu farklarının minimumu. Tüm çiftleri denemek O(n²) olurdu.
2. *Neden kopya üzerinde sıralıyorsun?* — Fonksiyon `const`; eklenme sırasını bozmak istemiyoruz.
3. *Dönüş tipi neden `long`?* — `INT_MAX - INT_MIN` int'e sığmaz (4294967295). Fark `long` ile hesaplanıyor (42'deki 64-bit Linux'ta long 64 bit).
4. *addRange'e sığmayan aralık verirsen?* — Hiçbirini eklemez, exception fırlatır ("ya hepsi ya hiçbiri"); main'de boyutun 0 kaldığı gösteriliyor.
5. *addRange neden template?* — Her container'ın iterator'u (list, vector, hatta `int*` dizi) ile çalışsın diye; `vector::insert` de aynı şekilde çalışır.
6. *Aynı sayı iki kez eklenirse shortestSpan?* — 0 döner (main'de "duplicates" testi). 10 000 sayılık testte beklenen sonuçlar 3 ve 29997.
7. *Neden kendi exception sınıfı yok?* — Standart `std::out_of_range` / `std::logic_error` yeterli; istersen CPP05'teki gibi iç içe `class FullException : public std::exception` de yazılabilir.

---

## ex02 — MutantStack

**Ne / nasıl:** `std::stack` bir **container adaptor**: elemanları `protected` bir üye olan `c`'de tutar
(varsayılan `std::deque<T>`) ve sadece `push/pop/top/size/empty` sunar. `MutantStack<T, Container>`
`std::stack<T, Container>`'dan türer, `Container`'ın iterator türlerini `typedef` ile alır ve
`begin/end/rbegin/rend` (const sürümleriyle) içinde `this->c.begin()` vb. döndürür. Stack'in tüm fonksiyonları
kalıtımla hazır gelir.

**Kavramlar:** container adaptor, `protected` üyeye türetilmiş sınıftan erişim, `this->c` (bağımlı taban sınıf),
`typedef typename ...`, iterator / const_iterator / reverse_iterator, iterasyon sırası (begin = en alttaki, ilk eklenen;
`top()` = `*rbegin()`), şablonda varsayılan parametre (`Container = std::deque<T>`), C++98'de `> >` boşluğu.

**Olası sorular:**
1. *`std::stack` neden iterable değil?* — Adaptor; LIFO arayüzünü bilerek kısıtlıyor, iterator vermiyor.
2. *`c` nedir, nasıl erişiyorsun?* — stack'in alttaki container'ı; `protected` olduğu için türeyen sınıf erişebilir.
3. *Neden `this->c`, sadece `c` değil?* — Taban sınıf şablon parametresine bağlı; derleyici bağımlı tabanlarda ismi kendiliğinden aramaz, `this->` aramayı örnekleme anına erteler.
4. *Subject main'i `std::list` ile neden aynı çıktıyı veriyor?* — `push_back`/`back`/`pop_back` stack'in `push`/`top`/`pop`'u ile aynı uçta çalışıyor ve iki yapı da baştan (ilk eklenen) sona doğru geziliyor. main iki çıktıyı da basıyor: `17 1 5 3 5 737 0`.
5. *`std::stack<int> s(mstack);` neden derleniyor?* — MutantStack bir `std::stack`; türetilmiş nesne taban referansına bağlanır, stack'in kopya kurucusu çalışır (slicing, iterator'lar kaybolur).
6. *`std::stack`'in yıkıcısı sanal değil, sorun mu?* — MutantStack ek üye tutmadığı için sızıntı yok; ama `std::stack*` üzerinden `delete` etmek teknik olarak tanımsız davranış, bu yüzden öyle kullanmıyoruz.
7. *Başka container ile çalışır mı?* — Evet: `MutantStack<int, std::vector<int> >`, `MutantStack<int, std::list<int> >` main'de test ediliyor.
