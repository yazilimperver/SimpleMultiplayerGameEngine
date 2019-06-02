/**
 * \file    CommunicationInfrastructure_Global.h
 * \date    2019/05/31
 * \author  yazilimperver
 * \brief   In this file, we are going to briefly describe the protocol that will be used for communication.
This protocol is very simple and just for simple multiplayer communication.

General Principles:
- Participants can join lobby till permitted capacity
- If client does not respond to heartbeat msg (ID:0) three times it is assumed dead, disconnected and dropped
- Client requested information when connected client should provide them in 1 second before join
- Min message length is 8 bytes

Message Structure:
MsgStart <1 Byte> | Direction <1 Bytes>| MsgID <1 Bytes>| MsgLength <1 Bytes> | MsgContent | MsgEnd <4 Bytes>

 * Copyright © 2018, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef COMMUNICATIONINFRASTRUCTURE_GLOBAL_H__
#define COMMUNICATIONINFRASTRUCTURE_GLOBAL_H__

 /// Common message protocol constants
constexpr int  cMinMsgLength = 8;
constexpr char cExpectedMsgStart = 0x45;
constexpr int  cExpectedMsgEnd = 0x65432109;
constexpr int  cMsgStartIndex = 0;
constexpr int  cMsgDirectionIndex = 1;
constexpr int  cMsgIdIndex = 2;
constexpr int  cMsgLengthIndex = 3;
constexpr int  cMsgDataIndex = 4;
constexpr char cMsgDirServerToClient = 1;
constexpr char cMsgDirClientToServer = 2;


#endif // COMMUNICATIONINFRASTRUCTURE_GLOBAL_H__

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