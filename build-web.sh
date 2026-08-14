#!/usr/bin/env bash
# Builds the browser (WebAssembly) version of the game into web/dist/.
#
# Requires emscripten on PATH (https://emscripten.org/docs/getting_started):
#     git clone https://github.com/emscripten-core/emsdk
#     cd emsdk && ./emsdk install latest && ./emsdk activate latest
#     source ./emsdk_env.sh
#
# The output must be served over HTTP — browsers refuse to load a .wasm
# from a file:// URL.

set -euo pipefail
cd "$(dirname "$0")"

out=web/dist
mkdir -p "$out"

# -Oz --closure 1        : ~330 KB wasm + ~28 KB js (about 113 KB gzipped)
# -sASYNCIFY             : lets the blocking std::getline loop suspend the
#                          whole C++ call stack instead of freezing the tab
# -sMODULARIZE           : exposes createGame() instead of polluting globals
# -sINVOKE_RUN=0         : the page calls main() once stdout is wired up
em++ -std=c++17 -Oz TextBasedGame/*.cpp -o "$out/game.js" \
	-sASYNCIFY -sASYNCIFY_STACK_SIZE=65536 \
	-sMODULARIZE=1 -sEXPORT_NAME=createGame \
	-sINVOKE_RUN=0 -sENVIRONMENT=web \
	-sEXPORTED_RUNTIME_METHODS=FS,stringToNewUTF8,callMain \
	--closure 1


echo "Built $out"
echo "Serve game.js + game.wasm from your app (see web/README.md)."
