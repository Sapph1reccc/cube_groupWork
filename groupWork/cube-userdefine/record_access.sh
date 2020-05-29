#!/bin/sh
killall -9 envset_proc
rm -f instance/server/aspect_policy.cfg
rm -f instance/guke003/aspect_policy.cfg
yes|cp instance/server/plugin_config.cfg.access instance/server/plugin_config.cfg
yes|cp instance/server/sys_config.cfg.label instance/server/sys_config.cfg
yes|cp instance/server/router_policy.cfg.record instance/server/router_policy.cfg
yes|cp instance/server/aspect_policy.cfg.access instance/server/aspect_policy.cfg

yes|cp instance/guke003/sys_config.cfg.record instance/guke003/sys_config.cfg
yes|cp instance/guke003/router_policy.cfg.record instance/guke003/router_policy.cfg
sleep 1

sh run_cube.sh exec_def/_user_server.def &
sleep 1
sh run_cube.sh exec_def/_guke003_user.def login.msg write.msg read.msg


