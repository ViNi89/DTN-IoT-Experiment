#ifndef __IOT_DTN__H
#define __IOT_DTN__H

#include <iot/types.h>
#include <iot/cache.h>

#if TARGET==IOT_PLATFORM_SKY
#define PACKETBUF_CONF_SIZE 512
#endif

#include "contiki.h"
#include "net/rime.h"
#include "random.h"

#define IOT_BROADCAST_INTERVAL ( 2 * CLOCK_SECOND )

#define IOT_EPOCH_MID ( 4 * CLOCK_SECOND )
#define IOT_EPOCH_MAX ( 8 * CLOCK_SECOND )
#define IOT_EPOCH_MIN ( CLOCK_SECOND )
#define IOT_INTEREST_MIN ( 1 )

#define IOT_NETWORK_ENTITY(x) ((struct iotNetworkEntity*)x)

struct iotNetworkEntity {
  struct unicast_conn m_UC;
  struct broadcast_conn m_BC;
} iotNetworkEntity;

struct iotClient {
  struct unicast_conn     m_UC;
  struct broadcast_conn   m_BC;

  iotBool                 m_Interests[MAX_TYPE];
  iotBool		              m_InRange;
  iotBool		              m_PendingAnnounce;
  enum iotPacketTypes     m_ForwardType;

} iotClient;

struct iotDataMule {
  struct unicast_conn m_UC;
  struct broadcast_conn m_BC;

  struct iotCache m_PacketCache;
} iotDataMule;

// Construction
iotInt32 iot_mule_create(struct iotDataMule *dm);
iotInt32 iot_client_create(struct iotClient* p);

// Cleanup
iotInt32 iot_mule_close(struct iotDataMule *dm);
iotInt32 iot_client_close(struct iotClient* p);

// Utility
iotChar *iot_client_interest_json_desc(struct iotClient *c, iotChar *buffer,
                             iotInt32 *len);

void iot_client_announce(struct iotClient *c);

iotBool iot_mule_discovered();
const rimeaddr_t *iot_mule_address();
const iotChar* iot_mule_address_desc();

iotBool iot_mule_changed();
iotInt32 iot_set_mule_address(const rimeaddr_t *address);
iotInt32 iot_set_prev_mule_address(const rimeaddr_t *address);
#endif // __IOT_DTN__H
