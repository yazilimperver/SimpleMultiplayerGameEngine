/**
 * \file    CommonMessage.h
 * \date    2019/06/07
 * \author  yazilimperver
 * \brief   
 * Copyright © 2018, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef COMMONMESSAGE_H__
#define COMMONMESSAGE_H__

#include <NetworkLibrary_Global.h>
#include <vector>

 // Message Structure :
 // MsgStart <1 Byte> | Direction <1 Bytes> | MsgID <1 Bytes> | MsgLength <1 Bytes> | MsgContent | MsgEnd <4 Bytes>

struct CommonMessage
{
	unsigned char mMsgStart{ cExpectedMsgStart };
	unsigned char mMsgId{ 0 };
	unsigned char mMsgLength{ 8U };
	unsigned char mSrcId{ 8U };
	std::vector<unsigned char> mMsgContent;
};

#endif // COMMONMESSAGE_H__

/*
  Copyright (c) [2018] [Yazilimperver <yazilimpervergs@gmail.com>]
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
