目前进展：
=
杨瑞宸（访控）：
-
  1. 基本访控应该莫得问题了，多顾客越权读写问题限制了；
  2. 目前每次写的订单号就是登陆姓名+当前系统时间（精确到秒）+物流公司（目前只有一个），格式gukexxx__YYYYMMDD__YT；
  3. 记录项先后顺序问题解决。
  4. *登陆挑战/绕过登陆问题需要讨论 ——目前没有登陆挑战，没有login.msg只能先段错误，但不知道怎么解决这个段错误来给用户显示报错。————你这个的意思是如果没有login.msg就会报错吗？*
  5. 加上了空订单号的判断，如果读空订单不会显示一堆""，而是直接显示提醒；
  
----------------------------------------------------
杜方浩（界面）：
-
  1.登录界面的messag.log文件可以解析成登录使用的login.msg文件；

  2.顾客购买界面的message.log文件可以解析成写操作使用的write.msg文件；

  3.所有界面已经基本设计完成，但根据角色进行切换的功能还需对echo模块进行改造后才能实现，但不知道为什么在echo_plugin文件夹的.c文件中进行修改无法对返回消息进行更改，待周五询问过老师后再做处理。

------------------------------------------------------------
李洪超（测试）：
-
访问控制测试：
  1. 当第一个顾客填写的第一个订单信息时（只能填写一个记录项），但是其他记录项的值都会发生更改
  如：只填写了Goods_name却出现下面情况：
“Goods_name":"顾客001写货物数量测试","Goods_num":"guke001__20200515183321","Rec_addr":"1写货物数量测试","Deli_addr":"","isSent":"","isReceived":"","Goods_addr":"","isFinished":"����"
只填写了Goods_num却出现下面情况：
"Goods_name":"�","Goods_num":"顾客002写货物数量测试","Rec_addr":"测试","Deli_addr":"","isSent":"����","isReceived":"��������","Goods_addr":"","isFinished":""
  并且只会发生在第一个顾客上，后面的顾客并无影响。

挑战登录，安全标记，读写，访问控制模块连接到一起：
执行脚本是record_access1.sh，运行前需要看一下exec_def里面的文件地址对吗。如果运行不了，先把全部c文件编译一下。其余名字带有1的脚本和以前不是挑战登录时的脚本效果一样。
不登录可以越过访问控制的问题在使用挑战登录以后依旧没有解决，所以还是需要在访问控制模块中进行限制。
----------------------------------------------------------------
徐琮坤（可信）：
-



-----------------------------------------------------------------
