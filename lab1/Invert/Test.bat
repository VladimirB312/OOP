rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ��� ������� � ���������� -h ��������� ������� ��� ��������
%PROGRAM% -h >nul
if ERRORLEVEL 1 goto err
echo Test 1 passed

rem ��� ������� � ���������� �������� �� -h � �������������� ������ ��������� ��������� ��� ��������
%PROGRAM% missing.file
if NOT ERRORLEVEL 1 goto err
echo Test 2 passed

rem ��� ������� � ����� ��� 2 ����������� ��������� ��������� ��� ��������
%PROGRAM% matrix.file -h >nul
if NOT ERRORLEVEL 1 goto err
echo Test 3 passed

rem ��� ������� � ������� ������ � ������� ������������ �� �������� �������� ��������� ��������� ��� ��������
%PROGRAM% test-data\matrix-error.txt >nul
if NOT ERRORLEVEL 1 goto err
echo Test 4 passed

rem ��� ������� � ������� ������ � ������� �� ����������� ���������� �������� ��������� ��������� ��� ��������
%PROGRAM% test-data\matrix-not-enough.txt >nul
if NOT ERRORLEVEL 1 goto err
echo Test 5 passed

rem ��� ������� � ������� ������ � ������� ������ ���������� �������� ��������� ��������� ��� ��������
%PROGRAM% test-data\matrix-extra.txt >nul
if NOT ERRORLEVEL 1 goto err
echo Test 6 passed

rem ���� ������������ ������� ����� 0 ��������� ��������� ��� ��������
%PROGRAM% test-data\matrix-null.txt >nul
if NOT ERRORLEVEL 1 goto err
echo Test 7 passed

rem �������� ������������ �������������� ��������� �������
%PROGRAM% test-data\matrix-e.txt >"%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\matrix-e-out.txt >nul
if ERRORLEVEL 1 goto err
echo Test 8 passed

rem �������� ������������ �������������� �������
%PROGRAM% test-data\matrix-ok-1.txt >"%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\matrix-ok-1-out.txt >nul
if ERRORLEVEL 1 goto err
echo Test 9 passed

rem �������� ������������ �������������� ������� � �������������� ����������
%PROGRAM% test-data\matrix-ok-2.txt >"%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\matrix-ok-2-out.txt >nul
if ERRORLEVEL 1 goto err
echo Test 10 passed

rem �������� ������� �������������� ������� �������
%PROGRAM% test-data\matrix-0.txt >"%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
echo Test 11 passed

echo OK
exit 0

:err
echo Program testing failed
exit 1