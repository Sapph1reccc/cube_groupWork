#!/bin/sh
killall -9 envset_proc
rm instance/server/lib/RECORD_DEFINE-RECORD.lib	#删除lib记录便于观察
rm -f instance/server/aspect_policy.cfg
rm -f instance/dianzhu/aspect_policy.cfg
rm -f instance/wuliu/aspect_policy.cfg
rm -f instance/guke001/aspect_policy.cfg
rm -f instance/guke002/aspect_policy.cfg
rm -f instance/kefu/aspect_policy.cfg

yes|cp instance/server/plugin_config.cfg.access instance/server/plugin_config.cfg
yes|cp instance/server/sys_config.cfg.label instance/server/sys_config.cfg
yes|cp instance/server/router_policy.cfg.record instance/server/router_policy.cfg
yes|cp instance/server/aspect_policy.cfg.access instance/server/aspect_policy.cfg

yes|cp instance/dianzhu/sys_config.cfg.record instance/dianzhu/sys_config.cfg
yes|cp instance/dianzhu/router_policy.cfg.record instance/dianzhu/router_policy.cfg

yes|cp instance/wuliu/sys_config.cfg.record instance/dianzhu/sys_config.cfg
yes|cp instance/wuliu/router_policy.cfg.record instance/dianzhu/router_policy.cfg

yes|cp instance/kefu/sys_config.cfg.record instance/dianzhu/sys_config.cfg
yes|cp instance/kefu/router_policy.cfg.record instance/dianzhu/router_policy.cfg

yes|cp instance/guke001/sys_config.cfg.record instance/dianzhu/sys_config.cfg
yes|cp instance/guke001/router_policy.cfg.record instance/dianzhu/router_policy.cfg

yes|cp instance/guke002/sys_config.cfg.record instance/dianzhu/sys_config.cfg
yes|cp instance/guke002/router_policy.cfg.record instance/dianzhu/router_policy.cfg
sleep 1

sh run_cube.sh exec_def/_user_server.def &
sleep 1
sh run_cube.sh exec_def/_guke001_client.def login.msg write.msg write1.msg read.msg &
sleep 4
sh run_cube.sh exec_def/_guke002_client.def login.msg write.msg write1.msg read.msg &
sleep 4
sh run_cube.sh exec_def/_kefu_client.def login.msg write.msg write1.msg & #read.msg &
sleep 4
sh run_cube.sh exec_def/_wuliu_client.def login.msg write.msg read.msg &
sleep 4
sh run_cube.sh exec_def/_dianzhu_client.def login.msg write.msg write1.msg read.msg
