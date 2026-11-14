# CPP05 — Çalışma notları (Repetition and Exceptions)

Derleme: her klasörde `make` → `./bureaucrat`, `./form`, `./forms`, `./intern`.
Hepsi `c++ -Wall -Wextra -Werror -std=c++98` ile derlenir; valgrind sızıntı yok.

Genel kural hatırlatması: derece **1 en yüksek**, **150 en düşük**. "Derece artır" = sayıyı küçült.
Karşılaştırmada `bureaucrat.getGrade() > gerekenDerece` ise memur **yetersiz** (sayı büyük = rütbe düşük).

---

## ex00 — Bureaucrat

**Ne yapıyor?** `Bureaucrat` sabit (`const`) bir isim ve 1–150 arası bir derece tutar. Kurucu ve
`incrementGrade()` / `decrementGrade()` aralık dışına çıkılırsa `GradeTooHighException` veya
`GradeTooLowException` fırlatır. `operator<<` çıktısı: `<name>, bureaucrat grade <grade>.`

**Kavramlar:** istisna (`throw` / `try` / `catch`), `std::exception`'dan türeyen iç içe (nested) sınıf,
`what() const throw()`, const üye + init list, OCF, üye olmayan `operator<<` (getter kullanır, `friend` yok).

**Muhtemel sorular**
1. *Neden `std::exception`'dan türettin?* — `catch (std::exception & e)` ile hepsi tek blokta yakalanabilsin ve `what()` sanal olduğu için doğru mesaj gelsin.
2. *`throw()` ne demek?* — C++98 istisna belirtimi: bu fonksiyon istisna fırlatmaz. `std::exception::what()` da böyle bildirildiği için override ederken aynısını yazıyoruz.
3. *Kurucu istisna fırlatırsa ne olur?* — Nesne hiç oluşmamış sayılır, yıkıcısı çağrılmaz; o ana kadar kurulmuş üyeler (ör. `name_`) otomatik yok edilir.
4. *`name_` const iken atama operatörü ne yapıyor?* — const üye atanamaz, sadece `grade_` kopyalanıyor (main'de "assigned" testi bunu gösteriyor).
5. *Neden referansla yakalıyorsun (`catch (std::exception & e)`)?* — Kopyalama olmaz ve dilimleme (slicing) olmaz; türetilmiş sınıfın `what()`'ı çağrılır.
6. *İstisna sınıfları OCF'de mi olmalı?* — Subject'e göre hayır; derleyicinin ürettikleri yeterli.

---

## ex01 — Form

**Ne yapıyor?** `Form` sabit isim, `signed_` bayrağı (başta `false`), sabit imza ve çalıştırma dereceleri
tutar. Dereceler aralık dışındaysa kurucu `Form::GradeTooHigh/LowException` fırlatır. `beSigned(Bureaucrat)`
derece yeterliyse formu imzalar, değilse `GradeTooLowException` fırlatır. `Bureaucrat::signForm(Form&)`
bu istisnayı yakalayıp `X signed Y` ya da `X couldn't sign Y because <reason>.` yazar.

**Kavramlar:** sınıflar arası döngüsel bağımlılık → `Bureaucrat.hpp`'de `class Form;` ileri bildirimi,
`.cpp`'de gerçek `#include`; init list sırası = üye bildirim sırası; istisnayı bir fonksiyonda fırlatıp
başka fonksiyonda yakalamak.

**Muhtemel sorular**
1. *Neden ileri bildirim (forward declaration)?* — İki başlık birbirini include ederse döngü olur. `signForm` sadece referans aldığı için eksik tip yeterli; tam tanım `.cpp`'de include ediliyor.
2. *Eşit derece imzalayabilir mi?* — Evet; kontrol `getGrade() > gradeToSign_` ise hata, eşitse imzalar (main'de 50/50 testi).
3. *Neden `beSigned` fırlatıyor da `signForm` yakalıyor?* — Form kuralı kontrol eder, memur sonucu raporlar; istisna çağrı zincirinde yukarı çıkar.
4. *Form atama operatörü neyi kopyalıyor?* — Sadece `signed_`; isim ve dereceler const.
5. *Init list sırasını karıştırırsam?* — `-Wall` ile `-Wreorder` uyarısı → `-Werror` yüzünden derlenmez; üyeler her zaman bildirim sırasıyla kurulur.
6. *Özellikler neden private?* — Subject öyle istiyor; dışarıdan erişim sadece getter'larla.

---

## ex02 — AForm + somut formlar

**Ne yapıyor?** `Form` soyut `AForm` oldu (saf sanal `executeAction() const = 0`). `execute(executor)` önce
imzalı mı (`FormNotSignedException`) ve derece yeterli mi (`GradeTooLowException`) diye **taban sınıfta** bakar,
sonra sanal `executeAction()`'ı çağırır (Template Method fikri — subject'in "daha zarif yol" dediği).
Somut formlar: Shrubbery (145/137, `<target>_shrubbery` dosyasına ASCII ağaç), Robotomy (72/45, %50 başarı,
`std::rand() % 2`), PresidentialPardon (25/5, Zaphod Beeblebrox affı). `Bureaucrat::executeForm` sonucu yazar.

**Kavramlar:** soyut sınıf, saf sanal fonksiyon, sanal yıkıcı, kalıtımda kurucu zinciri
(`AForm("...", 145, 137)` init list'te), türetilmiş sınıfta `AForm::operator=(other)` çağırmak,
`std::ofstream` (C++98'de `fileName.c_str()` şart), `srand(time(NULL))` main'de bir kez.

**Muhtemel sorular**
1. *AForm neden soyut, nasıl anlaşılır?* — En az bir saf sanal fonksiyonu var (`= 0`); `AForm f;` derlenmez (main'de yorum satırı).
2. *Yıkıcı neden `virtual`?* — `AForm* p = new RobotomyRequestForm(...); delete p;` dediğimizde alt sınıfın yıkıcısı da çalışsın, sızıntı/UB olmasın.
3. *Kontroller neden tabanda?* — Tek yerde yazılır, alt sınıflar sadece işini yapar; yeni form eklerken kontrolü unutmak mümkün olmaz.
4. *`srand` neden `executeAction` içinde değil?* — Her çağrıda tekrar tohumlarsak aynı saniyede hep aynı sonuç gelir; program başında bir kez yeterli.
5. *Dosya açılamazsa?* — `ShrubberyCreationForm::FileOpenException` fırlatılır; `executeForm` yakalayıp mesaj yazar (main'de `no_such_dir/home` testi).
6. *`target_` neden const değil?* — Atama operatörü hedefi de kopyalayabilsin diye; isim/dereceler zaten tabanda const.

---

## ex03 — Intern

**Ne yapıyor?** `Intern::makeForm(name, target)` form adını bir isim dizisinde arar; bulduğu indeksteki
**fonksiyon işaretçisi** ile ilgili formu `new` ile oluşturup `AForm*` döner ve `Intern creates <form>` yazar.
Bilinmeyen isimde hata mesajı yazıp `NULL` döner. Dönen formu `delete` etmek çağıranın görevi.
Geçerli adlar: `shrubbery creation`, `robotomy request`, `presidential pardon`.

**Kavramlar:** fonksiyon işaretçisi + `typedef`, paralel diziler (`names[i]` ↔ `creators[i]`),
`static` (dosyaya özel) fonksiyonlar, polimorfik dönüş (`AForm*`), sahiplik/bellek yönetimi.

**Muhtemel sorular**
1. *Neden if/else zinciri yok?* — Subject cezalandırıyor; dizi + döngü okunur ve yeni form eklemek tek satır.
2. *`typedef AForm* (*FormCreator)(std::string const &);` ne demek?* — "string referansı alıp `AForm*` dönen fonksiyonu gösteren işaretçi" tipine `FormCreator` adı veriyor.
3. *Neden üye fonksiyon işaretçisi değil?* — İkisi de olur. Üye versiyonu: `AForm* (Intern::*creators[3])(std::string const &) const` ve çağrı `(this->*creators[i])(target)`. Burada daha sade olduğu için dosyaya özel `static` fonksiyonlar seçildi.
4. *Bellek kimde?* — `makeForm` `new` ile oluşturur, çağıran `delete` eder (main'de tüm formlar siliniyor; valgrind temiz).
5. *Bilinmeyen isimde neden istisna değil de NULL?* — Subject sadece "açık bir hata mesajı yaz" diyor; NULL dönüp main'de kontrol etmek basit. İstisna fırlatmak da savunulabilir.
6. *Intern'in OCF'si neden boş?* — Hiç üyesi yok; kopya/atama kopyalanacak bir şey olmadığı için `(void)other` ile boş.

---

## Subject'te açık olmayan noktalar ve seçimler

- Artırma/azaltma fonksiyon adları verilmemiş → `incrementGrade()` / `decrementGrade()`.
- `Form`/`AForm` için `operator<<` biçimi serbest → `Form <name> [signed: yes/no, grade to sign: X, grade to execute: Y]`.
- const üyeli sınıflarda (`Bureaucrat`, `Form`, `AForm`) atama operatörü yalnız const olmayan alanları kopyalar.
- Tüm mesajlar `std::cout`'a yazılır (genel kural: aksi belirtilmedikçe standart çıktı).
- Robotomy başarısız olsa da bu bir istisna değil; form yine "executed" sayılır.
- Zaten imzalı formu tekrar imzalamak hata sayılmadı (subject bir şey istemiyor).
- `Intern creates <form>` mesajında oluşturulan formun adı (`getName()`) yazılır.
