--printĬ���л���
io.write("sin(3)=",math.sin(3),"\n")

io.write(string.format("sin(3)=%.4f\n",math.sin(3)))
--io.write("12"..12..1)--����д��
io.write("12",12,1,"\n")
s=12
f=1
print("12"..s..f)

--��ȡ
--*all ��ʾ��ȡ�����ļ�
--*line ��ʾ��ȡ��һ��
--*number ��ʾ��ȡ��һ�е�һ������
--<num> ��ȡһ��������<num> �������ַ����ַ���

tt = io.read("*all")

print(tt)

local f =assert(io.open("ff.lua",'r'))
local t =f:read("*all")
print(t)
f:close()