rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ��� ������� � ����� ��� ����� ����������� ��������� ��������� ��� ��������
%PROGRAM% param1 param2 param3 >nul
if NOT ERRORLEVEL 1 goto err
echo Test 1 passed

rem ��� ������� � ���������� ����� ��������������� �������� ����� ��������� ��������� ��� ��������
%PROGRAM% missing.file output.txt >nul
if NOT ERRORLEVEL 1 goto err
echo Test 2 passed

rem ��� ������ ��������� 99 ������ ��������� ������� ��� ��������
%PROGRAM% test-data\test99.txt "%TEMP%\output.txt" >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\test99-out.txt >nul
if ERRORLEVEL 1 goto err
echo Test 3 passed

rem ��� ������ ��������� 100 ������ ��������� ������� ��� ��������
%PROGRAM% test-data\test100.txt "%TEMP%\output.txt" >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\test100-out.txt >nul
if ERRORLEVEL 1 goto err
echo Test 4 passed

rem ��� ������ ��������� 101 ������ ��������� ��������� ��� ��������
%PROGRAM% test-data\test101.txt "%TEMP%\output.txt" >nul
if NOT ERRORLEVEL 1 goto err
echo Test 5 passed

rem ��� ������ ��������� 99 ������ ��������� ������� ��� ��������
%PROGRAM% test-data\test99h.txt "%TEMP%\output.txt" >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\test99h-out.txt >nul
if ERRORLEVEL 1 goto err
echo Test 6 passed

rem ��� ������ ��������� 100 ������ ��������� ������� ��� ��������
%PROGRAM% test-data\test100h.txt "%TEMP%\output.txt" >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\test100h-out.txt >nul
if ERRORLEVEL 1 goto err
echo Test 7 passed

rem ��� ������ ��������� 101 ������ ��������� ��������� ��� ��������
%PROGRAM% test-data\test101h.txt "%TEMP%\output.txt" >nul
if NOT ERRORLEVEL 1 goto err
echo Test 8 passed

rem ��� ������ � ������ ��������� 100 ������ ��������� ������� ��� ��������
%PROGRAM% test-data\testMAX.txt "%TEMP%\output.txt" >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\testMAX-out.txt >nul
if ERRORLEVEL 1 goto err
echo Test 9 passed

rem ��� ���������� ����� B ��������� ��������� ��� ��������
%PROGRAM% test-data\testB.txt "%TEMP%\output.txt" >nul
if NOT ERRORLEVEL 1 goto err
echo Test 10 passed

rem ��� ���������� ����� A ��������� ��������� ��� ��������
%PROGRAM% test-data\testA.txt "%TEMP%\output.txt" >nul
if NOT ERRORLEVEL 1 goto err
echo Test 11 passed

rem ��� ����������� ������ ��������� ��������� ��������� ��� ��������
%PROGRAM% test-data\testWall.txt "%TEMP%\output.txt" >nul
if NOT ERRORLEVEL 1 goto err
echo Test 12 passed

rem ��� ���������� ���� ��������� �������� ��� �������� ����
%PROGRAM% test-data\testNoExit.txt "%TEMP%\output.txt" >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\testNoExit.txt >nul
if ERRORLEVEL 1 goto err
echo Test 13 passed

rem ��� ������������ ��������� ��������� � ���������� �������
%PROGRAM% test-data\testDifWidth.txt "%TEMP%\output.txt" >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\testDifWidth-out.txt >nul
if ERRORLEVEL 1 goto err
echo Test 14 passed

rem ��� ������������ ��������� ��������� � ���������� ������� � �������
%PROGRAM% test-data\testDifSize.txt "%TEMP%\output.txt" >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\testDifSize-out.txt >nul
if ERRORLEVEL 1 goto err
echo Test 15 passed

rem ��� ������������ ��������� ��������� � ������� ��������
%PROGRAM% test-data\testDifSize.txt "%TEMP%\output.txt" >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\testDifSize-out.txt >nul
if ERRORLEVEL 1 goto err
echo Test 16 passed

rem ���� ����������� ��������� ������� � ������ ���� ��� ������ ���������
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