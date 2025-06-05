#ifndef LLSKINTERFACE_H
#define LLSKINTERFACE_H

#include <stdint.h>
#include <osmocom/core/prim.h>

// Primitive definitions adapted from osmo-hnodeb hnb_prim.h

#define HNB_PRIM_API_VERSION 0
#define HNB_PRIM_UD_SOCK_DEFAULT "/tmp/hnb_prim_sock"

#define HNB_PRIM_SAPI_IUH 1
#define HNB_PRIM_SAPI_GTP 2
#define HNB_PRIM_SAPI_AUDIO 3

struct hnb_iuh_configure_ind_param {
    uint16_t mcc;
    uint16_t mnc;
    uint16_t cell_identity;
    uint16_t lac;
    uint8_t  rac;
    uint8_t  reserved;
    uint16_t sac;
    uint16_t rnc_id;
} __attribute__((packed));

struct hnb_iuh_conn_establish_cnf_param {
    uint32_t context_id;
    uint8_t  domain;
    uint8_t  cause; /* 0 = success */
} __attribute__((packed));

struct hnb_iuh_prim {
    struct osmo_prim_hdr hdr;
    union {
        struct hnb_iuh_configure_ind_param configure_ind;
        struct hnb_iuh_conn_establish_cnf_param conn_establish_cnf;
    } u;
} __attribute__((packed));

#define LLSK_SAPI_IUH_VERSION_MIN 0
#define LLSK_SAPI_IUH_VERSION_MAX 0
#define LLSK_SAPI_AUDIO_VERSION_MIN 0
#define LLSK_SAPI_AUDIO_VERSION_MAX 1
#define LLSK_SAPI_GTP_VERSION_MIN 0
#define LLSK_SAPI_GTP_VERSION_MAX 0

#include <Sockets.h>
#include <Threads.h>

class LLSKInterface {
    char mReadBuffer[2048];
    UDPSocket mSocket;
    Thread mDriveThread;
public:
    LLSKInterface();
    void start();
    void drive();
    void send(const void* data, size_t len);
};

#endif // LLSKINTERFACE_H
