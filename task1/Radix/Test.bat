rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem При запуске без параметров ожидается нулевой код возврата
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

rem Если параметры исходной или выходной системы счисления выходят за пределы от 2 до 36 ожидается ненулевой код возврата
%PROGRAM% 37 3 1F >nul
if NOT ERRORLEVEL 1 goto err
echo Test 4 passed

rem При запуске с параметром значения не соответствующим исходной системе счисления ожидается ненулевой код возврата
rem Первый параметр исходной нотации равный 3 не сооветствует значению 13
%PROGRAM% 3 10 13 >nul
if NOT ERRORLEVEL 1 goto err
echo Test 5 passed

echo OK
exit 0

:err
echo Program testing failed
exit 1