#ifndef PACKET_H
#define PACKET_H

#include <ptl/payload.h>

#ifdef __cpluscplus
    namespace packet {
    namespace c {
    extern "C" {
#endif

typedef uint16_t    packet_size_t;

typedef struct
{
payload_id_t    m_payload_id;
packet_size_t   m_size;
} packet_header_t;

#ifdef __cplusplus
    } //extern "C"
    } //namespace c
    } //namespace packet
#endif

#endif

