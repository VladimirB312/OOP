rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ��� ������� ��� ���������� ��������� ��������� ��� ��������
%PROGRAM% >nul
if NOT ERRORLEVEL 1 goto err
echo Test 1 passed

rem ��� ������� � ����������� ���������� ������ 4 ��������� ��������� ��� ��������
%PROGRAM% crypt input output 100 extraarg >nul
if NOT ERRORLEVEL 1 goto err
echo Test 2 passed

rem ��� ������� � �������� ����� ���������� ��������� ��������� ��� ��������
%PROGRAM% invalidtype input output 100 >nul
if NOT ERRORLEVEL 1 goto err
echo Test 3 passed

rem ��� ������� � ������ ������ 0 ��������� ��������� ��� ��������
%PROGRAM% crypt test-data/input.txt "%TEMP%\output.txt" -1 >nul
if NOT ERRORLEVEL 1 goto err
echo Test 4 passed

rem ��� ������� � ������ ������ 0 ��������� ������� ��� ��������
%PROGRAM% crypt test-data/input.txt "%TEMP%\output.txt" 0 >nul
if ERRORLEVEL 1 goto err
echo Test 5 passed

rem ��� ������� � ������ ������ 255 ��������� ������� ��� ��������
%PROGRAM% crypt test-data/input.txt "%TEMP%\output.txt" 255 >nul
if ERRORLEVEL 1 goto err
echo Test 6 passed

rem ��� ������� � ������ ������ 256 ��������� ��������� ��� ��������
%PROGRAM% crypt test-data/input.txt "%TEMP%\output.txt" 256 >nul
if NOT ERRORLEVEL 1 goto err
echo Test 7 passed

rem ��� ������� � ������ crypt � ������ 12 ������������ ���� ������ ��������� � ��������
%PROGRAM% crypt test-data/fox.txt "%TEMP%\fox-encoded.txt" 12 >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox-encoded.txt" test-data\fox-encoded.txt >nul
if ERRORLEVEL 1 goto err
echo Test 8 passed

rem ��� ������� � ������ decrypt � ������ 12 ������������� ���� ������ ��������� � ��������
%PROGRAM% decrypt "%TEMP%\fox-encoded.txt" "%TEMP%\fox.txt"  12 >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" test-data\fox.txt >nul
if ERRORLEVEL 1 goto err
echo Test 9 passed

rem ��� ������� ������� � ������ crypt, � ����� � ������ decrypt � ������ 132 �������� ���� ������ ��������� � ��������
%PROGRAM% crypt test-data/fox.txt "%TEMP%\fox-encoded.txt" 132 >nul
if ERRORLEVEL 1 goto err
%PROGRAM% decrypt "%TEMP%\fox-encoded.txt" "%TEMP%\fox.txt" 132 >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" test-data\fox.txt >nul
if ERRORLEVEL 1 goto err
echo Test 10 passed

rem ��� ������� ������� � ������ crypt, � ����� � ������ decrypt � ������ 0 �������� ���� ������ ��������� � ��������
%PROGRAM% crypt test-data/fox.txt "%TEMP%\fox-encoded.txt" 0 >nul
if ERRORLEVEL 1 goto err
%PROGRAM% decrypt "%TEMP%\fox-encoded.txt" "%TEMP%\fox.txt" 0 >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" test-data\fox.txt >nul
if ERRORLEVEL 1 goto err
echo Test 11 passed

rem ��� ������� ������� � ������ crypt, � ����� � ������ decrypt � ������ 255 �������� ���� ������ ��������� � ��������
%PROGRAM% crypt test-data/fox.txt "%TEMP%\fox-encoded.txt" 255 >nul
if ERRORLEVEL 1 goto err
%PROGRAM% decrypt "%TEMP%\fox-encoded.txt" "%TEMP%\fox.txt" 255 >nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" test-data\fox.txt >nul
if ERRORLEVEL 1 goto err
echo Test 11 passed

rem ��� ������� ������� � ������ crypt, � ����� � ������ decrypt � ������ ������ �������� ���� ������ ��������� � ��������
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