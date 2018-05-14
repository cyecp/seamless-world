/**
 * @file:   tss_sdk_anti.h
 * @brief:  This header file provides the interface of TSS SDK.
 * @copyright: 2012 Tencent. All Rights Reserved.
 */

#ifndef TSS_SDK_ANTI_V0_H_
#define TSS_SDK_ANTI_V0_H_

#include "tss_sdk.h"
#include "tss_sdk_anti.h"

#ifdef __cplusplus
extern "C"
{
#endif /* end of __cplusplus */

#pragma pack(1)

/* �����û���Ϣ */
/* Add user information */
typedef struct
{
    /* [in] openid*/
    TssSdkOpenid openid_;
    /* [in] ��Ϸ�ͻ��˵İ汾 game client version */
    unsigned int client_ver_;
    /* [in] ��Ϸ�ͻ���ip game client ip */
    unsigned int client_ip_;
    /* [in] �û���ǰ�Ľ�ɫ�� user's current role name */
    const char *role_name_;
} TssSdkAntiAddUserInfo;

/* ɾ���û���Ϣ */
/* delete user information */
typedef struct
{
    /* [in] openid*/
    TssSdkOpenid openid_;
} TssSdkAntiDelUserInfo;

/* �յ����������*/
/* recv anti data */
typedef struct
{
    /* [in] openid*/
    TssSdkOpenid openid_;
    /* [in] gamesvr�յ���anti���� */
    /* [in] anti data received by gamesvr */
    const unsigned char *anti_data_;
    /* [in] gamesvr�յ���anti���ݳ��� */
    /* [in] length of anti data received by gamesvr */
    unsigned int anti_data_len_;
} TssSdkAntiRecvDataInfo;

/* ������Ϸ���ݰ� */
/* decryption of packets */
typedef struct
{
    /* [in] openid*/
    TssSdkOpenid openid_;
    /* [in] gamesvr�յ�����Ϸ�������� */
    /* [in] game encrypt data received by gamesvr */
    const unsigned char *encrypt_data_;
    /* [in] gamesvr�յ�����Ϸ�������ݳ��� */
    /* [in] length of encrypt data received by gamesvr */
    unsigned int encrypt_data_len_;
    /* [in/out] ������Ž��ܺ����Ϸ����buf���ռ��ɵ��÷����� */
    /* [in/out] buf used to store the decrypted game package, space allocated by the caller */
    unsigned char *game_pkg_buf_;
    /* [in/out] ����Ϊgame_pkg_buf_��size�����Ϊ���ܺ����Ϸ��ʵ�ʳ��� */
    /* [in/out] input is size of game_pkg_buf_, output is the actual length of decrypted game package */
    unsigned int game_pkg_buf_len_;
} TssSdkAntiDecryptPkgInfo;

/* ��Ϸ���ݰ���Ϣ */
/* Game data package information */
typedef struct
{
    /* [in] openid*/
    TssSdkOpenid openid_;
    /* [in] ��Ϸ�������� Game package command word */
    unsigned int cmd_id_;
    /* [in] ��Ϸ���ݰ� Game data packets */
    const unsigned char *game_pkg_;
    /* [in] ��Ϸ���ݰ����� the length of game data packets */
    unsigned int game_pkg_len_;
} TssSdkAntiGamePkgInfo;

/* �������ݰ���Ϣ */
/* Encrypted data packet information */
typedef struct
{
    /* [in] openid*/
    TssSdkOpenid openid_;
    /* [in] ��Ϸ�������� Game package command word */
    unsigned int cmd_id_;
    /* [in] ��Ϸ���ݰ� Game data packets */
    const unsigned char *game_pkg_;
    /* [in] ��Ϸ���ݰ����ȣ���󳤶�ҪС��65000
    the length of game data packets, maximum length less than 65,000 */
    unsigned int game_pkg_len_;
    /* [in/out] ��Ϸ���ݰ����ܺ�����ݰ����ڴ��ɵ��÷����䣬���64k
    encrypted game data package assembled into anti data
    memory allocated by the caller, 64k at the maximum */
    unsigned char *encrypt_data_;
    /* [in/out] ����ʱΪencrypt_data_len_�ĳ��ȣ����ʱΪʵ��encrypt_data_len_ʹ�õĳ���
    length of encrypt_data_len_ when input, actual length of encrypt_data_len_ when output */
    unsigned int encrypt_data_len_;
} TssSdkAntiEncryptPkgInfo;

/* Ҫ���͵�anti������Ϣ */
/* anti data to be sent*/
typedef struct
{
    /* [in] openid*/
    TssSdkOpenid openid_;
    /* [in] anti���ݳ��� length of anti data */
    unsigned short anti_data_len_;
    /* [in] ��Ҫ���͵��ͻ��˵�anti���� anti data need to be sent to the client */
    const unsigned char *anti_data_;
} TssSdkAntiSendDataInfo;

/* ֪ͨ�����û�����Ϸ���û���½ʱ���� */
/* Notice to add a user, the game called when the user login */
typedef TssSdkProcResult(*TssSdkAddUser)(TssSdkAntiAddUserInfo *add_user_info);

/* ֪ͨɾ���û�����Ϸ���û��˳�ʱ���� */
/* Notice to delete a user, the game called when the user log out */
typedef TssSdkProcResult(*TssSdkDelUser)(const TssSdkAntiDelUserInfo *del_user_info);

/* ���տͻ�������anti���ݣ���Ϸ�յ����������ʱ���� */
/* recv anti data, the game called when recvd anti data */
typedef TssSdkProcResult(*TssSdkRecvDataFromClient)(TssSdkAntiRecvDataInfo *recv_pkg_info);


/* �ж�������Ϸ���Ƿ����װ�, 0��ʾ������ƭ������Ϸ������������ 1��ʾ����ƭ������Ϸ��Ҫ������Ϸ������ */
/* Determine whether the uplink game package is cheating package, */
/*0 means it is not deceive package which the game continue to processlater; */
/*1 means a deceive package which the game needs to discard */
typedef int (*TssSdkIsCheatPkg)(const TssSdkAntiGamePkgInfo *up_pkg_info);

/* �����е�anti���ݰ����н��� */
/* Decrypt for the uplink game data package */
typedef TssSdkAntiDecryptResult(*TssSdkDecryptPkg)(TssSdkAntiDecryptPkgInfo *decrypt_pkg_info);

/* ����Ҫ���ܵ���Ϸ�����м���,�������Ҫ���ܣ�����Ϸ���д����������Ҫ���ܣ���Ҫ��Ϸ���ͷ��ص�anti����  */
/* encrypt the game package which is needed, if not, the game process on its own; if needed, the game should send back the anti data */
typedef TssSdkAntiEncryptResult(*TssSdkEncryptPkg)(TssSdkAntiEncryptPkgInfo *down_pkg_info);

/* ����Anti���ݣ�������Ϸʵ�� */
/* send anti data, need to be implement by game */
typedef TssSdkProcResult(*TssSdkSendDataToClient)(const TssSdkAntiSendDataInfo *anti_data);

typedef struct
{
    /* ���ͼ��ܺ�����ݵ��ͻ���, �˺�����Ҫ��Ϸ������ʵ��*/
    /* Send encrypted data to the client, this function need to be implemented by game server */
    TssSdkSendDataToClient send_data_to_client_;
} TssSdkAntiInitInfo;


typedef struct
{
    /* �����û� Add user */
    TssSdkAddUser add_user_;

    /* ɾ���û� delete user */
    TssSdkDelUser del_user_;

    /* �յ���������ݰ� recv anti data package */
    TssSdkRecvDataFromClient recv_anti_data_;

    /* �ж��Ƿ���ƭ�� Determine whether the deception package */
    TssSdkIsCheatPkg is_cheat_pkg_;

    /* �������ݰ� decrypt data package */
    TssSdkDecryptPkg decrypt_pkg_;

    /* �������ݰ� encrypt data package */
    TssSdkEncryptPkg encrypt_pkg_;
} TssSdkAntiInterf;


/* ��ȡAnti�ӿ� */
/* �˺������tss_sdk_load�ɹ�֮����ܵ��� */
/* Get Anti interface */
/* This macro must be called after the success of tss_sdk_load */
#define TSS_SDK_GET_ANTI_INTERF(init_data) \
    (const TssSdkAntiInterf*)tss_sdk_get_busi_interf("tss_sdk_get_anti_interf", (const TssSdkAntiInitInfo *)(init_data))

#pragma pack()

#ifdef __cplusplus
} /* end of extern "C" */
#endif /* end of __cplusplus */

#endif /* TSS_SDK_ANTI_H_ */
