rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem При запуске с одним параметром отличным от -h ожидается ненулевой код возврата
%PROGRAM% -v >nul
if NOT ERRORLEVEL 1 goto err
echo Test 1 passed

rem При запуске с правильными параметрами ожидается нулевой код возврата
rem В случае отсутствия искомой строки во входном файле, выходной файл должен быть равен входному
%PROGRAM% test-data\fox.txt "%TEMP%\fox.txt" bird cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" test-data\fox.txt >nul
if ERRORLEVEL 1 goto err
echo Test 2 passed

rem Тест замены во входном файле строки "dog" на "cat"
%PROGRAM% test-data\fox.txt "%TEMP%\fox.txt" dog cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" test-data\fox-replace-dog-with-cat.txt >nul
if ERRORLEVEL 1 goto err
echo Test 3 passed

rem Тест замены во входном файле первых символов строки "fox" на "cat"
%PROGRAM% test-data\fox-first.txt "%TEMP%\fox-first.txt" fox cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox-first.txt" test-data\fox-first-replace.txt >nul
if ERRORLEVEL 1 goto err
echo Test 4 passed

rem Тест замены во входном файле строки "1231234" на "XYZ"
%PROGRAM% test-data\digits.txt "%TEMP%\digits.txt" 1231234 XYZ
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\digits.txt" test-data\digits-replace-1231234-with-XYZ.txt >nul
if ERRORLEVEL 1 goto err
echo Test 5 passed

rem Тест замены во входном файле, состоящим из нескольких строк, строки "brown" на "red"
%PROGRAM% test-data\multiline.txt "%TEMP%\multiline.txt" brown red
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\multiline.txt" test-data\multiline-replace.txt >nul
if ERRORLEVEL 1 goto err
echo Test 6 passed

rem Тест замены в с многократным вхождением искомой строки в строку-заменитель "ma" "mama"
%PROGRAM% test-data\mama.txt "%TEMP%\mama.txt" ma mama
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\mama.txt" test-data\mama-replace.txt >nul
if ERRORLEVEL 1 goto err
echo Test 7 passed

rem При отсутствии, заданного параметрами, входного файла, программа должна вернуть ненулевой код возврата
%PROGRAM% test-data\missing.txt "%TEMP%\mama.txt" ma mama >nul
if NOT ERRORLEVEL 1 goto err
echo Test 8 passed

echo OK
exit 0

:err
echo Program testing failed
exit 1