rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамл€ющих кавычек (если они были)

rem ѕеременна€ PROGRAM будет хранить первый аргумент командной строки заключЄнный в кавычки
set PROGRAM="%~1"

rem ѕри запуске с параметром -h ожидаетс€ нулевой код возврата
%PROGRAM% -h >nul
if ERRORLEVEL 1 goto err
echo Test 1 passed

rem ѕри запуске с параметром отличным от -h и несуществующим файлом ожидаетс€ ненулевой код возврата
%PROGRAM% missing.file >nul
if NOT ERRORLEVEL 1 goto err
echo Test 2 passed

rem ѕри запуске с более чем 2 параметрами ожидаетс€ ненулевой код возврата
%PROGRAM% matrix.file -h >nul
if NOT ERRORLEVEL 1 goto err
echo Test 3 passed

rem ѕри запуске с входным файлом правильного формата ожидаетс€ нулевой код возврата
%PROGRAM% test-data\matrix.txt >nul
if ERRORLEVEL 1 goto err
echo Test 4 passed

rem ѕри запуске с входным файлом в котором присутствует не цифровое значение ожидаетс€ ненулевой код возврата
%PROGRAM% test-data\matrix-error.txt >nul
if NOT ERRORLEVEL 1 goto err
echo Test 5 passed

rem ѕри запуске с входным файлом в котором не достаточное количество значений ожидаетс€ ненулевой код возврата
%PROGRAM% test-data\matrix-not-enough.txt >nul
if NOT ERRORLEVEL 1 goto err
echo Test 6 passed

rem ѕри запуске с входным файлом в котором лишнее количество значений ожидаетс€ ненулевой код возврата
%PROGRAM% test-data\matrix-extra.txt >nul
if NOT ERRORLEVEL 1 goto err
echo Test 7 passed

rem ≈сли определитель матрицы равен 0 ожидаетс€ ненулевой код возврата
%PROGRAM% test-data\matrix-null.txt >nul
if NOT ERRORLEVEL 1 goto err
echo Test 8 passed

echo OK
exit 0

:err
echo Program testing failed
exit 1