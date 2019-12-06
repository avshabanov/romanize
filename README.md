# Romanization Utility

This simple utility attempts to do cyrillic to roman conversion.
Internal implementation uses hashtable and bloom filter.

Sample usage:

```bash
$ make
# ...produces ./target/romanize
$ echo 'фи-вы-а' | ./target/romanize
fi-vy-a
```

Note, that it understands only UTF-8 by default, so, for example,
CP1251-encoded input needs to be converted to UTF-8 first.

E.g.:

```bash
$ cat text-in-cp1251.txt | iconv -f cp1251 | ./target/romanize
# produces readable text
```
