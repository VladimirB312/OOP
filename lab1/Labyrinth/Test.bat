rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem При запуске с более чем двумя параметрами ожидается ненулевой код возврата
%PROGRAM% param1 param2 param3 >nul
if NOT ERRORLEVEL 1 goto err
echo Test 1 passed

rem При запуске с параметром имени несуществующего входного файла ожидается ненулевой код возврата
%PROGRAM% missing.file output.txt >nul
if NOT ERRORLEVEL 1 goto err
echo Test 2 passed

rem При ширине лабиринта 99 клеток ожидается нулевой код возврата
%PROGRAM% test-data\test99.txt "%TEMP%\output.txt" >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\test99-out.txt >nul
if ERRORLEVEL 1 goto err
echo Test 3 passed

rem При ширине лабиринта 100 клеток ожидается нулевой код возврата
%PROGRAM% test-data\test100.txt "%TEMP%\output.txt" >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\test100-out.txt >nul
if ERRORLEVEL 1 goto err
echo Test 4 passed

rem При ширине лабиринта 101 клетка ожидается ненулевой код возврата
%PROGRAM% test-data\test101.txt "%TEMP%\output.txt" >nul
if NOT ERRORLEVEL 1 goto err
echo Test 5 passed

rem При высоте лабиринта 99 клеток ожидается нулевой код возврата
%PROGRAM% test-data\test99h.txt "%TEMP%\output.txt" >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\test99h-out.txt >nul
if ERRORLEVEL 1 goto err
echo Test 6 passed

rem При высоте лабиринта 100 клеток ожидается нулевой код возврата
%PROGRAM% test-data\test100h.txt "%TEMP%\output.txt" >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\test100h-out.txt >nul
if ERRORLEVEL 1 goto err
echo Test 7 passed

rem При высоте лабиринта 101 клетка ожидается ненулевой код возврата
%PROGRAM% test-data\test101h.txt "%TEMP%\output.txt" >nul
if NOT ERRORLEVEL 1 goto err
echo Test 8 passed

rem При высоте и ширине лабиринта 100 клеток ожидается нулевой код возврата
%PROGRAM% test-data\testMAX.txt "%TEMP%\output.txt" >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\testMAX-out.txt >nul
if ERRORLEVEL 1 goto err
echo Test 9 passed

rem При отсутствии точки B ожидается ненулевой код возврата
%PROGRAM% test-data\testB.txt "%TEMP%\output.txt" >nul
if NOT ERRORLEVEL 1 goto err
echo Test 10 passed

rem При отсутствии точки A ожидается ненулевой код возврата
%PROGRAM% test-data\testA.txt "%TEMP%\output.txt" >nul
if NOT ERRORLEVEL 1 goto err
echo Test 11 passed

rem При незамкнутых стенах лабиринта ожидается ненулевой код возврата
%PROGRAM% test-data\testWall.txt "%TEMP%\output.txt" >nul
if NOT ERRORLEVEL 1 goto err
echo Test 12 passed

rem При отсутствии пути выводится лабиринт без указания пути
%PROGRAM% test-data\testNoExit.txt "%TEMP%\output.txt" >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\testNoExit.txt >nul
if ERRORLEVEL 1 goto err
echo Test 13 passed

rem При правильности обработки лабиринта с меняющейся шириной
%PROGRAM% test-data\testDifWidth.txt "%TEMP%\output.txt" >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\testDifWidth-out.txt >nul
if ERRORLEVEL 1 goto err
echo Test 14 passed

rem При правильности обработки лабиринта с меняющейся шириной и высотой
%PROGRAM% test-data\testDifSize.txt "%TEMP%\output.txt" >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\testDifSize-out.txt >nul
if ERRORLEVEL 1 goto err
echo Test 15 passed

rem При правильности обработки лабиринта с пустыми строками
%PROGRAM% test-data\testDifSize.txt "%TEMP%\output.txt" >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\testDifSize-out.txt >nul
if ERRORLEVEL 1 goto err
echo Test 16 passed

rem Тест максимально возможной глубины и ширины пути при обходе лабиринта
%PROGRAM% test-data\test-max-load.txt "%TEMP%\output.txt" >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\test-max-load-out.txt >nul
if ERRORLEVEL 1 goto err
echo Test 17 passed

echo OK
exit 0

:err
echo Program testing failed
exit 1