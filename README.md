# Wordle (C + Python)

The five-letter word-guessing game, implemented twice: once in C and once in Python.

## What's inside

- **wordle_game.c + wordle_lib.c / wordle_lib.h** — the C game and its library (guess checking, letter feedback, vocabulary handling), with tests in `wordle_lib_test.c`.
- **wordle.py** — the same game in Python.
- **vocabulary.txt / tinyvocabulary.txt** — word lists the game draws from.

## Build & run

```sh
make            # builds wordle_game and the tests
./wordle_game
python3 wordle.py
```

## Tech

C, Python, Make
