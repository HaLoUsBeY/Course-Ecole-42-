#!/bin/bash
# polyset tek komut testi. Kullanim (exam klasorunde):
#   wsl bash test_polyset.sh sonuç/polyset
# Klasorde senin 6 dosyan olmali:
#   searchable_array_bag.hpp/.cpp  searchable_tree_bag.hpp/.cpp  set.hpp/.cpp
# Verilen dosyalar (bag, array_bag, tree_bag...) examshell'den otomatik alinir.
#
# Ne yapar:
#   1) examshell main + subject main + ek main ile derler (g++ ve clang++)
#   2) farkli argumanlarla calistirip referans cozumun ciktisiyla karsilastirir
#   3) valgrind

DIR="${1:?Klasor ver: wsl bash test_polyset.sh sonuç/polyset}"
HERE="$(cd "$(dirname "$0")" && pwd)"
SRC="$(cd "$HERE/$DIR" 2>/dev/null && pwd)" || { echo "Klasor bulunamadi: $DIR"; exit 1; }
REF="$HERE/42_examshell/.resources/rank05/level1/polyset"
[ -d "$REF" ] || { echo "42_examshell/.../polyset bulunamadi"; exit 1; }
FILES="searchable_array_bag.hpp searchable_array_bag.cpp searchable_tree_bag.hpp searchable_tree_bag.cpp set.hpp set.cpp"
for f in $FILES; do
	[ -f "$SRC/$f" ] || { echo "Eksik dosya: $DIR/$f"; exit 1; }
done

R='\033[0;31m'; G='\033[0;32m'; Y='\033[1;33m'; N='\033[0m'
W="$(mktemp -d)"
trap 'rm -rf "$W"' EXIT
mkdir -p "$W/ref" "$W/user"
cp "$REF/subject/"*.hpp "$REF/subject/array_bag.cpp" "$REF/subject/tree_bag.cpp" "$W/ref/"
cp "$REF/subject/"*.hpp "$REF/subject/array_bag.cpp" "$REF/subject/tree_bag.cpp" "$W/user/"
for f in $FILES; do cp "$REF/$f" "$W/ref/"; cp "$SRC/$f" "$W/user/"; done

# --- mainler
cp "$REF/main.cpp" "$W/main_examshell.cpp"
{ echo '#include "searchable_tree_bag.hpp"'; echo '#include "searchable_array_bag.hpp"'; echo '#include "set.hpp"'; cat "$REF/subject/main.cpp"; } > "$W/main_subject.cpp"
cat > "$W/main_ek.cpp" <<'EOF'
#include "searchable_tree_bag.hpp"
#include "searchable_array_bag.hpp"
#include "set.hpp"
#include <iostream>

int main()
{
	int v[] = {5, 3, 8, 1, 4, 7, 9, 3};

	// OCF: kopya kurucu ve atama derin kopya mi?
	searchable_array_bag a;
	a.insert(v, 8);
	searchable_array_bag a2(a);
	searchable_array_bag a3;
	a3 = a;
	a.clear();
	std::cout << "a2: "; a2.print();
	std::cout << "a3: "; a3.print();
	std::cout << "a2.has(9) " << a2.has(9) << " a2.has(2) " << a2.has(2) << " a.has(5) " << a.has(5) << std::endl;

	searchable_tree_bag t;
	t.insert(v, 8);
	searchable_tree_bag t2(t);
	searchable_tree_bag t3;
	t3 = t;
	t.clear();
	std::cout << "t2: "; t2.print();
	std::cout << "t3: "; t3.print();
	for (int i = 0; i <= 10; i++)
		std::cout << t2.has(i);
	std::cout << " | t.has(5) " << t.has(5) << std::endl;

	// const nesneler: has ve print const olmali
	const searchable_tree_bag ct(t2);
	const searchable_array_bag ca(a2);
	std::cout << "ct.has(7) " << ct.has(7) << " ca.has(7) " << ca.has(7) << std::endl;
	ct.print();
	ca.print();

	// set: ayni sayi iki kez girmemeli
	searchable_array_bag sb;
	set s(sb);
	s.insert(v, 8);
	s.insert(5);
	s.insert(100);
	std::cout << "set(array): "; s.print();
	std::cout << "get_bag: "; s.get_bag().print();
	std::cout << "s.has(100) " << s.has(100) << " s.has(6) " << s.has(6) << std::endl;
	s.clear();
	std::cout << "clear sonrasi: "; s.print();

	searchable_tree_bag tb;
	set st(tb);
	st.insert(v, 8);
	st.insert(3);
	std::cout << "set(tree): "; st.print();
	const set& cs = st;                 // const set: has ve print const olmali
	std::cout << "cs.has(4) " << cs.has(4) << std::endl;
	cs.print();
	return 0;
}
EOF

hata=0
ok()   { echo -e "  ${G}OK${N}  $1"; }
fail() { echo -e "  ${R}HATA${N} $1"; hata=1; }

build() { # $1 = ref|user  $2 = main  $3 = derleyici  $4 = cikti
	$3 -Wall -Wextra -Werror -std=c++98 -I"$W/$1" "$W/main_$2.cpp" "$W/$1/array_bag.cpp" "$W/$1/tree_bag.cpp" \
		"$W/$1/searchable_array_bag.cpp" "$W/$1/searchable_tree_bag.cpp" "$W/$1/set.cpp" -o "$4"
}

for m in examshell subject ek; do
	build ref $m g++ "$W/ref_$m" 2>"$W/referr.txt" || { echo "Referans derlenemedi ($m)"; head -30 "$W/referr.txt"; exit 1; }
done

echo -e "${Y}== 1) Derleme (-Wall -Wextra -Werror -std=c++98)${N}"
for cxx in g++ clang++; do
	for m in examshell subject ek; do
		if build user $m $cxx "$W/user_${cxx}_$m" 2> "$W/err.txt"; then
			ok "$cxx + $m main"
		else
			fail "$cxx + $m main derlenmedi:"
			head -20 "$W/err.txt" | sed 's/^/        /'
		fi
	done
done
[ $hata -eq 0 ] || { echo -e "\n${R}SONUC: DERLEME HATASI${N}"; exit 1; }

echo -e "${Y}== 2) Cikti (referansla karsilastirma)${N}"
check() { # $1 = main  $2.. = argumanlar
	m=$1; shift
	"$W/ref_$m" "$@" > "$W/r.txt" 2>&1
	timeout 5 "$W/user_g++_$m" "$@" > "$W/u.txt" 2>&1
	if diff -q "$W/r.txt" "$W/u.txt" >/dev/null; then
		ok "$m main  $*"
	else
		fail "$m main  $*  ciktisi farkli  (< beklenen  > senin)"
		diff "$W/r.txt" "$W/u.txt" | head -20 | sed 's/^/        /'
	fi
}
for args in "10 20 30" "5 3 8 1 4 7 9" "1 1 2 2" "0 -5 5" "42" "3 2 1"; do
	check examshell $args
	check subject $args
done
check ek

echo -e "${Y}== 3) Valgrind${N}"
for run in "examshell 10 20 30" "examshell 5 3 8 1 4 7 9" "ek"; do
	set -- $run; m=$1; shift
	if valgrind -q --leak-check=full --error-exitcode=9 "$W/user_g++_$m" "$@" >/dev/null 2>"$W/vg.txt"; then
		ok "$m main $*"
	else
		fail "$m main $*:"
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
