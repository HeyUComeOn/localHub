print("-----------my configure!")

width   =   480
height  =   320

name    =   "x_mitsui"  --name  =   18

function test01()
    print("I'm test01.")
end

function test02( integ , str)
    print("the num "..integ.." "..str)
end

function test03( integ , str)
    return "我是test03函数","我也是test03函数"
end