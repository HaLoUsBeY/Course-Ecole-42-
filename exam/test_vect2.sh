#!/bin/bash
# vect2 tek komut testi. Kullanim (exam klasorunde):
#   wsl bash test_vect2.sh sonuç/vect2
# Klasorde vect2.hpp ve vect2.cpp olmali. Senin dosyalarina dokunmaz.
#
# Ne yapar:
#   1) Subject main'i     (g++ ve clang++, -Wall -Wextra -Werror -std=c++98)
#   2) examshell main'i   (subject main'i ile ayni + tester'in kullandigi)
#   3) Ek main            (subject cumleleri + kenar durumlar: v*2==vect2(4,4), const [], zincir, self-assign...)
#   Her biri referans cozumun ciktisiyla karsilastirilir + valgrind.

DIR="${1:?Klasor ver: wsl bash test_vect2.sh sonuç/vect2}"
HERE="$(cd "$(dirname "$0")" && pwd)"
SRC="$(cd "$HERE/$DIR" 2>/dev/null && pwd)" || { echo "Klasor bulunamadi: $DIR"; exit 1; }
REF="$HERE/42_examshell/.resources/rank05/level1/vect2"
[ -d "$REF" ] || { echo "42_examshell/.../vect2 bulunamadi"; exit 1; }
for f in vect2.hpp vect2.cpp; do
	[ -f "$SRC/$f" ] || { echo "Eksik dosya: $DIR/$f"; exit 1; }
done

R='\033[0;31m'; G='\033[0;32m'; Y='\033[1;33m'; N='\033[0m'
W="$(mktemp -d)"
trap 'rm -rf "$W"' EXIT
mkdir -p "$W/ref" "$W/user"
cp "$REF/vect2.hpp" "$REF/vect2.cpp" "$W/ref/"
cp "$SRC/vect2.hpp" "$SRC/vect2.cpp" "$W/user/"

# --- mainler
sed -n '/^#include "vect2.hpp"/,$p' "$REF/sub.txt" > "$W/main_subject.cpp"
cp "$REF/main.cpp" "$W/main_examshell.cpp"
cat > "$W/main_ek.cpp" <<'EOF'
#include "vect2.hpp"
#include <iostream>

int main()
{
	// subject cumlesi: (vect2(2,2) * 2 == vect2(4,4)) dogru olmali
	std::cout << "vect2(2,2)*2 == vect2(4,4): " << (vect2(2, 2) * 2 == vect2(4, 4)) << std::endl;
	std::cout << "2*vect2(2,2) == vect2(4,4): " << (2 * vect2(2, 2) == vect2(4, 4)) << std::endl;

	// subject cumlesi: << ciktisi "{" v[0] ", " v[1] "}" ile ayni
	vect2 p(-7, 13);
	std::cout << p << std::endl;
	std::cout << "{" << p[0] << ", " << p[1] << "}" << std::endl;

	// const nesne: [], +, -, *, ==, !=, <<, tekli -
	const vect2 c(3, -4);
	std::cout << "c: " << c << " c[0]: " << c[0] << " c[1]: " << c[1] << std::endl;
	std::cout << "c + c: " << (c + c) << " c - c: " << (c - c) << " c * -2: " << (c * -2) << std::endl;
	std::cout << "-c: " << -c << " -(-c): " << -(-c) << " 0 * c: " << 0 * c << std::endl;
	std::cout << "c == c: " << (c == c) << " c != c: " << (c != c) << std::endl;
	vect2 kopya(c);
	std::cout << "kopya(c): " << kopya << " kopya == c: " << (kopya == c) << std::endl;

	// [] ile yazma
	vect2 a;
	a[0] = 5;
	a[1] = -6;
	std::cout << "a: " << a << std::endl;

	// zincirleme ve referans donusu
	vect2 b(1, 1);
	vect2 d;
	d = b = a;
	std::cout << "d = b = a: " << d << " " << b << std::endl;
	(b += a) += a;
	std::cout << "(b += a) += a: " << b << std::endl;
	(b -= a) -= a;
	std::cout << "(b -= a) -= a: " << b << std::endl;
	(b *= 2) *= 3;
	std::cout << "(b *= 2) *= 3: " << b << std::endl;
	vect2& ayni = b;
	b = ayni;                                   // self-assignment
	std::cout << "b = b: " << b << std::endl;
	++(++b);
	std::cout << "++(++b): " << b << std::endl;
	--(--b);
	std::cout << "--(--b): " << b << std::endl;

	// son ek: eski degeri doner, nesne degisir
	vect2 e(10, 20);
	vect2 eski = e++;
	std::cout << "eski: " << eski << " e: " << e << std::endl;
	eski = e--;
	std::cout << "eski: " << eski << " e: " << e << std::endl;

	// karisik ifade
	vect2 f = 2 * a - a * 3 + -a;
	std::cout << "2*a - a*3 + -a: " << f << std::endl;
	f += f += a;
	std::cout << "f += f += a: " << f << std::endl;
	return 0;
}
EOF

hata=0
ok()   { echo -e "  ${G}OK${N}  $1"; }
fail() { echo -e "  ${R}HATA${N} $1"; hata=1; }

# --- referans derle (siyah kutu: sadece ciktisi kullanilir)
for m in subject examshell ek; do
	g++ -Wall -Wextra -std=c++98 -I"$W/ref" "$W/main_$m.cpp" "$W/ref/vect2.cpp" -o "$W/ref_$m" 2>/dev/null \
		|| { echo "Referans derlenemedi ($m)"; exit 1; }
done

echo -e "${Y}== 1) Derleme (-Wall -Wextra -Werror -std=c++98)${N}"
for cxx in g++ clang++; do
	for m in subject examshell ek; do
		if $cxx -Wall -Wextra -Werror -std=c++98 -I"$W/user" "$W/main_$m.cpp" "$W/user/vect2.cpp" -o "$W/user_${cxx}_$m" 2> "$W/err.txt"; then
			ok "$cxx + $m main"
		else
			fail "$cxx + $m main derlenmedi:"
			head -20 "$W/err.txt" | sed 's/^/        /'
		fi
	done
done
[ $hata -eq 0 ] || { echo -e "\n${R}SONUC: DERLEME HATASI${N}"; exit 1; }

echo -e "${Y}== 2) Cikti (referansla karsilastirma)${N}"
for m in subject examshell ek; do
	"$W/ref_$m" > "$W/r.txt" 2>&1
	timeout 5 "$W/user_g++_$m" > "$W/u.txt" 2>&1
	if diff -q "$W/r.txt" "$W/u.txt" >/dev/null; then
		ok "$m main"
	else
		fail "$m main ciktisi farkli  (< beklenen  > senin)"
		diff "$W/r.txt" "$W/u.txt" | head -30 | sed 's/^/        /'
	fi
done

echo -e "${Y}== 3) Valgrind${N}"
for m in subject ek; do
	if valgrind -q --leak-check=full --error-exitcode=9 "$W/user_g++_$m" >/dev/null 2>"$W/vg.txt"; then
		ok "$m main"
	else
		fail "$m main:"
		head -20 "$W/vg.txt" | sed 's/^/        /'
	fi
done

echo
if [ $hata -eq 0 ]; then
	echo -e "${G}SONUC: HEPSI GECTI${N}"
else
	echo -e "${R}SONUC: HATA VAR (yukaridaki HATA satirlarina bak)${N}"
	exit 1
fi
