rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem При запуске без параметров ожидается ненулевой код возврата
%PROGRAM% >nul
if NOT ERRORLEVEL 1 goto err
echo Test 1 passed

rem При запуске с первым нечисловым параметром ожидается ненулевой код возврата
%PROGRAM% str23ing 16 1F >nul
if NOT ERRORLEVEL 1 goto err
echo Test 2 passed

rem При запуске со вторым нечисловым параметром ожидается ненулевой код возврата
%PROGRAM% 16 st65ring 1F >nul
if NOT ERRORLEVEL 1 goto err
echo Test 3 passed

rem При запуске со значением исходной системы счисления больше 36 ожидается ненулевой код возврата
%PROGRAM% 37 3 1F >nul
if NOT ERRORLEVEL 1 goto err
echo Test 4 passed

rem При запуске со значением исходной системы счисления меньше 2 ожидается ненулевой код возврата
%PROGRAM% 1 3 0 >nul
if NOT ERRORLEVEL 1 goto err
echo Test 5 passed

rem При запсуске с максимальным значением исходной системы счисления ожидается нулевой код возврата
%PROGRAM% 36 3 1F >nul
if ERRORLEVEL 1 goto err
echo Test 6 passed

rem При запсуске с минимальным значением исходной системы счисления ожидается нулевой код возврата
%PROGRAM% 2 3 11 >nul
if ERRORLEVEL 1 goto err
echo Test 7 passed

rem При запуске со значением выходной системы счисления больше 36 ожидается ненулевой код возврата
%PROGRAM% 16 37 1F >nul
if NOT ERRORLEVEL 1 goto err
echo Test 8 passed

rem При запуске со значением выходной системы счисления меньше 2 ожидается ненулевой код возврата
%PROGRAM% 4 1 0 >nul
if NOT ERRORLEVEL 1 goto err
echo Test 9 passed

rem ППри запсуске с максимальным значением выходной системы счисления ожидается нулевой код возврата
%PROGRAM% 16 36 1F >nul
if ERRORLEVEL 1 goto err
echo Test 10 passed

rem При запсуске с минимальным значением выходной системы счисления ожидается нулевой код возврата
%PROGRAM% 5 2 11 >nul
if ERRORLEVEL 1 goto err
echo Test 11 passed

rem При запуске с параметром значения не соответствующим исходной системе счисления ожидается ненулевой код возврата
rem Первый параметр исходной нотации равный 3 не сооветствует значению 13
%PROGRAM% 3 10 13 >nul
if NOT ERRORLEVEL 1 goto err
echo Test 12 passed

rem При запуске с параметром значения не соответствующим исходной системе счисления ожидается ненулевой код возврата
rem Значение uf не соответствует нотации
%PROGRAM% 10 10 uf >nul
if NOT ERRORLEVEL 1 goto err
echo Test 13 passed

rem При запуске с параметром значения не соответствующим исходной системе счисления ожидается ненулевой код возврата
rem Значение - не соответствует нотации
%PROGRAM% 10 10 - >nul
if NOT ERRORLEVEL 1 goto err
echo Test 14 passed

rem При переполнении ожидается ненулевой код возврата
%PROGRAM% 36 10 ZZZZZZ >nul
if NOT ERRORLEVEL 1 goto err
echo Test 15 passed

rem При минимальном значении ожидается нулевой код возврата
%PROGRAM% 36 10 0 >nul
if ERRORLEVEL 1 goto err
echo Test 16 passed

rem При максимальном значении ожидается нулевой код возврата
%PROGRAM% 10 10 2147483647 >nul
if ERRORLEVEL 1 goto err
echo Test 17 passed

rem При следующем после максимального значении ожидается ненулевой код возврата
%PROGRAM% 10 10 2147483648 >nul
if NOT ERRORLEVEL 1 goto err
echo Test 18 passed

rem При значении следующем перед максимальным значением ожидается нулевой код возврата
%PROGRAM% 10 10 2147483646 >nul
if ERRORLEVEL 1 goto err
echo Test 19 passed

rem При минимальном значении ожидается нулевой код возврата
%PROGRAM% 10 10 -2147483647 >nul
if ERRORLEVEL 1 goto err
echo Test 20 passed

rem При следующем перед минимального значении ожидается ненулевой код возврата
%PROGRAM% 10 10 -2147483648 >nul
if NOT ERRORLEVEL 1 goto err
echo Test 21 passed

rem При значении следующем после минимальным значением ожидается нулевой код возврата
%PROGRAM% 10 10 -2147483646 >nul
if ERRORLEVEL 1 goto err
echo Test 22 passed

echo OK
exit 0

:err
echo Program testing failed
exit 1