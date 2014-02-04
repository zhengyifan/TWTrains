/* /////////////////////////////////////////////////////////////////////////
* File:        TrainErrcodeDef.h
* Purpose:     define Errcode
* Created:     May 28,2011
* Author :     Evan Zheng
* Email  :     zheng_yifan@hotmail.com
* ///////////////////////////////////////////////////////////////////////// */

#ifndef _TRAINERRCODEDEF_H_ 
#define _TRAINERRCODEDEF_H_ 

typedef int	ErrorCode;	// 错误码

const ErrorCode TS_ERROR_SUCCESS                   = 1000;         // 成功
const ErrorCode TS_ERROR_MGRAPH_NOTCREATE          = 1001;         // 图没有被创建
const ErrorCode TS_ERROR_INPUT_TRACK_ERR           = 1002;         // 输入参数错误

#endif