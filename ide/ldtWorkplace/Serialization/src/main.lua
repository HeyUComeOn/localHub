function serialization( o )
  if(type(o)=="number")then
    io.write( o )
  elseif type(o)=="string" then
    io.write("[===[",o,"]===]")

  else

  end

end

a = 'a "program lua" \\'
print (string.format("%q",a))--�����ȷ����
--�����޻���tabel��ҳĩ�н���
function N_serialization(o)
  if type(o)=="number" then
    io.write(o)
  elseif type(o)=="string" then
    io.write(string.format("%q",o))
  elseif type(o)=="table" then
    io.write("{\n")
    for key, var in pairs(o) do
      io.write(" ",key," = ")
      N_serialization(var)
      io.write(",\n")
    end
    io.write("}\n")
  end
end
N_serialization({3,"lua","3sfs3",{123,"jj"}})

--[[
local a = {}
local b = {}
a.next = b
b.next = a
a��b֮������໥���ù�ϵ�ںܶ������� 
�����Ľṹ��ʹa��b�޷���ϵͳִ�е���������������
����lua�������ǿ��Ի��յ�
�����ϣ�����Ա������׵Ļ��� 
����ʹ��lua��������
]]
