目前进展：
=
杨瑞宸（访控）：
-
  1. 基本访控应该莫得问题了，多顾客越权读写问题限制了；
  2. 目前每次写的订单号就是登陆姓名+当前系统时间（精确到秒）+物流公司（目前只有一个），格式gukexxx__YYYYMMDD__YT；
  **3. 还没有加记录项先后顺序问题。**
  *（等，应该好解决）4. 登陆挑战/绕过登陆问题需要讨论 ——目前没有登陆挑战，没有login.msg只能先段错误，但不知道怎么解决这个段错误来给用户显示报错。————你这个的意思是如果没有login.msg就会报错吗？*
  5. 加上了空订单号的判断，如果读空订单不会显示一堆""，而是直接显示提醒；
  
----------------------------------------------------
杜方浩（界面）：
-
  1. 只有简单页面，无法实现交互

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
  2. 当店主端不登录时同样可以读写，并且可以读写任意数据（其他用户也可以通过同样的手段越过访问控制）。————同杨瑞宸-4


----------------------------------------------------------------
徐琮坤（可信）：
-



-----------------------------------------------------------------
