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

echo OK
exit 0

:err
echo Program testing failed
exit 1