#!/bin/bash
# Exam Rank 05 sorularinin hepsi icin genel test (test_bigint.sh'nin genellestirilmis hali).
# Kullanim (exam klasorunde):  wsl bash test_soru.sh <soru> <klasor>
#   <soru>   : vect2 | bigint | polyset | life | bsq
#   <klasor> : cozumunun oldugu klasor (bu betigin klasorune gore), ornek: deneme/vect2-1024
# examshell'in resmi tester.sh'sini gecici bir klasorde calistirir; senin dosyalarina dokunmaz.

Q="${1:?Soru adi ver: vect2 | bigint | polyset | life | bsq}"
DIR="${2:?Klasor ver: wsl bash test_soru.sh $Q deneme/$Q-1}"
HERE="$(cd "$(dirname "$0")" && pwd)"
SRC="$(cd "$HERE/$DIR" 2>/dev/null && pwd)" || { echo "Klasor bulunamadi: $DIR"; exit 1; }

REF=""
LEVEL=""
for base in "$HERE" "$HERE/.." "$HERE/../.."; do
	for lv in level1 level2; do
		if [ -d "$base/42_examshell/.resources/rank05/$lv/$Q" ]; then
			REF="$base/42_examshell/.resources/rank05/$lv/$Q"
			LEVEL="$lv"
			break 2
		fi
	done
done
[ -n "$REF" ] || { echo "Soru bulunamadi: $Q (42_examshell/.resources/rank05 altinda)"; exit 1; }

case "$Q" in
	life|bsq)
		ls "$SRC"/*.c >/dev/null 2>&1 || { echo "Klasorde .c dosyasi yok: $DIR"; exit 1; }
		ls "$SRC"/*.h >/dev/null 2>&1 || { echo "Klasorde .h dosyasi yok (tester en az bir .h istiyor): $DIR"; exit 1; }
		;;
	*)
		ls "$SRC"/*.cpp >/dev/null 2>&1 || { echo "Klasorde .cpp dosyasi yok: $DIR"; exit 1; }
		;;
esac

W="$(mktemp -d)"
trap 'rm -rf "$W"' EXIT
mkdir -p "$W/x/.resources/rank05/$LEVEL" "$W/x/rendu/$Q"
cp -r "$REF" "$W/x/.resources/rank05/$LEVEL/"
cp "$SRC"/* "$W/x/rendu/$Q/" 2>/dev/null

echo ">>> $Q ($LEVEL) test ediliyor: $DIR"
cd "$W/x/.resources/rank05/$LEVEL/$Q" && bash tester.sh < /dev/null
