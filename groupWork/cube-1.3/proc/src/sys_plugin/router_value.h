#ifndef NAMEVALUE
#define NAMEVALUE

static NAME2VALUE message_flow_valuelist[] = 
{
    {"INIT",MSG_FLOW_INIT},
    {"LOCAL",MSG_FLOW_LOCAL},
    {"DELIVER",MSG_FLOW_DELIVER},
    {"QUERY",MSG_FLOW_QUERY},
    {"RESPONSE",MSG_FLOW_RESPONSE},
    {"ASPECT",MSG_FLOW_ASPECT},
    {"ASPECT_LOCAL",MSG_FLOW_ASPECT_LOCAL},
    {"ASPECT_RETURN",MSG_FLOW_ASPECT_RETURN},
    {"WAIT",MSG_FLOW_WAIT},
    {"TRANS",MSG_FLOW_TRANS},
    {"DRECV",MSG_FLOW_DRECV},
    {"QRECV",MSG_FLOW_QRECV},
    {"FINISH",MSG_FLOW_FINISH},
//  {"ERROR",MSG_FLOW_ERROR},
    {NULL,0}
};

static NAME2VALUE match_entity_valuelist[] = 
{
	{"MESSAGE",DISPATCH_MATCH_MSG},
	{"MESSAGE_RECORD",DISPATCH_MATCH_MSG_RECORD},
	{"MESSAGE_EXPAND",DISPATCH_MATCH_MSG_EXPAND},
	{"PROC",DISPATCH_MATCH_PROC},
	{NULL,0}
};

static NAME2VALUE message_flag_valuelist[] = 
{
	{"CRYPT",MSG_FLAG_CRYPT},
	{"SIGN",MSG_FLAG_SIGN},
	{"ZIP",MSG_FLAG_SIGN},
	{"VERIFY",MSG_FLAG_VERIFY},
	{"RESPONSE",MSG_FLAG_RESPONSE},
	{NULL,0}
};

{
	{"MAIN",PROC_TYPE_MAIN},
	{"CONN",PROC_TYPE_CONN},
	{"ROUTER",PROC_TYPE_ROUTER},
	{"PORT",PROC_TYPE_PORT},
	{"MONITOR",PROC_TYPE_MONITOR},
	{"DECIDE",PROC_TYPE_DECIDE},
	{"CONTROL",PROC_TYPE_CONTROL},
	{NULL,0}
};

static NAME2VALUE match_rule_op_valuelist[] =
{
    {"AND",MATCH_OP_AND},
    {"OR",MATCH_OP_OR},
    {"NOT",MATCH_OP_NOT},
    {"ERR",MATCH_OP_ERR},
    {NULL,0}
};

static NAME2VALUE message_area_valuelist[] =
{
    {"HEAD",MATCH_AREA_HEAD},
    {"RECORD",MATCH_AREA_RECORD},
    {"EXPAND",MATCH_AREA_EXPAND},
    {"ERR",MATCH_AREA_ERR},
    {NULL,0}
};

static NAME2VALUE message_target_type_valuelist[] =
{
    {"LOCAL",MSG_TARGET_LOCAL},
    {"PORT",MSG_TARGET_PORT},
    {"NAME",MSG_TARGET_NAME},
    {"UUID",MSG_TARGET_UUID},
    {"RECORD",MSG_TARGET_RECORD},
    {"EXPAND",MSG_TARGET_EXPAND},
    {"SPLIT",MSG_TARGET_SPLIT},
    {"CONN",MSG_TARGET_CONN},
    {"MIXUUID",MSG_TARGET_MIXUUID},
    {"ERR",MSG_TARGET_ERROR},
    {NULL,0}
};
#endif
