--1.string.find��ʹ��
print("-------------1---------------")
local testStr="HelloLua,HelloWorld"
j,k=string.find(testStr,"Hello")
print(j,k)-->1    5

i = string.find(testStr,"ok")
print(i)-->nil

--2.string.match()������ʹ��
print("-------------2---------------")
m= string.match(testStr,"Hello")--�Ƿ���Ŀ���ַ�������������nil
print(m)

--3.string.sub��ȡ�ַ���ʹ��*
--��   1->-1��ʾ��ȡȫ���ַ��� -1->0��ȡ���ַ�����
print("-------------3---------------")
s=string.sub(testStr,1,1)
print(s)

--4.�滻
print("-------------4---------------")
n=string.gsub(testStr,"HelloLua","HelloCpp")
print(n)
print(testStr)-- ����ԭ���ַ���

--5.ɾ���ַ���
print("-------------5---------------")
t=testStr;
l=nil--�ײ��ͷ��ڴ�
print(l)

--���滻ʵ��
s=string.gsub(testStr,"Lua","")--�ѵڶ��������滻Ϊ������
print(s)