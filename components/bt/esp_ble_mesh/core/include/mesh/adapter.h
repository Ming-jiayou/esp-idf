/*
 * SPDX-FileCopyrightText: 2017 Nordic Semiconductor ASA
 * SPDX-FileCopyrightText: 2015-2017 Intel Corporation
 * SPDX-FileContributor: 2018-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _BLE_MESH_ADAPTER_H_
#define _BLE_MESH_ADAPTER_H_

#include <sys/types.h>
#include "mesh/config.h"
#include "mesh/types.h"
#include "mesh/utils.h"
#include "mesh/uuid.h"
#include "mesh/buf.h"

#ifdef __cplusplus
extern "C" {
#endif

/* BLE Mesh Max Connection Count */
/**
 * The maximum number of connection count is limited by
 * the resources allocated by both the host and the controller
 * components, so the actual number of available connections
 * is the minimum of the resources from both.
 *
 * On the C3/S3 platform, the controller uses the macro `CONFIG_BT_CTRL_BLE_MAX_ACT`,
 * but adv and scan also occupy this resource, so the actual number of available
 * connections is (CONFIG_BT_CTRL_BLE_MAX_ACT - adv instance count - scan).
 * However, the macro allocation on the host is entirely for connections,
 * so on the C3/S3 platform, the maximum number of connectable devices should
 * be determined by the configuration at the host minus the number of
 * advertising instances and scan from the controller's configuration.
*/
#ifdef CONFIG_BT_BLUEDROID_ENABLED
#if CONFIG_IDF_TARGET_ESP32
#define BLE_MESH_MAX_CONN   1
#elif (CONFIG_IDF_TARGET_ESP32C3 || CONFIG_IDF_TARGET_ESP32S3)
/* @todo: must ensure CONFIG_BT_CTRL_BLE_MAX_ACT is greater than 2 */
#if CONFIG_BT_ACL_CONNECTIONS > (CONFIG_BT_CTRL_BLE_MAX_ACT - 2)
/* decrease the adv,scan */
#define BLE_MESH_MAX_CONN   (CONFIG_BT_CTRL_BLE_MAX_ACT - 2)
#else
#define BLE_MESH_MAX_CONN   CONFIG_BT_ACL_CONNECTIONS
#endif /* CONFIG_BT_ACL_CONNECTIONS > (CONFIG_BT_CTRL_BLE_MAX_ACT - 2) */
#elif CONFIG_IDF_TARGET_ESP32C6 || CONFIG_IDF_TARGET_ESP32H2 || CONFIG_IDF_TARGET_ESP32C5
#if CONFIG_BT_ACL_CONNECTIONS > CONFIG_BT_LE_MAX_CONNECTIONS
#define BLE_MESH_MAX_CONN   CONFIG_BT_LE_MAX_CONNECTIONS
#else
#define BLE_MESH_MAX_CONN   CONFIG_BT_ACL_CONNECTIONS
#endif /* CONFIG_BT_ACL_CONNECTIONS > CONFIG_BT_LE_MAX_CONNECTIONS */
#else
/* default setting */
#define BLE_MESH_MAX_CONN   1
#endif
#endif /* CONFIG_BT_BLUEDROID_ENABLED */

#ifdef CONFIG_BT_NIMBLE_ENABLED
#if CONFIG_IDF_TARGET_ESP32
#define BLE_MESH_MAX_CONN   1
#elif (CONFIG_IDF_TARGET_ESP32C3 || CONFIG_IDF_TARGET_ESP32S3)
/* @todo: must ensure CONFIG_BT_CTRL_BLE_MAX_ACT is greater than 2 */
#if CONFIG_BT_NIMBLE_MAX_CONNECTIONS > (CONFIG_BT_CTRL_BLE_MAX_ACT - 2)
/* decrease the adv,scan */
#define BLE_MESH_MAX_CONN   (CONFIG_BT_CTRL_BLE_MAX_ACT - 2)
#else
#define BLE_MESH_MAX_CONN   CONFIG_BT_NIMBLE_MAX_CONNECTIONS
#endif /* CONFIG_BT_NIMBLE_MAX_CONNECTIONS > (CONFIG_BT_CTRL_BLE_MAX_ACT - 2) */
#elif CONFIG_IDF_TARGET_ESP32C6 || CONFIG_IDF_TARGET_ESP32H2 || CONFIG_IDF_TARGET_ESP32C5
#define BLE_MESH_MAX_CONN   CONFIG_BT_NIMBLE_MAX_CONNECTIONS
#else
/* default setting */
#define BLE_MESH_MAX_CONN   1
#endif
#endif /* CONFIG_BT_NIMBLE_ENABLED */

#define BLE_MESH_GAP_ADV_MAX_LEN    31

#define BLE_MESH_GATT_DEF_MTU_SIZE  23

#if CONFIG_BLE_MESH_USE_BLE_50
#define BLE_MESH_ADV_PHY_UNASSIGNED                                 0
#define BLE_MESH_ADV_PHY_1M                                         1
#define BLE_MESH_ADV_PHY_2M                                         2
#define BLE_MESH_ADV_PHY_CODED                                      3
#define BLE_MESH_ADV_PHY_OPTION_NO_PREFER                           0
#define BLE_MESH_ADV_PHY_OPTION_PREFER_S2                           1
#define BLE_MESH_ADV_PHY_OPTION_PREFER_S8                           2
#define BLE_MESH_ADV_PHY_OPTION_REQUIRE_S2                          3
#define BLE_MESH_ADV_PHY_OPTION_REQUIRE_S8                          4
#endif

/* BD ADDR types */
#define BLE_MESH_ADDR_PUBLIC         0x00
#define BLE_MESH_ADDR_RANDOM         0x01
#define BLE_MESH_ADDR_PUBLIC_ID      0x02
#define BLE_MESH_ADDR_RANDOM_ID      0x03

/* BD ADDR length */
#define BLE_MESH_ADDR_LEN                   0x06

/* Advertising types */
#if !CONFIG_BLE_MESH_USE_BLE_50
#define BLE_MESH_ADV_IND                    0x00
#define BLE_MESH_ADV_DIRECT_IND             0x01
#define BLE_MESH_ADV_SCAN_IND               0x02
#define BLE_MESH_ADV_NONCONN_IND            0x03
#define BLE_MESH_ADV_DIRECT_IND_LOW_DUTY    0x04
#define BLE_MESH_ADV_SCAN_RSP               0x04
#else
/* Bluetooth Core Spec 6.0, Vol 4, Part E, 7.7.65.13 */
#define BLE_MESH_ADV_IND                   (0x13)
#define BLE_MESH_ADV_DIRECT_IND            (0x15)
#define BLE_MESH_ADV_SCAN_IND              (0x12)
#define BLE_MESH_ADV_NONCONN_IND           (0x10)
#define BLE_MESH_ADV_DIRECT_IND_LOW_DUTY   (0x1b)
#define BLE_MESH_ADV_SCAN_RSP              (0x1b)
#endif

/* advertising channel map */
#define BLE_MESH_ADV_CHNL_37                BIT(0)
#define BLE_MESH_ADV_CHNL_38                BIT(1)
#define BLE_MESH_ADV_CHNL_39                BIT(2)

/* Advertising filter policy */
#define BLE_MESH_AP_SCAN_CONN_ALL           0x00
#define BLE_MESH_AP_SCAN_WL_CONN_ALL        0x01
#define BLE_MESH_AP_SCAN_ALL_CONN_WL        0x02
#define BLE_MESH_AP_SCAN_CONN_WL            0x03

/* Scan types */
#define BLE_MESH_SCAN_PASSIVE               0x00
#define BLE_MESH_SCAN_ACTIVE                0x01

/* Scan operation */
#define BLE_MESH_SCAN_DISABLE               0x00
#define BLE_MESH_SCAN_ENABLE                0x01

/* Scan duplicate operation */
#define BLE_MESH_SCAN_FILTER_DUP_DISABLE    0x00
#define BLE_MESH_SCAN_FILTER_DUP_ENABLE     0x01

/* Scan filter policy */
#define BLE_MESH_SP_ADV_ALL                 0x00
#define BLE_MESH_SP_ADV_WL                  0x01
#define BLE_MESH_SP_ADV_ALL_RPA_DIR_ADV     0x02
#define BLE_MESH_SP_ADV_WL_RPA_DIR_ADV      0x03

/* Error codes for Error response PDU */
#define BLE_MESH_ATT_ERR_INVALID_HANDLE             0x01
#define BLE_MESH_ATT_ERR_READ_NOT_PERMITTED         0x02
#define BLE_MESH_ATT_ERR_WRITE_NOT_PERMITTED        0x03
#define BLE_MESH_ATT_ERR_INVALID_PDU                0x04
#define BLE_MESH_ATT_ERR_AUTHENTICATION             0x05
#define BLE_MESH_ATT_ERR_NOT_SUPPORTED              0x06
#define BLE_MESH_ATT_ERR_INVALID_OFFSET             0x07
#define BLE_MESH_ATT_ERR_AUTHORIZATION              0x08
#define BLE_MESH_ATT_ERR_PREPARE_QUEUE_FULL         0x09
#define BLE_MESH_ATT_ERR_ATTRIBUTE_NOT_FOUND        0x0a
#define BLE_MESH_ATT_ERR_ATTRIBUTE_NOT_LONG         0x0b
#define BLE_MESH_ATT_ERR_ENCRYPTION_KEY_SIZE        0x0c
#define BLE_MESH_ATT_ERR_INVALID_ATTRIBUTE_LEN      0x0d
#define BLE_MESH_ATT_ERR_UNLIKELY                   0x0e
#define BLE_MESH_ATT_ERR_INSUFFICIENT_ENCRYPTION    0x0f
#define BLE_MESH_ATT_ERR_UNSUPPORTED_GROUP_TYPE     0x10
#define BLE_MESH_ATT_ERR_INSUFFICIENT_RESOURCES     0x11

/* Common Profile Error Codes (from CSS) */
#define BLE_MESH_ATT_ERR_WRITE_REQ_REJECTED         0xfc
#define BLE_MESH_ATT_ERR_CCC_IMPROPER_CONF          0xfd
#define BLE_MESH_ATT_ERR_PROCEDURE_IN_PROGRESS      0xfe
#define BLE_MESH_ATT_ERR_OUT_OF_RANGE               0xff

/* EIR/AD data type definitions */
#define BLE_MESH_DATA_FLAGS                 0x01 /* AD flags */
#define BLE_MESH_DATA_UUID16_SOME           0x02 /* 16-bit UUID, more available */
#define BLE_MESH_DATA_UUID16_ALL            0x03 /* 16-bit UUID, all listed */
#define BLE_MESH_DATA_UUID32_SOME           0x04 /* 32-bit UUID, more available */
#define BLE_MESH_DATA_UUID32_ALL            0x05 /* 32-bit UUID, all listed */
#define BLE_MESH_DATA_UUID128_SOME          0x06 /* 128-bit UUID, more available */
#define BLE_MESH_DATA_UUID128_ALL           0x07 /* 128-bit UUID, all listed */
#define BLE_MESH_DATA_NAME_SHORTENED        0x08 /* Shortened name */
#define BLE_MESH_DATA_NAME_COMPLETE         0x09 /* Complete name */
#define BLE_MESH_DATA_TX_POWER              0x0A /* Tx Power */
#define BLE_MESH_DATA_CLASS_OF_DEVICE       0x0D /* Class of Device */
#define BLE_MESH_DATA_SIMP_PAIR_HASH_C      0x0E /* Simple Pairing Hash C */
#define BLE_MESH_DATA_SIMP_PAIR_RAND_R      0x0F /* Simple Pairing Randomizer R */
#define BLE_MESH_DATA_SEC_MANAGER_TK_VAL    0x10 /* Security Manager TK Value */
#define BLE_MESH_DATA_SEC_MANAGER_OOB_FLAG  0x11 /* Security Manager Out of Band Flags */
#define BLE_MESH_DATA_SLAVE_CONN_INT_RANGE  0x12 /* Slave Connection Interval Range */
#define BLE_MESH_DATA_SOLICIT16             0x14 /* Solicit UUIDs, 16-bit */
#define BLE_MESH_DATA_SOLICIT128            0x15 /* Solicit UUIDs, 128-bit */
#define BLE_MESH_DATA_SVC_DATA16            0x16 /* Service data, 16-bit UUID */
#define BLE_MESH_DATA_PUBLIC_TARGET_ADDR    0x17 /* Public Target Address */
#define BLE_MESH_DATA_RANDOM_TARGET_ADDR    0x18 /* Random Target Address */
#define BLE_MESH_DATA_GAP_APPEARANCE        0x19 /* GAP appearance */
#define BLE_MESH_DATA_ADV_INTERVAL          0x1A /* Advertising Interval */
#define BLE_MESH_DATA_LE_DEVICE_ADDR        0x1B /* LE Bluetooth Device Address */
#define BLE_MESH_DATA_LE_ROLE               0x1C /* LE Role */
#define BLE_MESH_DATA_SIMP_PAIR_HASH_C_256  0x1D /* Simple Pairing Hash C-256 */
#define BLE_MESH_DATA_SIMP_PAIR_RAND_R_256  0x1E /* Simple Pairing Randomizer R-256 */
#define BLE_MESH_DATA_SOLICIT32             0x1F /* Solicit UUIDs, 32-bit */
#define BLE_MESH_DATA_SVC_DATA32            0x20 /* Service data, 32-bit UUID */
#define BLE_MESH_DATA_SVC_DATA128           0x21 /* Service data, 128-bit UUID */
#define BLE_MESH_DATA_LE_SEC_CONN_CFM_VAL   0x22 /* LE Secure Connections Confirmation Value */
#define BLE_MESH_DATA_LE_SEC_CONN_RAND_VAL  0x23 /* LE Secure Connections Random Value */
#define BLE_MESH_DATA_URI                   0x24 /* URI */
#define BLE_MESH_DATA_INDOOR_POSITION       0x25 /* Indoor Positioning */
#define BLE_MESH_DATA_TRANS_DISC_DATA       0x26 /* Transport Discovery Data */
#define BLE_MESH_DATA_LE_SUPPORT_FEAT       0x27 /* LE Supported Features */
#define BLE_MESH_DATA_CHAN_MAP_UPDATE_IND   0x28 /* Channel Map Update Indication */
#define BLE_MESH_DATA_MESH_PROV             0x29 /* Mesh Provisioning PDU */
#define BLE_MESH_DATA_MESH_MESSAGE          0x2A /* Mesh Networking PDU */
#define BLE_MESH_DATA_MESH_BEACON           0x2B /* Mesh Beacon */
#define BLE_MESH_DATA_BIGINFO               0x2C /* BIGInf */
#define BLE_MESH_DATA_BROADCAST_COD         0x2D /* Broadcast_Cod */
#define BLE_MESH_DATA_3D_INFO_DATA          0x3D /* 3D Information Data */
#define BLE_MESH_DATA_MANUFACTURER_DATA     0xFF /* Manufacturer Specific Data */

#define BLE_MESH_AD_LIMITED     0x01 /* Limited Discoverable */
#define BLE_MESH_AD_GENERAL     0x02 /* General Discoverable */
#define BLE_MESH_AD_NO_BREDR    0x04 /* BR/EDR not supported */

/* Client Characteristic Configuration Values */

/** @def BLE_MESH_GATT_CCC_NOTIFY
 *  @brief Client Characteristic Configuration Notification.
 *
 *  If set, changes to Characteristic Value shall be notified.
 */
#define BLE_MESH_GATT_CCC_NOTIFY        0x0001

/** @def BLE_MESH_GATT_CCC_INDICATE
 *  @brief Client Characteristic Configuration Indication.
 *
 *  If set, changes to Characteristic Value shall be indicated.
 */
#define BLE_MESH_GATT_CCC_INDICATE      0x0002

/**  @def BLE_MESH_GATT_ERR
  *  @brief Construct error return value for attribute read and write callbacks.
  *
  *  @param _att_err ATT error code
  *
  *  @return Appropriate error code for the attribute callbacks.
  *
  */
#define BLE_MESH_GATT_ERR(_att_err)     (-(_att_err))

enum {
    BLE_MESH_GATT_ITER_STOP = 0,
    BLE_MESH_GATT_ITER_CONTINUE,
};

/* GATT attribute permission bit field values */
enum {
    /** No operations supported, e.g. for notify-only */
    BLE_MESH_GATT_PERM_NONE = 0,

    /** Attribute read permission. */
    BLE_MESH_GATT_PERM_READ = BIT(0),

    /** Attribute write permission. */
    BLE_MESH_GATT_PERM_WRITE = BIT(1),

    /** Attribute read permission with encryption.
     *
     *  If set, requires encryption for read access.
     */
    BLE_MESH_GATT_PERM_READ_ENCRYPT = BIT(2),

    /** Attribute write permission with encryption.
     *
     *  If set, requires encryption for write access.
     */
    BLE_MESH_GATT_PERM_WRITE_ENCRYPT = BIT(3),

    /** Attribute read permission with authentication.
     *
     *  If set, requires encryption using authenticated link-key for read
     *  access.
     */
    BLE_MESH_GATT_PERM_READ_AUTHEN = BIT(4),

    /** Attribute write permission with authentication.
     *
     *  If set, requires encryption using authenticated link-key for write
     *  access.
     */
    BLE_MESH_GATT_PERM_WRITE_AUTHEN = BIT(5),

    /** Attribute prepare write permission.
     *
     *  If set, allows prepare writes with use of BT_GATT_WRITE_FLAG_PREPARE
     *  passed to write callback.
     */
    BLE_MESH_GATT_PERM_PREPARE_WRITE = BIT(6),
};

/** Advertising options */
enum {
    /** Convenience value when no options are specified. */
    BLE_MESH_ADV_OPT_NONE = 0,

    /** Advertise as connectable. Type of advertising is determined by
     * providing SCAN_RSP data and/or enabling local privacy support.
     */
    BLE_MESH_ADV_OPT_CONNECTABLE = BIT(0),

    /** Don't try to resume connectable advertising after a connection.
     *  This option is only meaningful when used together with
     *  BLE_MESH_ADV_OPT_CONNECTABLE. If set the advertising will be stopped
     *  when bt_le_adv_stop() is called or when an incoming (slave)
     *  connection happens. If this option is not set the stack will
     *  take care of keeping advertising enabled even as connections
     *  occur.
     */
    BLE_MESH_ADV_OPT_ONE_TIME = BIT(1),
};

/* Defined GAP timers */
#define BLE_MESH_GAP_SCAN_FAST_INTERVAL     0x0060  /* 60 ms    */
#define BLE_MESH_GAP_SCAN_FAST_WINDOW       0x0030  /* 30 ms    */
#define BLE_MESH_GAP_SCAN_SLOW_INTERVAL_1   0x0800  /* 1.28 s   */
#define BLE_MESH_GAP_SCAN_SLOW_WINDOW_1     0x0012  /* 11.25 ms */
#define BLE_MESH_GAP_SCAN_SLOW_INTERVAL_2   0x1000  /* 2.56 s   */
#define BLE_MESH_GAP_SCAN_SLOW_WINDOW_2     0x0012  /* 11.25 ms */
#define BLE_MESH_GAP_ADV_FAST_INT_MIN_0     0x0020  /* 20 ms    */
#define BLE_MESH_GAP_ADV_FAST_INT_MAX_0     0x0020  /* 20 ms    */
#define BLE_MESH_GAP_ADV_FAST_INT_MIN_1     0x0030  /* 30 ms    */
#define BLE_MESH_GAP_ADV_FAST_INT_MAX_1     0x0060  /* 60 ms    */
#define BLE_MESH_GAP_ADV_FAST_INT_MIN_2     0x00a0  /* 100 ms   */
#define BLE_MESH_GAP_ADV_FAST_INT_MAX_2     0x00f0  /* 150 ms   */
#define BLE_MESH_GAP_ADV_SLOW_INT_MIN       0x0320  /* 500 ms   */
#define BLE_MESH_GAP_ADV_SLOW_INT_MAX       0x0320  /* 500 ms   */
#define BLE_MESH_GAP_INIT_CONN_INT_MIN      0x0018  /* 30 ms    */
#define BLE_MESH_GAP_INIT_CONN_INT_MAX      0x0028  /* 50 ms    */

/* Characteristic Properties Bit field values */

/** @def BLE_MESH_GATT_CHRC_BROADCAST
 *  @brief Characteristic broadcast property.
 *
 *  If set, permits broadcasts of the Characteristic Value using Server
 *  Characteristic Configuration Descriptor.
 */
#define BLE_MESH_GATT_CHRC_BROADCAST              0x01

/** @def BLE_MESH_GATT_CHRC_READ
 *  @brief Characteristic read property.
 *
 *  If set, permits reads of the Characteristic Value.
 */
#define BLE_MESH_GATT_CHRC_READ                   0x02

/** @def BLE_MESH_GATT_CHRC_WRITE_WITHOUT_RESP
 *  @brief Characteristic write without response property.
 *
 *  If set, permits write of the Characteristic Value without response.
 */
#define BLE_MESH_GATT_CHRC_WRITE_WITHOUT_RESP     0x04

/** @def BLE_MESH_GATT_CHRC_WRITE
 *  @brief Characteristic write with response property.
 *
 *  If set, permits write of the Characteristic Value with response.
 */
#define BLE_MESH_GATT_CHRC_WRITE                  0x08

/** @def BLE_MESH_GATT_CHRC_NOTIFY
 *  @brief Characteristic notify property.
 *
 *  If set, permits notifications of a Characteristic Value without
 *  acknowledgment.
 */
#define BLE_MESH_GATT_CHRC_NOTIFY                 0x10

/** @def BLE_MESH_GATT_CHRC_INDICATE
 *  @brief Characteristic indicate property.
 *
 * If set, permits indications of a Characteristic Value with acknowledgment.
 */
#define BLE_MESH_GATT_CHRC_INDICATE               0x20

/** @def BLE_MESH_GATT_CHRC_AUTH
 *  @brief Characteristic Authenticated Signed Writes property.
 *
 *  If set, permits signed writes to the Characteristic Value.
 */
#define BLE_MESH_GATT_CHRC_AUTH                   0x40

/** @def BLE_MESH_GATT_CHRC_EXT_PROP
 *  @brief Characteristic Extended Properties property.
 *
 * If set, additional characteristic properties are defined in the
 * Characteristic Extended Properties Descriptor.
 */
#define BLE_MESH_GATT_CHRC_EXT_PROP               0x80

/** @brief Characteristic Attribute Value. */
struct bt_mesh_gatt_char {
    /** Characteristic UUID. */
    const struct bt_mesh_uuid *uuid;
    /** Characteristic properties. */
    uint8_t                    properties;
};

/** @brief GATT Service structure */
struct bt_mesh_gatt_service {
    /** Service Attributes */
    struct bt_mesh_gatt_attr *attrs;
    /** Service Attribute count */
    uint16_t                  attr_count;
    sys_snode_t               node;
};

typedef struct {
    uint8_t type;
    uint8_t val[6];
} bt_mesh_addr_t;

/** Description of different data types that can be encoded into
  * advertising data. Used to form arrays that are passed to the
  * bt_le_adv_start() function.
  */
struct bt_mesh_adv_data {
    uint8_t type;
    uint8_t data_len;
    const uint8_t *data;
};

/** @brief Helper to declare elements of bt_data arrays
 *
 *  This macro is mainly for creating an array of struct
 *  bt_mesh_adv_data elements which is then passed to
 *  bt_le_adv_start().
 *
 *  @param _type Type of advertising data field
 *  @param _data Pointer to the data field payload
 *  @param _data_len Number of bytes behind the _data pointer
 */
#define BLE_MESH_ADV_DATA(_type, _data, _data_len)  \
    {                                               \
        .type = (_type),                            \
        .data_len = (_data_len),                    \
        .data = (const uint8_t *)(_data),           \
    }

/** @brief Helper to declare elements of bt_data arrays
 *
 *  This macro is mainly for creating an array of struct bt_mesh_adv_data
 *  elements which is then passed to bt_le_adv_start().
 *
 *  @param _type Type of advertising data field
 *  @param _bytes Variable number of single-byte parameters
 */
#define BLE_MESH_ADV_DATA_BYTES(_type, _bytes...)       \
    BLE_MESH_ADV_DATA(_type, ((uint8_t []) { _bytes }), \
        sizeof((uint8_t []) { _bytes }))

/* BLE Mesh Advertising Parameters */
struct bt_mesh_adv_param {
    /** Bit-field of advertising options */
    uint8_t  options;

    /** Minimum Advertising Interval (N * 0.625) */
    uint16_t interval_min;

    /** Maximum Advertising Interval (N * 0.625) */
    uint16_t interval_max;

#if CONFIG_BLE_MESH_USE_BLE_50
    /** Maximum Advertising Duration (N * 0.625) */
    uint16_t adv_duration;

    /** Advertising Packages Number */
    uint16_t adv_count;

    /** Advertising Primary PHY */
    uint8_t primary_phy;

    /** Advertising Secondary PHY */
    uint8_t secondary_phy;
#endif
};

#define ADV_TASK_ADV_INST_EVT(inst_id) BIT(inst_id)

enum bt_mesh_adv_inst_type {
    BLE_MESH_ADV_INS,
#if CONFIG_BLE_MESH_SUPPORT_MULTI_ADV
#if (CONFIG_BLE_MESH_NODE && CONFIG_BLE_MESH_PB_GATT) || \
     CONFIG_BLE_MESH_GATT_PROXY_SERVER
    BLE_MESH_ADV_PROXY_INS,
#endif
#if CONFIG_BLE_MESH_SEPARATE_RELAY_ADV_INSTANCE
    BLE_MESH_RELAY_ADV_INS,
#endif
#if CONFIG_BLE_MESH_SEPARATE_BLE_ADV_INSTANCE
    BLE_MESH_BLE_ADV_INS,
#endif
#endif /* CONFIG_BLE_MESH_SUPPORT_MULTI_ADV */
    BLE_MESH_ADV_INS_TYPES_NUM,
};

#if CONFIG_BLE_MESH_SUPPORT_BLE_ADV
enum bt_mesh_ble_adv_priority {
    BLE_MESH_BLE_ADV_PRIO_LOW,
    BLE_MESH_BLE_ADV_PRIO_HIGH,
};

struct bt_mesh_ble_adv_param {
    uint16_t interval;         /* Advertising interval */
    uint8_t  adv_type;         /* Advertising type */
    uint8_t  own_addr_type;    /* Own address type */
    uint8_t  peer_addr_type;   /* Peer address type */
    uint8_t  peer_addr[6];     /* Peer address */
    uint16_t duration;         /* Duration is milliseconds */
    uint16_t period;           /* Period in milliseconds */
    uint16_t count;            /* Number of advertising duration */
    uint8_t  priority:2;       /* Priority of BLE advertising packet */
};

struct bt_mesh_ble_adv_data {
    uint8_t adv_data_len;      /* Advertising data length */
    uint8_t adv_data[31];      /* Advertising data */
    uint8_t scan_rsp_data_len; /* Scan response data length */
    uint8_t scan_rsp_data[31]; /* Scan response data */
};
#endif /* CONFIG_BLE_MESH_SUPPORT_BLE_ADV */

/* BLE Mesh scan parameters */
struct bt_mesh_scan_param {
    /** Scan type (BLE_MESH_SCAN_ACTIVE or BLE_MESH_SCAN_PASSIVE) */
    uint8_t  type;

    /** Duplicate filtering (BLE_MESH_SCAN_FILTER_DUP_ENABLE or
     *  BLE_MESH_SCAN_FILTER_DUP_DISABLE)
     */
    uint8_t  filter_dup;

    /** Scan interval (N * 0.625 ms) */
    uint16_t interval;

    /** Uncoded phy Scan window (N * 0.625 ms) */
    uint16_t window;

    /** BLE scan filter policy */
    uint8_t  scan_fil_policy;
};

struct bt_mesh_conn {
    uint16_t handle;
    bt_mesh_atomic_t ref;
};

/* BLE Mesh advertising report  */
struct bt_mesh_adv_report {
    /* Advertiser LE address and type. */
    bt_mesh_addr_t addr;

    /* Strength of advertiser signal. */
    int8_t rssi;

    /* Type of advertising response from advertiser. */
    uint8_t adv_type;

    /* Buffer containing advertiser data. */
    struct net_buf_simple adv_data;

#if CONFIG_BLE_MESH_USE_BLE_50
    /* Primary advertising PHY */
    uint8_t primary_phy;

    /* Secondary advertising PHY */
    uint8_t secondary_phy;
#endif /* CONFIG_BLE_MESH_USE_BLE_50 */
};

/** @typedef bt_mesh_scan_cb_t
 *  @brief Callback type for reporting LE scan results.
 *
 *  A function of this type is given to the bt_le_scan_start() function
 *  and will be called for any discovered LE device.
 *
 *  @param adv_rpt: BLE Mesh advertising report.
 */
typedef void bt_mesh_scan_cb_t(struct bt_mesh_adv_report *adv_rpt);

/*  @typedef bt_mesh_dh_key_cb_t
 *  @brief Callback type for DH Key calculation.
 *
 *  Used to notify of the calculated DH Key.
 *
 *  @param key Public key.
 *  @param user_data User data.
 *
 *  @return The DH Key, or NULL in case of failure.
 */
typedef void (*bt_mesh_dh_key_cb_t)(const uint8_t key[32], void *user_data);

/** @typedef bt_mesh_gatt_attr_func_t
 *  @brief Attribute iterator callback.
 *
 *  @param attr Attribute found.
 *  @param user_data Data given.
 *
 *  @return BLE_MESH_GATT_ITER_CONTINUE if should continue to the next attribute
 *  or BLE_MESH_GATT_ITER_STOP to stop.
 */
typedef uint8_t (*bt_mesh_gatt_attr_func_t)(const struct bt_mesh_gatt_attr *attr,
                                            void *user_data);

/** @brief Connection callback structure.
 *
 *  This structure is used for tracking the state of a connection.
 *  It is registered with the help of the bt_mesh_gatts_conn_cb_register() API.
 *  It's permissible to register multiple instances of this @ref bt_conn_cb
 *  type, in case different modules of an application are interested in
 *  tracking the connection state. If a callback is not of interest for
 *  an instance, it may be set to NULL and will as a consequence not be
 *  used for that instance.
 */
struct bt_mesh_conn_cb {
    /** @brief A new connection has been established.
     *
     *  This callback notifies the application of a new connection.
     *  In case the err parameter is non-zero it means that the
     *  connection establishment failed.
     *
     *  @param conn New connection object.
     *  @param err HCI error. Zero for success, non-zero otherwise.
     */
    void (*connected)(struct bt_mesh_conn *conn, uint8_t err);

    /** @brief A connection has been disconnected.
     *
     *  This callback notifies the application that a connection
     *  has been disconnected.
     *
     *  @param conn Connection object.
     *  @param reason HCI reason for the disconnection.
     */
    void (*disconnected)(struct bt_mesh_conn *conn, uint8_t reason);
};

struct bt_mesh_prov_conn_cb {
    void (*connected)(bt_mesh_addr_t *addr, struct bt_mesh_conn *conn, int id);

    void (*disconnected)(bt_mesh_addr_t *addr, struct bt_mesh_conn *conn, uint8_t reason);

    ssize_t (*prov_write_descr)(bt_mesh_addr_t *addr, struct bt_mesh_conn *conn);

    ssize_t (*prov_notify)(struct bt_mesh_conn *conn, uint8_t *data, uint16_t len);

    ssize_t (*proxy_write_descr)(bt_mesh_addr_t *addr, struct bt_mesh_conn *conn);

    ssize_t (*proxy_notify)(struct bt_mesh_conn *conn, uint8_t *data, uint16_t len);
};

/** @brief GATT Attribute structure. */
struct bt_mesh_gatt_attr {
    /** Attribute UUID */
    const struct bt_mesh_uuid *uuid;

    /** Attribute read callback
     *
     *  @param conn   The connection that is requesting to read
     *  @param attr   The attribute that's being read
     *  @param buf    Buffer to place the read result in
     *  @param len    Length of data to read
     *  @param offset Offset to start reading from
     *
     *  @return Number of bytes read, or in case of an error
     *          BLE_MESH_GATT_ERR() with a specific ATT error code.
     */
    ssize_t (*read)(struct bt_mesh_conn *conn,
                    const struct bt_mesh_gatt_attr *attr,
                    void *buf, uint16_t len,
                    uint16_t offset);

    /** Attribute write callback
     *
     *  @param conn   The connection that is requesting to write
     *  @param attr   The attribute that's being written
     *  @param buf    Buffer with the data to write
     *  @param len    Number of bytes in the buffer
     *  @param offset Offset to start writing from
     *  @param flags  Flags (BT_GATT_WRITE_*)
     *
     *  @return Number of bytes written, or in case of an error
     *          BLE_MESH_GATT_ERR() with a specific ATT error code.
     */
    ssize_t (*write)(struct bt_mesh_conn *conn,
                     const struct bt_mesh_gatt_attr *attr,
                     const void *buf, uint16_t len,
                     uint16_t offset, uint8_t flags);

    /** Attribute user data */
    void *user_data;
    /** Attribute handle */
    uint16_t handle;
    /** Attribute permissions */
    uint8_t  perm;
};

/** @def BLE_MESH_GATT_PRIMARY_SERVICE
 *  @brief Primary Service Declaration Macro.
 *
 *  Helper macro to declare a primary service attribute.
 *
 *  @param _service Service attribute value.
 */
#define BLE_MESH_GATT_PRIMARY_SERVICE(_service)     \
{                                                   \
    .uuid = BLE_MESH_UUID_GATT_PRIMARY,             \
    .read = bt_mesh_gatts_attr_read_service,        \
    .user_data = _service,                          \
    .perm = BLE_MESH_GATT_PERM_READ,                \
}

/** @def BLE_MESH_GATT_SECONDARY_SERVICE
 *  @brief Secondary Service Declaration Macro.
 *
 *  Helper macro to declare a secondary service attribute.
 *
 *  @param _service Service attribute value.
 */
#define BLE_MESH_GATT_SECONDARY_SERVICE(_service)   \
{                                                   \
    .uuid = BLE_MESH_UUID_GATT_SECONDARY,           \
    .read = bt_mesh_gatts_attr_read_service,        \
    .user_data = _service,                          \
    .perm = BLE_MESH_GATT_PERM_READ,                \
}

/** @def BLE_MESH_GATT_INCLUDE_SERVICE
 *  @brief Include Service Declaration Macro.
 *
 *  Helper macro to declare database internal include service attribute.
 *
 *  @param _service_incl the first service attribute of service to include
 */
#define BLE_MESH_GATT_INCLUDE_SERVICE(_service_incl)    \
{                                                       \
    .uuid = BLE_MESH_UUID_GATT_INCLUDE,                 \
    .read = bt_mesh_gatts_attr_read_included,           \
    .user_data = _service_incl,                         \
    .perm = BLE_MESH_GATT_PERM_READ,                    \
}

/** @def BLE_MESH_GATT_CHARACTERISTIC
 *  @brief Characteristic Declaration Macro.
 *
 *  Helper macro to declare a characteristic attribute.
 *
 *  @param _uuid Characteristic attribute uuid.
 *  @param _props Characteristic attribute properties.
 */
#define BLE_MESH_GATT_CHARACTERISTIC(_uuid, _props)             \
{                                                               \
    .uuid = BLE_MESH_UUID_GATT_CHRC,                            \
    .read = bt_mesh_gatts_attr_read_chrc,                       \
    .user_data = (&(struct bt_mesh_gatt_char) { .uuid = _uuid,  \
                           .properties = _props, }),            \
    .perm = BLE_MESH_GATT_PERM_READ,                            \
}

/** @def BLE_MESH_GATT_DESCRIPTOR
 *  @brief Descriptor Declaration Macro.
 *
 *  Helper macro to declare a descriptor attribute.
 *
 *  @param _uuid Descriptor attribute uuid.
 *  @param _perm Descriptor attribute access permissions.
 *  @param _read Descriptor attribute read callback.
 *  @param _write Descriptor attribute write callback.
 *  @param _value Descriptor attribute value.
 */
#define BLE_MESH_GATT_DESCRIPTOR(_uuid, _perm, _read, _write, _value)   \
{                           \
    .uuid = _uuid,          \
    .read = _read,          \
    .write = _write,        \
    .user_data = _value,    \
    .perm = _perm,          \
}

/** @def BLE_MESH_GATT_SERVICE
 *  @brief Service Structure Declaration Macro.
 *
 *  Helper macro to declare a service structure.
 *
 *  @param _attrs Service attributes.
 */
#define BLE_MESH_GATT_SERVICE(_attrs)   \
{                                       \
    .attrs = _attrs,                    \
    .attr_count = ARRAY_SIZE(_attrs),   \
}

int bt_mesh_host_init(void);
int bt_mesh_host_deinit(void);

#if CONFIG_BLE_MESH_USE_BLE_50
int bt_le_ext_adv_start(const uint8_t inst_id,
                        const struct bt_mesh_adv_param *param,
                        const struct bt_mesh_adv_data *ad, size_t ad_len,
                        const struct bt_mesh_adv_data *sd, size_t sd_len);

#if CONFIG_BLE_MESH_SUPPORT_BLE_ADV
int bt_mesh_ble_ext_adv_start(const uint8_t inst_id,
                              const struct bt_mesh_ble_adv_param *param,
                              const struct bt_mesh_ble_adv_data *adv_data);
#endif /* CONFIG_BLE_MESH_SUPPORT_BLE_ADV */

int bt_le_ext_adv_stop(uint8_t inst_id);

#else /* CONFIG_BLE_MESH_USE_BLE_50 */
int bt_le_adv_start(const struct bt_mesh_adv_param *param,
                    const struct bt_mesh_adv_data *ad, size_t ad_len,
                    const struct bt_mesh_adv_data *sd, size_t sd_len);

#if CONFIG_BLE_MESH_SUPPORT_BLE_ADV
int bt_mesh_ble_adv_start(const struct bt_mesh_ble_adv_param *param,
                          const struct bt_mesh_ble_adv_data *data);
#endif /* CONFIG_BLE_MESH_SUPPORT_BLE_ADV */

int bt_le_adv_stop(void);
#endif /* CONFIG_BLE_MESH_USE_BLE_50 */

int bt_le_scan_start(const struct bt_mesh_scan_param *param, bt_mesh_scan_cb_t cb);

int bt_le_scan_stop(void);

typedef enum {
    BLE_MESH_WHITELIST_REMOVE,
    BLE_MESH_WHITELIST_ADD,
} bt_mesh_wl_operation;

struct bt_mesh_white_list {
    bool add_remove;
    uint8_t remote_bda[BLE_MESH_ADDR_LEN];
    uint8_t addr_type;
    /* For Bluedroid host, this callback is used to notify the
     * result of updating white list.
     */
    void (*update_wl_comp_cb)(uint8_t status, bt_mesh_wl_operation wl_operation);
};

int bt_le_update_white_list(struct bt_mesh_white_list *wl);

void bt_mesh_gatts_conn_cb_register(struct bt_mesh_conn_cb *cb);
void bt_mesh_gatts_conn_cb_deregister(void);

int bt_mesh_gatts_disconnect(struct bt_mesh_conn *conn, uint8_t reason);

int bt_mesh_gatts_service_register(struct bt_mesh_gatt_service *svc);
int bt_mesh_gatts_service_deregister(struct bt_mesh_gatt_service *svc);

int bt_mesh_gatts_service_unregister(struct bt_mesh_gatt_service *svc);

ssize_t bt_mesh_gatts_attr_read_included(struct bt_mesh_conn *conn,
                                         const struct bt_mesh_gatt_attr *attr,
                                         void *buf, uint16_t len, uint16_t offset);

ssize_t bt_mesh_gatts_attr_read(struct bt_mesh_conn *conn,
                                const struct bt_mesh_gatt_attr *attr,
                                void *buf, uint16_t buf_len, uint16_t offset,
                                const void *value, uint16_t value_len);

ssize_t bt_mesh_gatts_attr_read_service(struct bt_mesh_conn *conn,
                                        const struct bt_mesh_gatt_attr *attr,
                                        void *buf, uint16_t len, uint16_t offset);

ssize_t bt_mesh_gatts_attr_read_chrc(struct bt_mesh_conn *conn,
                                     const struct bt_mesh_gatt_attr *attr,
                                     void *buf, uint16_t len, uint16_t offset);

int bt_mesh_gatts_notify(struct bt_mesh_conn *conn,
                         const struct bt_mesh_gatt_attr *attr,
                         const void *data, uint16_t len);

uint16_t bt_mesh_gatt_get_mtu(struct bt_mesh_conn *conn);

/** APIs added by Espressif */
int bt_mesh_gatts_service_stop(struct bt_mesh_gatt_service *svc);
int bt_mesh_gatts_service_start(struct bt_mesh_gatt_service *svc);

int bt_mesh_gatts_set_local_device_name(const char *name);

void bt_mesh_gattc_conn_cb_register(struct bt_mesh_prov_conn_cb *cb);
void bt_mesh_gattc_conn_cb_deregister(void);

uint8_t bt_mesh_gattc_get_free_conn_count(void);

uint16_t bt_mesh_gattc_get_service_uuid(struct bt_mesh_conn *conn);

int bt_mesh_gattc_conn_create(const bt_mesh_addr_t *addr, uint16_t service_uuid);

void bt_gattc_conn_close(struct bt_mesh_conn *conn);

void bt_mesh_gattc_exchange_mtu(uint8_t index);

uint16_t bt_mesh_gattc_get_mtu_info(struct bt_mesh_conn *conn);

int bt_mesh_gattc_write_no_rsp(struct bt_mesh_conn *conn,
                               const struct bt_mesh_gatt_attr *attr,
                               const void *data, uint16_t len);

void bt_mesh_gattc_disconnect(struct bt_mesh_conn *conn);

struct bt_mesh_conn *bt_mesh_conn_ref(struct bt_mesh_conn *conn);

void bt_mesh_conn_unref(struct bt_mesh_conn *conn);

void bt_mesh_gatt_init(void);
void bt_mesh_gatt_deinit(void);

void bt_mesh_adapt_init(void);

void bt_mesh_set_private_key(const uint8_t pri_key[32]);

const uint8_t *bt_mesh_pub_key_get(void);

bool bt_mesh_check_public_key(const uint8_t key[64]);

int bt_mesh_dh_key_gen(const uint8_t remote_pub_key[64], uint8_t dhkey[32]);

int bt_mesh_encrypt_le(const uint8_t key[16], const uint8_t plaintext[16],
                       uint8_t enc_data[16]);

int bt_mesh_encrypt_be(const uint8_t key[16], const uint8_t plaintext[16],
                       uint8_t enc_data[16]);

enum {
    BLE_MESH_EXCEP_LIST_SUB_CODE_ADD = 0,
    BLE_MESH_EXCEP_LIST_SUB_CODE_REMOVE,
    BLE_MESH_EXCEP_LIST_SUB_CODE_CLEAN,
};

enum {
    BLE_MESH_EXCEP_LIST_TYPE_ADV_ADDR = 0,
    BLE_MESH_EXCEP_LIST_TYPE_MESH_LINK_ID,
    BLE_MESH_EXCEP_LIST_TYPE_MESH_BEACON,
    BLE_MESH_EXCEP_LIST_TYPE_MESH_PROV_ADV,
    BLE_MESH_EXCEP_LIST_TYPE_MESH_PROXY_ADV,
    BLE_MESH_EXCEP_LIST_TYPE_MESH_SOLIC_PDU,
    BLE_MESH_EXCEP_LIST_TYPE_MESH_URI,
    BLE_MESH_EXCEP_LIST_TYPE_MAX,
};

#define BLE_MESH_EXCEP_LIST_CLEAN_ADDR_LIST              BIT(0)
#define BLE_MESH_EXCEP_LIST_CLEAN_MESH_LINK_ID_LIST      BIT(1)
#define BLE_MESH_EXCEP_LIST_CLEAN_MESH_BEACON_LIST       BIT(2)
#define BLE_MESH_EXCEP_LIST_CLEAN_MESH_PROV_ADV_LIST     BIT(3)
#define BLE_MESH_EXCEP_LIST_CLEAN_MESH_PROXY_ADV_LIST    BIT(4)
#define BLE_MESH_EXCEP_LIST_CLEAN_MESH_SOLIC_PDU_LIST    BIT(5)
#define BLE_MESH_EXCEP_LIST_CLEAN_MESH_URI_LIST          BIT(6)
#define BLE_MESH_EXCEP_LIST_CLEAN_ALL_LIST               (BIT(0) | BIT(1) | BIT(2) | BIT(3) | \
                                                          BIT(4) | BIT(5) | BIT(6))

int bt_mesh_update_exceptional_list(uint8_t sub_code, uint32_t type, void *info);

#ifdef __cplusplus
}
#endif

#endif /* _BLE_MESH_ADAPTER_H_ */
