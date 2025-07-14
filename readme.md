--**Сборка**--

Используется система сборки CMake.\
Компилятор - mingw для Windows и gcc для Linux.

*Windows*\
```cd <путь>\netcafe```\
```cmake -S . -B build -G "MinGW Makefiles" && mingw32-make -C build```\
```cd build```\
```netcafe.exe test.txt``` или ```netcafe.exe <ваш-файл>.txt```

*Linux*\
```cd <путь>/netcafe```\
```cmake -S . -B build && cmake --build build```\
```cd build```\
```./netcafe test.txt``` или ```./netcafe <ваш-файл>.txt```

\
--**Коды ошибок**--\
1 - Файл не задан.\
2 - Файл не открывается на чтение.\
3 - Неправильный формат данных.
