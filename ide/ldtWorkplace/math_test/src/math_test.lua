--���W�����ֱ��ʹ�ã�Դ�a�ѽ�����

--�@ȡϵ�y�r�g���҂�ͨ�^os.time���چΙC��ÿ�յ�䛵ĕr��Ϳ��ԫ@ȡ��ǰ�r�g�ͱ��Cӛ䛕r�g�Č��ȁ��Д��Ƿ���Ҫ��ʾ�Ñ������Iȡ����
--os.time���ص��Ǵ�1970��x��x�յ����ھ�����������os.date���ص��ǰ���һ����ʽ����������ַ�����table
print(os.time())
print(os.date())

--�����
--�������÷��� �޲ε��ã� ���� ��0,1�� ֮��ĸ���������� ֻ�в��� n�� ���� 1-n ֮��������� ���������� n�� m�� ���� n-m ֮����������
math.randomseed(os.time())--�����������
print(math.random())
print(math.random(3))
print(math.random(1,10))


print(math.sin(3.14/6))

math.deg(3.14/6)--�����D�����Ƕ�
math.rad(30)--�Ƕ��D��������

print(math.sin(math.rad(30)))

local y =2.3
print(math.floor(y))--����ȡ��
print(math.ceil(y))--����ȡ��

print(math.max(6,6,8.78))    --��ֵȡ���
--math.min(y,...)

