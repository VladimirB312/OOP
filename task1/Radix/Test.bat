rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ��� ������� ��� ���������� ��������� ������� ��� ��������
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

rem ���� ��������� �������� ��� �������� ������� ��������� ������� �� ������� �� 2 �� 36 ��������� ��������� ��� ��������
%PROGRAM% 37 3 1F >nul
if NOT ERRORLEVEL 1 goto err
echo Test 4 passed

rem ��� ������� � ���������� �������� �� ��������������� �������� ������� ��������� ��������� ��������� ��� ��������
rem ������ �������� �������� ������� ������ 3 �� ������������ �������� 13
%PROGRAM% 3 10 13 >nul
if NOT ERRORLEVEL 1 goto err
echo Test 5 passed

echo OK
exit 0

:err
echo Program testing failed
exit 1