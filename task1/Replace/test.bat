rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ��� ������� ��� ���������� ��������� ��������� ��� ��������
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err
echo Test 1 passed

rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������  �������� �������� ����� 
%PROGRAM% test-data\fox.txt "%TEMP%\fox.txt" bird cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" test-data\fox.txt >nul
if ERRORLEVEL 1 goto err
echo Test 2 passed

rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������
%PROGRAM% test-data\fox.txt "%TEMP%\fox.txt" dog cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" test-data\fox-replace-dog-with-cat.txt >nul
if ERRORLEVEL 1 goto err
echo Test 3 passed

rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������
%PROGRAM% test-data\digits.txt "%TEMP%\digits.txt" 1231234 XYZ
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\digits.txt" test-data\digits-replace-1231234-with-XYZ.txt >nul
if ERRORLEVEL 1 goto err
echo Test 4 passed

echo OK
exit 0

:err
echo Program testing failed
exit 1