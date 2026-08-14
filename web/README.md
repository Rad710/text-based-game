# Browser build

The game compiled to WebAssembly with emscripten. The game logic is the same
code the Windows build uses — only the console I/O differs, and that is
isolated in `TextBasedGame/Platform.h` / `Platform.cpp`.

Run `../build-web.sh` to produce `dist/`:

| file | what it is |
| --- | --- |
| `game.wasm` | the compiled C++, ~330 KB (~102 KB gzipped) |
| `game.js` | emscripten's loader glue, ~28 KB (~11 KB gzipped) |

`dist/` is generated and not committed. The host app supplies the UI.

## Integrating

Load `game.js` as a plain static asset, not through a bundler — emscripten's
glue resolves the `.wasm` via `import.meta.url` and does runtime environment
detection, which bundlers tend to rewrite and break. A `<script>` tag pointing
at a static path works; so does a dynamic `import()` of a URL the bundler does
not process.

It defines `createGame(options)`. Two options are required:

```js
const game = await createGame({
    // byte-level stdout: (charCode) => …, and null meaning "flush"
    preRun: [(module) => module.FS.init(null, onByte, onByte)],
    // called whenever the game wants a line; resolve with what the user typed
    readLine: () => new Promise((resolve) => { … }),
});
game.callMain([]);
```

Three things the host has to get right:

**Flush stdout before resolving a read.** Prompts like `>> Command: ` end
without a newline, so they sit in the buffer until something flushes them. Call
the flush (`onByte(null)`) at the start of `readLine`, or the prompt shows up
after the answer instead of before it.

**Echo typed lines yourself.** The program never echoes its input, so the UI has
to write the line into the transcript when the user submits it.

**Handle a little ANSI.** The game emits `ESC[2J` / `ESC[H` (clear screen) and
`ESC[1;33m` / `ESC[0m` (bold yellow, on the `die` message). Everything else is
plain text.

## What the port needed

**Blocking input.** A browser tab cannot sit inside `std::getline(std::cin, …)`;
it would freeze the page. Emscripten's Asyncify suspends the whole C++ call
stack instead, so `GameInterface::play()` still reads a line the way it always
did.

**`system("cls")`.** A Windows shell call with nothing behind it in a browser.
It became the ANSI clear-screen escape, which is what it was reaching for
anyway.

**Output flushing.** As above — the reason `readLine` has to drain stdout.

## Gotcha

`--closure 1` renames dotted properties, so `Module.readLine` becomes
`Module.Yb` and the game never starts. `Platform.cpp` uses `Module["readLine"]`
for that reason — don't "clean it up" to dot notation.
