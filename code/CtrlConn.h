#pragma once

#define CtrlMsgDefs \
    X(ServerReady) \
    X(PlayerLeft) \
    X(TransferUser)

typedef enum CtrlMsgId {
    CtrlMsgId_None,
#define X(name) CtrlMsgId_ ## name,
    CtrlMsgDefs
#undef X
    CtrlMsgId_Count,
} CtrlMsgId;

typedef struct CtrlMsg_ServerReady {
    CtrlMsgId msg_id;
    uint32_t  server_id;
} CtrlMsg_ServerReady;

typedef struct CtrlMsg_PlayerLeft {
    CtrlMsgId msg_id;
    GmUuid    account_id;
} CtrlMsg_PlayerLeft;

typedef struct CtrlMsg_TransferUser {
    CtrlMsgId   msg_id;
    SocketAddr  peer_addr;
    IoSource    source;
    uintptr_t   token;
    uint8_t     cipher_init_key[20];
    bool        reconnection;
    GmUuid      account_id;
    GmUuid      char_id;
} CtrlMsg_TransferUser;

typedef union CtrlMsg {
    CtrlMsgId           msg_id;
    uint8_t             buffer[MSG_MAX_BUFFER_SIZE];
#define X(name) CtrlMsg_ ## name name;
    CtrlMsgDefs
#undef X
} CtrlMsg;
typedef array(CtrlMsg *) CtrlMsgArray;

typedef struct CtrlConn {
    uintptr_t     token;
    IoSource      source;
    SocketAddr    peer_addr;
    array_uint8_t incoming;
    array_uint8_t outgoing;
    bool          writable;
    bool          connected;
    CtrlMsgArray  messages;
    uint32_t      server_id;
} CtrlConn;

int  CtrlConn_Setup(CtrlConn *conn);
void CtrlConn_Free(CtrlConn *conn);
int  CtrlConn_FlushOutgoingBuffer(CtrlConn *conn);
int  CtrlConn_WriteMessage(CtrlConn *conn, CtrlMsg *msg, size_t size);
int  CtrlConn_GetMessages(CtrlConn *conn);
int  CtrlConn_ProcessEvent(CtrlConn *conn, Event event);

int  CtrlConn_UpdateWrite(CtrlConn *conn);
int  CtrlConn_WriteHandshake(CtrlConn *conn);
int  CtrlConn_SendServerReady(CtrlConn *conn, uint32_t server_id);
int  CtrlConn_SendPlayerLeft(CtrlConn *conn);
