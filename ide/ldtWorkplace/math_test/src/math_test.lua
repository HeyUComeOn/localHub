--數學庫可以直接使用，源碼已經集成

--獲取系統時間，我們通過os.time，在單機做每日登錄的時候就可以獲取當前時間和本機記錄時間的對比來判斷是否需要提示用戶可以領取獎勵
--os.time返回的是从1970年x月x日到现在经过的秒数，os.date返回的是按照一定格式输出的日期字符串或table
print(os.time())
print(os.date())

--随机数
--有三种用法： 无参调用， 产生 （0,1） 之间的浮点随机数； 只有参数 n， 产生 1-n 之间的整数； 有两个参数 n， m， 产生 n-m 之间的随机整数
math.randomseed(os.time())--设置随机种子
print(math.random())
print(math.random(3))
print(math.random(1,10))


print(math.sin(3.14/6))

math.deg(3.14/6)--弧度轉化爲角度
math.rad(30)--角度轉化爲弧度

print(math.sin(math.rad(30)))

local y =2.3
print(math.floor(y))--向下取整
print(math.ceil(y))--向上取整

print(math.max(6,6,8.78))    --多值取最大
--math.min(y,...)

