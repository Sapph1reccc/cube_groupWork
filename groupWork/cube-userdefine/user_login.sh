#!/bin/sh
killall -9 envset_proc
rm instance/server/output.txt
rm -f instance/server/aspect_policy.cfg
rm -f instance/guke001/aspect_policy.cfg
yes|cp instance/server/plugin_config.cfg.user instance/server/plugin_config.cfg
yes|cp instance/server/sys_config.cfg.user instance/server/sys_config.cfg
yes|cp instance/server/router_policy.cfg.user instance/server/router_policy.cfg

yes|cp instance/guke001/sys_config.cfg.user instance/guke001/sys_config.cfg
yes|cp instance/guke001/router_policy.cfg.user instance/guke001/router_policy.cfg
sleep 1

#/root/groupWork/cube-1.3/example/webmsgecho/jiexilogin

sh run_cube.sh exec_def/_user_server.def &
sleep 1
sh run_cube.sh exec_def/_guke001_client.def login.msg
