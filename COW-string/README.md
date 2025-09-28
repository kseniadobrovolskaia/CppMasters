# greatstr 

## Сборка
 
```
  $ git clone https://github.com/kseniadobrovolskaia/CppMasters
  $ cd COW-string
```
 
* По умолчанию будут скомпилированы бенчмарк *benchGreatStr* и тесты *greatstrTests*, написанные с помощью тестового фреймворка *GoogleTests*:

```
  $ cmake -S . -B build
  $ cmake --build build
```

## Запуск бенчмарка, сравнивающего GreatStr со std::string

``` 
  $ cd build
  $ ./benchGreatStr
``` 
```bash
-----------------------------------------------------------------------
Benchmark                             Time             CPU   Iterations
-----------------------------------------------------------------------
GreatStrDefaultConstructor         66.8 ns         66.8 ns     10494557
StdStringDefaultConstructor        75.6 ns         75.6 ns      9083339
GreatStrFromCString/10             86.5 ns         86.5 ns      7939398
GreatStrFromCString/100            83.2 ns         83.2 ns      8167448
StdStringFromCString/10             110 ns          110 ns      6545675
StdStringFromCString/100            183 ns          183 ns      3766038
GreatStrCopyConstructor/10         25.6 ns         25.6 ns     26277587
GreatStrCopyConstructor/100        23.8 ns         23.8 ns     29008246
StdStringCopyConstructor/10         107 ns          107 ns      6515194
StdStringCopyConstructor/100        175 ns          175 ns      3933432
```

*Видно, что копирование COW-строк значительно быстрее, чем у std::string.*

## Тестирование

```
  $ cd build/Test
  $ ./greatstrTests
```
