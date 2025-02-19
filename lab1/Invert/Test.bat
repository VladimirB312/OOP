rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem При запуске с параметром -h ожидается нулевой код возврата
%PROGRAM% -h >nul
if ERRORLEVEL 1 goto err
echo Test 1 passed

rem При запуске с параметром отличным от -h и несуществующим файлом ожидается ненулевой код возврата
%PROGRAM% missing.file
if NOT ERRORLEVEL 1 goto err
echo Test 2 passed

rem При запуске с более чем 2 параметрами ожидается ненулевой код возврата
%PROGRAM% matrix.file -h >nul
if NOT ERRORLEVEL 1 goto err
echo Test 3 passed

rem При запуске с входным файлом правильного формата ожидается нулевой код возврата
%PROGRAM% test-data\matrix.txt >nul
if ERRORLEVEL 1 goto err
echo Test 4 passed

rem При запуске с входным файлом в котором присутствует не цифровое значение ожидается ненулевой код возврата
%PROGRAM% test-data\matrix-error.txt >nul
if NOT ERRORLEVEL 1 goto err
echo Test 5 passed

rem При запуске с входным файлом в котором первое значение не цифровое ожидается ненулевой код возврата
%PROGRAM% test-data\matrix-error-first.txt >nul
if NOT ERRORLEVEL 1 goto err
echo Test 6 passed

rem При запуске с входным файлом в котором последнее значение не цифровое ожидается ненулевой код возврата
%PROGRAM% test-data\matrix-error-last.txt >nul
if NOT ERRORLEVEL 1 goto err
echo Test 7 passed

rem При запуске с входным файлом в котором не достаточное количество значений ожидается ненулевой код возврата
%PROGRAM% test-data\matrix-not-enough.txt >nul
if NOT ERRORLEVEL 1 goto err
echo Test 8 passed

rem При запуске с входным файлом в котором лишнее количество значений ожидается ненулевой код возврата
%PROGRAM% test-data\matrix-extra.txt >nul
if NOT ERRORLEVEL 1 goto err
echo Test 9 passed

rem Если определитель матрицы равен 0 ожидается ненулевой код возврата
%PROGRAM% test-data\matrix-null.txt >nul
if NOT ERRORLEVEL 1 goto err
echo Test 10 passed

echo OK
exit 0

:err
echo Program testing failed
exit 1