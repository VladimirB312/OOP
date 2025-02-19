rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамл€ющих кавычек (если они были)

rem ѕеременна€ PROGRAM будет хранить первый аргумент командной строки заключЄнный в кавычки
set PROGRAM="%~1"

rem ѕри запуске с более чем двум€ параметрами ожидаетс€ ненулевой код возврата
%PROGRAM% param1 param2 param3 >nul
if NOT ERRORLEVEL 1 goto err
echo Test 1 passed

rem ѕри запуске с параметром имени несуществующего входного файла ожидаетс€ ненулевой код возврата
%PROGRAM% missing.file output.txt >nul
if NOT ERRORLEVEL 1 goto err
echo Test 2 passed

echo OK
exit 0

:err
echo Program testing failed
exit 1