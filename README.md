### geos/wasm

GEOS and WebAssembly.

Braindump:

I don't think WebAssembly will constitute a big performance advantage for
geographical operations. However, what I do want is battle-tested geometry
operations. I love Turf, and continue to contribute to Turf, but a lot of Turf's
geometry algorithms are implemented from scratch and aren't nearly as robust as
GEOS.

Then Turf uses JSTS for a few of its operations. JSTS - JavaScript port of JTS,
which is a port of GEOS - has gotten a lot better. Maybe JSTS is the real best
option: it gives roughly the code of GEOS, albeit removed two steps from the
original, but doesn't have the full serialization cost of a WASM library.

That said, JSTS is large - we've been trying to remove it from Turf for years
and years, and it's not _exactly_ the same set of bugs as GEOS. If I have bugs,
I want all of the GEOS things to have bugs! And the roaring success of, say,
Shapely, indicates that GEOS's level of bugs is pretty tolerable.

So, the goal of GEOS/WASM is that maybe:

- We can get the same features/bugs as GEOS, with fewer steps to the source than
  JSTS.
- We can just use GEOS for a lot of stuff.
- Maybe it'll be fast, or small? I don't really know, this is all TBD. I've
  tinkered with WebAssembly but don't know that much about it.

## Other routes

- Maybe rust-geo is robust? But it [doesn't have
  buffering](https://github.com/georust/geo/issues/641), so probably a no-go.

## Implementation options

- Emscripten: oldest and most established option.
- Zig: I like Zig, and maybe this would make the toolchain simpler, and I'd much
  prefer to write Zig than C or C++. But on the
  other hand, maybe it'd make the process way less documented.
- Clang: looks like it does WASM directly, too. Looks like Emscripten _uses_
  LLVM's native support now.

## Notes

Okay, so step one is as painful as expected. Getting the basic GEOS example to compile
using any tool is hard. I can't get it compiled with Zig, Emscripten or cc. It's because
of import paths and stuff. I haven't messed with C in ages.

Looks like there are other people compiling GEOS as a prereq for other stuff.

- https://github.com/bugra9/gdal3.js

Okay, so far seeing:

- I'll need to compile GEOS first, then compile the bindings per the [docs](https://emscripten.org/docs/compiling/Building-Projects.html#using-libraries).
  Trying to compile GEOS separately isn't working yet.

```
CXXFLAGS="-fexceptions -DRENAME_INTERNAL_LIBTIFF_SYMBOLS -s ERROR_ON_UNDEFINED_SYMBOLS=0" CFLAGS=" -fexceptions -DRENAME_INTERNAL_LIBTIFF_SYMBOLS -s ERROR_ON_UNDEFINED_SYMBOLS=0" emconfigure ./configure --enable-shared=no --disable-inline
```
