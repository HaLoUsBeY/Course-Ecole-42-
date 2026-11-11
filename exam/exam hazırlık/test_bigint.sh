#!/bin/bash
# Kullanim (exam hazirlik klasorunde): wsl bash test_bigint.sh deneme1
# deneme1 klasorunde bigint.hpp ve bigint.cpp olmali.
# examshell'in resmi tester.sh'sini gecici bir klasorde calistirir; senin dosyalarina dokunmaz.

DIR="${1:?Klasor adi ver: wsl bash test_bigint.sh deneme1}"
HERE="$(cd "$(dirname "$0")" && pwd)"
SRC="$(cd "$HERE/$DIR" 2>/dev/null && pwd)" || { echo "Klasor bulunamadi: $DIR"; exit 1; }
REF=""
for base in "$HERE" "$HERE/.." "$HERE/../.."; do
	if [ -d "$base/42_examshell/.resources/rank05/level1/bigint" ]; then
		REF="$base/42_examshell/.resources/rank05/level1/bigint"
		break
	fi
done
[ -n "$REF" ] || { echo "42_examshell klasoru bulunamadi"; exit 1; }

for f in bigint.hpp bigint.cpp; do
	[ -f "$SRC/$f" ] || { echo "Eksik dosya: $DIR/$f"; exit 1; }
done

W="$(mktemp -d)"
trap 'rm -rf "$W"' EXIT
mkdir -p "$W/x/.resources/rank05/level1" "$W/x/rendu/bigint"
cp -r "$REF" "$W/x/.resources/rank05/level1/"
cp "$SRC/bigint.hpp" "$SRC/bigint.cpp" "$W/x/rendu/bigint/"

cd "$W/x/.resources/rank05/level1/bigint" && bash tester.sh
