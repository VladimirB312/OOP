rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem При запуске без параметров ожидается ненулевой код возврата
%PROGRAM% >nul
if NOT ERRORLEVEL 1 goto err
echo Test 1 passed

rem При запуске с количеством параметром больше 4 ожидается ненулевой код возврата
%PROGRAM% crypt input output 100 extraarg >nul
if NOT ERRORLEVEL 1 goto err
echo Test 2 passed

rem При запуске с неверным типом шифрования ожидается ненулевой код возврата
%PROGRAM% invalidtype input output 100 >nul
if NOT ERRORLEVEL 1 goto err
echo Test 3 passed

rem При запуске с ключем меньше 0 ожидается ненулевой код возврата
%PROGRAM% crypt test-data/input.txt "%TEMP%\output.txt" -1 >nul
if NOT ERRORLEVEL 1 goto err
echo Test 4 passed

rem При запуске с ключем равным 0 ожидается нулевой код возврата
%PROGRAM% crypt test-data/input.txt "%TEMP%\output.txt" 0 >nul
if ERRORLEVEL 1 goto err
echo Test 5 passed

rem При запуске с ключем равным 255 ожидается нулевой код возврата
%PROGRAM% crypt test-data/input.txt "%TEMP%\output.txt" 255 >nul
if ERRORLEVEL 1 goto err
echo Test 6 passed

rem При запуске с ключем равным 256 ожидается ненулевой код возврата
%PROGRAM% crypt test-data/input.txt "%TEMP%\output.txt" 256 >nul
if NOT ERRORLEVEL 1 goto err
echo Test 7 passed

rem При запуске в режиме crypt с ключем 12 зашифрованый файл должен совпадать с тестовым
%PROGRAM% crypt test-data/fox.txt "%TEMP%\fox-encoded.txt" 12 >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox-encoded.txt" test-data\fox-encoded.txt >nul
if ERRORLEVEL 1 goto err
echo Test 8 passed

rem При запуске в режиме decrypt с ключем 12 расшифрованый файл должен совпадать с тестовым
%PROGRAM% decrypt "%TEMP%\fox-encoded.txt" "%TEMP%\fox.txt"  12 >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" test-data\fox.txt >nul
if ERRORLEVEL 1 goto err
echo Test 9 passed

rem При запуске сначала в режиме crypt, а затем в режиме decrypt с ключем 132 итоговый файл должен совпадать с исходным
%PROGRAM% crypt test-data/fox.txt "%TEMP%\fox-encoded.txt" 132 >nul
if ERRORLEVEL 1 goto err
%PROGRAM% decrypt "%TEMP%\fox-encoded.txt" "%TEMP%\fox.txt" 132 >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" test-data\fox.txt >nul
if ERRORLEVEL 1 goto err
echo Test 10 passed

rem При запуске сначала в режиме crypt, а затем в режиме decrypt с ключем 0 итоговый файл должен совпадать с исходным
%PROGRAM% crypt test-data/fox.txt "%TEMP%\fox-encoded.txt" 0 >nul
if ERRORLEVEL 1 goto err
%PROGRAM% decrypt "%TEMP%\fox-encoded.txt" "%TEMP%\fox.txt" 0 >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" test-data\fox.txt >nul
if ERRORLEVEL 1 goto err
echo Test 11 passed

rem При запуске сначала в режиме crypt, а затем в режиме decrypt с ключем 255 итоговый файл должен совпадать с исходным
%PROGRAM% crypt test-data/fox.txt "%TEMP%\fox-encoded.txt" 255 >nul
if ERRORLEVEL 1 goto err
%PROGRAM% decrypt "%TEMP%\fox-encoded.txt" "%TEMP%\fox.txt" 255 >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" test-data\fox.txt >nul
if ERRORLEVEL 1 goto err
echo Test 11 passed

rem При запуске сначала в режиме crypt, а затем в режиме decrypt с пустым файлом итоговый файл должен совпадать с исходным
%PROGRAM% crypt test-data/empty.txt "%TEMP%\empty-encoded.txt" 255 >nul
if ERRORLEVEL 1 goto err
%PROGRAM% decrypt "%TEMP%\empty-encoded.txt" "%TEMP%\empty.txt" 255 >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\empty.txt" test-data\empty.txt >nul
if ERRORLEVEL 1 goto err
echo Test 12 passed

echo OK
exit 0

:err
echo Program testing failed
exit 1