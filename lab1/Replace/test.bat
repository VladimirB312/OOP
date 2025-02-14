rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ��� ������� � ����� ���������� �������� �� -h ��������� ��������� ��� ��������
%PROGRAM% -v >nul
if NOT ERRORLEVEL 1 goto err
echo Test 1 passed

rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������
rem � ������ ���������� ������� ������ �� ������� �����, �������� ���� ������ ���� ����� ��������
%PROGRAM% test-data\fox.txt "%TEMP%\fox.txt" bird cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" test-data\fox.txt >nul
if ERRORLEVEL 1 goto err
echo Test 2 passed

rem ���� ������ �� ������� ����� ������ "dog" �� "cat"
%PROGRAM% test-data\fox.txt "%TEMP%\fox.txt" dog cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" test-data\fox-replace-dog-with-cat.txt >nul
if ERRORLEVEL 1 goto err
echo Test 3 passed

rem ���� ������ �� ������� ����� ������ �������� ������ "fox" �� "cat"
%PROGRAM% test-data\fox-first.txt "%TEMP%\fox-first.txt" fox cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox-first.txt" test-data\fox-first-replace.txt >nul
if ERRORLEVEL 1 goto err
echo Test 4 passed

rem ���� ������ �� ������� ����� ������ "1231234" �� "XYZ"
%PROGRAM% test-data\digits.txt "%TEMP%\digits.txt" 1231234 XYZ
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\digits.txt" test-data\digits-replace-1231234-with-XYZ.txt >nul
if ERRORLEVEL 1 goto err
echo Test 5 passed

rem ���� ������ �� ������� �����, ��������� �� ���������� �����, ������ "brown" �� "red"
%PROGRAM% test-data\multiline.txt "%TEMP%\multiline.txt" brown red
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\multiline.txt" test-data\multiline-replace.txt >nul
if ERRORLEVEL 1 goto err
echo Test 6 passed

rem ���� ������ � � ������������ ���������� ������� ������ � ������-���������� "ma" "mama"
%PROGRAM% test-data\mama.txt "%TEMP%\mama.txt" ma mama
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\mama.txt" test-data\mama-replace.txt >nul
if ERRORLEVEL 1 goto err
echo Test 7 passed

rem ��� ����������, ��������� �����������, �������� �����, ��������� ������ ������� ��������� ��� ��������
%PROGRAM% test-data\missing.txt "%TEMP%\mama.txt" ma mama >nul
if NOT ERRORLEVEL 1 goto err
echo Test 8 passed

echo OK
exit 0

:err
echo Program testing failed
exit 1