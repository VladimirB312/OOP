rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ��� ������� ��� ���������� ��������� ��������� ��� ��������
%PROGRAM% >nul
if NOT ERRORLEVEL 1 goto err
echo Test 1 passed

rem ��� ������� � ������ ���������� ���������� ��������� ��������� ��� ��������
%PROGRAM% str23ing 16 1F >nul
if NOT ERRORLEVEL 1 goto err
echo Test 2 passed

rem ��� ������� �� ������ ���������� ���������� ��������� ��������� ��� ��������
%PROGRAM% 16 st65ring 1F >nul
if NOT ERRORLEVEL 1 goto err
echo Test 3 passed

rem ��� ������� �� ��������� �������� ������� ��������� ������ 36 ��������� ��������� ��� ��������
%PROGRAM% 37 3 1F >nul
if NOT ERRORLEVEL 1 goto err
echo Test 4 passed

rem ��� ������� �� ��������� �������� ������� ��������� ������ 2 ��������� ��������� ��� ��������
%PROGRAM% 1 3 0 >nul
if NOT ERRORLEVEL 1 goto err
echo Test 5 passed

rem ��� �������� � ������������ ��������� �������� ������� ��������� ��������� ������� ��� ��������
%PROGRAM% 36 3 1F >nul
if ERRORLEVEL 1 goto err
echo Test 6 passed

rem ��� �������� � ����������� ��������� �������� ������� ��������� ��������� ������� ��� ��������
%PROGRAM% 2 3 11 >nul
if ERRORLEVEL 1 goto err
echo Test 7 passed

rem ��� ������� �� ��������� �������� ������� ��������� ������ 36 ��������� ��������� ��� ��������
%PROGRAM% 16 37 1F >nul
if NOT ERRORLEVEL 1 goto err
echo Test 8 passed

rem ��� ������� �� ��������� �������� ������� ��������� ������ 2 ��������� ��������� ��� ��������
%PROGRAM% 4 1 0 >nul
if NOT ERRORLEVEL 1 goto err
echo Test 9 passed

rem ���� �������� � ������������ ��������� �������� ������� ��������� ��������� ������� ��� ��������
%PROGRAM% 16 36 1F >nul
if ERRORLEVEL 1 goto err
echo Test 10 passed

rem ��� �������� � ����������� ��������� �������� ������� ��������� ��������� ������� ��� ��������
%PROGRAM% 5 2 11 >nul
if ERRORLEVEL 1 goto err
echo Test 11 passed

rem ��� ������� � ���������� �������� �� ��������������� �������� ������� ��������� ��������� ��������� ��� ��������
rem ������ �������� �������� ������� ������ 3 �� ������������ �������� 13
%PROGRAM% 3 10 13 >nul
if NOT ERRORLEVEL 1 goto err
echo Test 12 passed

rem ��� ������� � ���������� �������� �� ��������������� �������� ������� ��������� ��������� ��������� ��� ��������
rem �������� uf �� ������������� �������
%PROGRAM% 10 10 uf >nul
if NOT ERRORLEVEL 1 goto err
echo Test 13 passed

rem ��� ������� � ���������� �������� �� ��������������� �������� ������� ��������� ��������� ��������� ��� ��������
rem �������� - �� ������������� �������
%PROGRAM% 10 10 - >nul
if NOT ERRORLEVEL 1 goto err
echo Test 14 passed

rem ��� ������������ ��������� ��������� ��� ��������
%PROGRAM% 36 10 ZZZZZZ >nul
if NOT ERRORLEVEL 1 goto err
echo Test 15 passed

rem ��� ����������� �������� ��������� ������� ��� ��������
%PROGRAM% 36 10 0 >nul
if ERRORLEVEL 1 goto err
echo Test 16 passed

rem ��� ������������ �������� ��������� ������� ��� ��������
%PROGRAM% 10 10 2147483647 >nul
if ERRORLEVEL 1 goto err
echo Test 17 passed

rem ��� ��������� ����� ������������� �������� ��������� ��������� ��� ��������
%PROGRAM% 10 10 2147483648 >nul
if NOT ERRORLEVEL 1 goto err
echo Test 18 passed

rem ��� �������� ��������� ����� ������������ ��������� ��������� ������� ��� ��������
%PROGRAM% 10 10 2147483646 >nul
if ERRORLEVEL 1 goto err
echo Test 19 passed

rem ��� ����������� �������� ��������� ������� ��� ��������
%PROGRAM% 10 10 -2147483647 >nul
if ERRORLEVEL 1 goto err
echo Test 20 passed

rem ��� ��������� ����� ������������ �������� ��������� ��������� ��� ��������
%PROGRAM% 10 10 -2147483648 >nul
if NOT ERRORLEVEL 1 goto err
echo Test 21 passed

rem ��� �������� ��������� ����� ����������� ��������� ��������� ������� ��� ��������
%PROGRAM% 10 10 -2147483646 >nul
if ERRORLEVEL 1 goto err
echo Test 22 passed

echo OK
exit 0

:err
echo Program testing failed
exit 1