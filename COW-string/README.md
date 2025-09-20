# greatstr 

## Сборка
 
```
  $ git clone https://github.com/kseniadobrovolskaia/CppMasters
  $ cd COW-string
```
 
* По умолчанию будут скомпилированы программа, использующая строки *useStr* и тесты *greatstrTests*, написанные с помощью тестового фреймворка *GoogleTests*:

```
  $ cmake -S . -B build
  $ cmake --build build
```

## Запуск программы, использующей строки

``` 
  $ cd build
  $ ./useStr
``` 

## Тестирование

```
  $ cd build/Test
  $ ./greatstrTests
```
