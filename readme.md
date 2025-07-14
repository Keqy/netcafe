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

--**Тесты**--

Тестовые файлы находятся в папке ```build```

*Выходные данные:*\
```test.txt```
```
09:00
08:48 1 client1
08:48 13 NotOpenYet
09:41 1 client1
09:48 1 client2
09:52 3 client1
09:52 13 ICanWaitNoLonger!
09:54 2 client1 1
10:25 2 client2 2
10:58 1 client3
10:59 2 client3 3
11:30 1 client4
11:35 2 client4 2
11:35 13 PlaceIsBusy
11:45 3 client4
12:33 4 client1
12:33 12 client4 1
12:43 4 client2
15:52 4 client4
19:00 11 client3
19:00
1 70 05:58
2 30 02:18
3 90 08:01
```
\
```wrongtimeformat.txt```
```
Wrong data format: 8:00 20:00
```
\
```youshallnotpass.txt```
```
10:00
10:00 1 stepan
10:10 2 stepan 1
10:40 1 valeriy
10:40 1 stepan
10:40 13 YouShallNotPass
10:43 2 valeriy 1
10:43 13 PlaceIsBusy
10:44 1 stepan
10:44 13 YouShallNotPass
10:45 2 valeriy 2
15:50 1 stepan
15:50 13 YouShallNotPass
15:51 2 stepan 2
15:51 13 PlaceIsBusy
15:51 1 stepan
15:51 13 YouShallNotPass
16:00 4 stepan
18:00 11 valeriy
18:00
1 72 05:50
2 96 07:15
```
\
```wrongtable.txt```
```
10:00
11:04 1 client1
11:06 2 client1 2
11:06 13 PlaceIsBusy
11:10 3 client1
11:10 13 ICanWaitNoLonger!
20:00 11 client1
20:00
1 0 00:00
```
\
```nightshift.txt```
```
22:40
22:30 1 client1
22:30 13 NotOpenYet
22:40 1 client1
22:44 3 client1
22:44 13 ICanWaitNoLonger!
22:44 2 client1 1
23:00 1 client2
23:01 2 client2 1
23:01 13 PlaceIsBusy
23:01 2 client2 2
23:20 4 client2
01:35 4 client1
02:14 1 client3
02:20 3 client3
02:20 13 ICanWaitNoLonger!
02:21 2 client3 3
04:00 11 client3
04:00
1 120 02:51
2 40 00:19
3 80 01:39
```
```queueoverflow.txt```
```
10:00
10:00 1 a
10:00 2 a 1
10:05 1 b
10:05 2 b 2
10:10 1 c
10:20 1 d
10:40 1 e
12:00 1 f
12:00 11 f
13:00 3 c
13:00 11 c
13:01 3 d
13:10 1 g
13:10 3 d
13:10 11 d
13:10 3 e
13:10 3 f
13:15 4 a
13:15 12 e 1
14:00 4 b
14:00 12 g 2
15:00 11 e
15:00 11 g
15:00
1 30 05:00
2 25 04:55
```
\
```notexist.txt```
```
Couldn't open file for reading: notexist.txt
```
\
--**Коды ошибок**--\
1 - Файл не задан.\
2 - Файл не открывается на чтение.\
3 - Неправильный формат данных.
