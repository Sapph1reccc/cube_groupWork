目前进展：
=
杨瑞宸（访控）：
-
  1. 基本访控完成，多顾客越权读写已限制；
  2. 目前每次写的订单号就是登陆姓名+当前系统时间（精确到秒）+物流公司（随便多少个），格式gukexxx__YYYYMMDD__物流；
  3. 记录项先后顺序问题解决；
  4. 加上了订单号记录项全空的判断，如果读全空订单不会显示一堆""，而是直接显示提醒；  
  - 0523  
  1. 和界面完成了部分结合，更改了部分代码来配合；  
  - 0525  
  1. 订单信息有的segment会出现乱码（无论第一个还是非第一个）是中文问题，将记录项全部改为英文就好了；
  2. 所有角色无法读根本不存在的订单号；
  3. 客服无法写不存在的订单号，写就直接段错误。此问题界面会直接读取我所提供的合法订单号，所以和界面全部完成结合后就不会存在段错误问题了。
  - 0527  
  1. 完成挑战登录。
  - 0529 & 0601 
  1. 完善加上登陆挑战后和界面结合的bug（安全标记在解析23后不用登陆直接写仍然存在）
  - 0605
  1. 和界面结合，删掉了不少东西（半成品状态）；
  2. 第一个订单乱码解决，而且现在用不到命令行来看结果；
  - 待解决
  1. 和界面进一步结合。
  
----------------------------------------------------
杜方浩（界面）：
-
  0.guke001使用端口13999，dianzhu使用端口14999，kefu使用端口15999，yuantong使用端口16999；

  1.写操作时，会出现段错误；

  2.由于写有问题，读操作暂时未完成；

  3.目前已经将index.html和CusShop.html开始与cube接入，但CusShop.html在购买东西（即写操作时出现错误），其他html还没更改消息格式

目前主要的问题是路由的配置和消息格式的匹配

------------------------------------------------------------
李洪超（测试）：
-
访问控制测试：
  1. 不登录可以越过访问控制的问题在使用挑战登录以后依旧没有解决，所以还是需要在访问控制模块中进行限制。
  
  2.使用错误的用户名和密码登录，会出现段错误，但message.log文件中返回信息正确，gdb调试发现是user_login.c中的proc_login_response函数中if(return_info->return_code != CHALLENGE)中的代码产生了段错误，但并知道该如何修改。
    
----------------------------------------------------------------
徐琮坤（可信）：
-



-----------------------------------------------------------------
