A tiny little lisp with heart!

A work in progress...

### Goals

    0. Learn new things, have fun doing it.

    1. Immutability is awesome!  And C is a terrible language to
    implement immutability in.  Should be fun!

    2. Use monadic parsing so that the language (scheme-like in
    nature) can be tweaked to try out new ideas.  This should also
    make it easy to add support for interesting formats and perhaps
    even make the (hopefully!) fast C parser available within the
    interpreter.

    3. Speaking of interpretation... if we link against llvm the
    interpreter should be able to compile code to any llvm target.

    4. Be portable.  It should run equally well in the browser or on
    any architecture supported by the compiler. (empscripten? asm.js?
    Sure!).
    
