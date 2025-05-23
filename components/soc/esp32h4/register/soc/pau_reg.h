/**
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 *  SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#include <stdint.h>
#include "soc/soc.h"
#ifdef __cplusplus
extern "C" {
#endif

/** PAU_REGDMA_CONF_REG register
 *  Peri backup control register
 */
#define PAU_REGDMA_CONF_REG (DR_REG_PAU_BASE + 0x0)
/** PAU_START : WT; bitpos: [3]; default: 0;
 *  backup start signal
 */
#define PAU_START    (BIT(3))
#define PAU_START_M  (PAU_START_V << PAU_START_S)
#define PAU_START_V  0x00000001U
#define PAU_START_S  3
/** PAU_TO_MEM : R/W; bitpos: [4]; default: 0;
 *  backup direction(reg to mem / mem to reg)
 */
#define PAU_TO_MEM    (BIT(4))
#define PAU_TO_MEM_M  (PAU_TO_MEM_V << PAU_TO_MEM_S)
#define PAU_TO_MEM_V  0x00000001U
#define PAU_TO_MEM_S  4
/** PAU_LINK_SEL : R/W; bitpos: [8:5]; default: 0;
 *  Link select
 */
#define PAU_LINK_SEL    0x0000000FU
#define PAU_LINK_SEL_M  (PAU_LINK_SEL_V << PAU_LINK_SEL_S)
#define PAU_LINK_SEL_V  0x0000000FU
#define PAU_LINK_SEL_S  5
/** PAU_SW_RETRY_EN : R/W; bitpos: [9]; default: 0;
 *  sw_retry_en
 */
#define PAU_SW_RETRY_EN    (BIT(9))
#define PAU_SW_RETRY_EN_M  (PAU_SW_RETRY_EN_V << PAU_SW_RETRY_EN_S)
#define PAU_SW_RETRY_EN_V  0x00000001U
#define PAU_SW_RETRY_EN_S  9
/** PAU_PAUDMA_BUSY : RO; bitpos: [10]; default: 0;
 *  regdma_busy
 */
#define PAU_PAUDMA_BUSY    (BIT(10))
#define PAU_PAUDMA_BUSY_M  (PAU_PAUDMA_BUSY_V << PAU_PAUDMA_BUSY_S)
#define PAU_PAUDMA_BUSY_V  0x00000001U
#define PAU_PAUDMA_BUSY_S  10
/** PAU_FIX_PRI_EN : R/W; bitpos: [11]; default: 0;
 *  fix_pri_en
 */
#define PAU_FIX_PRI_EN    (BIT(11))
#define PAU_FIX_PRI_EN_M  (PAU_FIX_PRI_EN_V << PAU_FIX_PRI_EN_S)
#define PAU_FIX_PRI_EN_V  0x00000001U
#define PAU_FIX_PRI_EN_S  11

/** PAU_REGDMA_CLK_CONF_REG register
 *  Clock control register
 */
#define PAU_REGDMA_CLK_CONF_REG (DR_REG_PAU_BASE + 0x4)
/** PAU_CLK_EN : R/W; bitpos: [0]; default: 0;
 *  clock enable
 */
#define PAU_CLK_EN    (BIT(0))
#define PAU_CLK_EN_M  (PAU_CLK_EN_V << PAU_CLK_EN_S)
#define PAU_CLK_EN_V  0x00000001U
#define PAU_CLK_EN_S  0

/** PAU_REGDMA_ETM_CTRL_REG register
 *  ETM start ctrl reg
 */
#define PAU_REGDMA_ETM_CTRL_REG (DR_REG_PAU_BASE + 0x8)
/** PAU_ETM_START_0 : WT; bitpos: [0]; default: 0;
 *  etm_start_0 reg
 */
#define PAU_ETM_START_0    (BIT(0))
#define PAU_ETM_START_0_M  (PAU_ETM_START_0_V << PAU_ETM_START_0_S)
#define PAU_ETM_START_0_V  0x00000001U
#define PAU_ETM_START_0_S  0
/** PAU_ETM_START_1 : WT; bitpos: [1]; default: 0;
 *  etm_start_1 reg
 */
#define PAU_ETM_START_1    (BIT(1))
#define PAU_ETM_START_1_M  (PAU_ETM_START_1_V << PAU_ETM_START_1_S)
#define PAU_ETM_START_1_V  0x00000001U
#define PAU_ETM_START_1_S  1
/** PAU_ETM_START_2 : WT; bitpos: [2]; default: 0;
 *  etm_start_2 reg
 */
#define PAU_ETM_START_2    (BIT(2))
#define PAU_ETM_START_2_M  (PAU_ETM_START_2_V << PAU_ETM_START_2_S)
#define PAU_ETM_START_2_V  0x00000001U
#define PAU_ETM_START_2_S  2
/** PAU_ETM_START_3 : WT; bitpos: [3]; default: 0;
 *  etm_start_3 reg
 */
#define PAU_ETM_START_3    (BIT(3))
#define PAU_ETM_START_3_M  (PAU_ETM_START_3_V << PAU_ETM_START_3_S)
#define PAU_ETM_START_3_V  0x00000001U
#define PAU_ETM_START_3_S  3
/** PAU_ETM_LINK_SEL_0 : R/W; bitpos: [8:4]; default: 0;
 *  etm_link sel
 */
#define PAU_ETM_LINK_SEL_0    0x0000001FU
#define PAU_ETM_LINK_SEL_0_M  (PAU_ETM_LINK_SEL_0_V << PAU_ETM_LINK_SEL_0_S)
#define PAU_ETM_LINK_SEL_0_V  0x0000001FU
#define PAU_ETM_LINK_SEL_0_S  4
/** PAU_ETM_LINK_SEL_1 : R/W; bitpos: [13:9]; default: 0;
 *  etm_link sel
 */
#define PAU_ETM_LINK_SEL_1    0x0000001FU
#define PAU_ETM_LINK_SEL_1_M  (PAU_ETM_LINK_SEL_1_V << PAU_ETM_LINK_SEL_1_S)
#define PAU_ETM_LINK_SEL_1_V  0x0000001FU
#define PAU_ETM_LINK_SEL_1_S  9
/** PAU_ETM_LINK_SEL_2 : R/W; bitpos: [18:14]; default: 0;
 *  etm_link sel
 */
#define PAU_ETM_LINK_SEL_2    0x0000001FU
#define PAU_ETM_LINK_SEL_2_M  (PAU_ETM_LINK_SEL_2_V << PAU_ETM_LINK_SEL_2_S)
#define PAU_ETM_LINK_SEL_2_V  0x0000001FU
#define PAU_ETM_LINK_SEL_2_S  14
/** PAU_ETM_LINK_SEL_3 : R/W; bitpos: [23:19]; default: 0;
 *  etm_link sel
 */
#define PAU_ETM_LINK_SEL_3    0x0000001FU
#define PAU_ETM_LINK_SEL_3_M  (PAU_ETM_LINK_SEL_3_V << PAU_ETM_LINK_SEL_3_S)
#define PAU_ETM_LINK_SEL_3_V  0x0000001FU
#define PAU_ETM_LINK_SEL_3_S  19
/** PAU_ETM_RETRY_EN_0 : R/W; bitpos: [24]; default: 0;
 *  etm_retry
 */
#define PAU_ETM_RETRY_EN_0    (BIT(24))
#define PAU_ETM_RETRY_EN_0_M  (PAU_ETM_RETRY_EN_0_V << PAU_ETM_RETRY_EN_0_S)
#define PAU_ETM_RETRY_EN_0_V  0x00000001U
#define PAU_ETM_RETRY_EN_0_S  24
/** PAU_ETM_RETRY_EN_1 : R/W; bitpos: [25]; default: 0;
 *  etm_retry
 */
#define PAU_ETM_RETRY_EN_1    (BIT(25))
#define PAU_ETM_RETRY_EN_1_M  (PAU_ETM_RETRY_EN_1_V << PAU_ETM_RETRY_EN_1_S)
#define PAU_ETM_RETRY_EN_1_V  0x00000001U
#define PAU_ETM_RETRY_EN_1_S  25
/** PAU_ETM_RETRY_EN_2 : R/W; bitpos: [26]; default: 0;
 *  etm_retry
 */
#define PAU_ETM_RETRY_EN_2    (BIT(26))
#define PAU_ETM_RETRY_EN_2_M  (PAU_ETM_RETRY_EN_2_V << PAU_ETM_RETRY_EN_2_S)
#define PAU_ETM_RETRY_EN_2_V  0x00000001U
#define PAU_ETM_RETRY_EN_2_S  26
/** PAU_ETM_RETRY_EN_3 : R/W; bitpos: [27]; default: 0;
 *  etm_retry
 */
#define PAU_ETM_RETRY_EN_3    (BIT(27))
#define PAU_ETM_RETRY_EN_3_M  (PAU_ETM_RETRY_EN_3_V << PAU_ETM_RETRY_EN_3_S)
#define PAU_ETM_RETRY_EN_3_V  0x00000001U
#define PAU_ETM_RETRY_EN_3_S  27

/** PAU_REGDMA_CURRENT_LINK_ADDR_REG register
 *  current link addr
 */
#define PAU_REGDMA_CURRENT_LINK_ADDR_REG (DR_REG_PAU_BASE + 0xc)
/** PAU_CURRENT_LINK_ADDR : RO; bitpos: [31:0]; default: 0;
 *  current link addr reg
 */
#define PAU_CURRENT_LINK_ADDR    0xFFFFFFFFU
#define PAU_CURRENT_LINK_ADDR_M  (PAU_CURRENT_LINK_ADDR_V << PAU_CURRENT_LINK_ADDR_S)
#define PAU_CURRENT_LINK_ADDR_V  0xFFFFFFFFU
#define PAU_CURRENT_LINK_ADDR_S  0

/** PAU_REGDMA_PERI_ADDR_REG register
 *  Backup addr
 */
#define PAU_REGDMA_PERI_ADDR_REG (DR_REG_PAU_BASE + 0x10)
/** PAU_PERI_ADDR : RO; bitpos: [31:0]; default: 0;
 *  peri addr reg
 */
#define PAU_PERI_ADDR    0xFFFFFFFFU
#define PAU_PERI_ADDR_M  (PAU_PERI_ADDR_V << PAU_PERI_ADDR_S)
#define PAU_PERI_ADDR_V  0xFFFFFFFFU
#define PAU_PERI_ADDR_S  0

/** PAU_REGDMA_MEM_ADDR_REG register
 *  mem addr
 */
#define PAU_REGDMA_MEM_ADDR_REG (DR_REG_PAU_BASE + 0x14)
/** PAU_MEM_ADDR : RO; bitpos: [31:0]; default: 0;
 *  mem addr reg
 */
#define PAU_MEM_ADDR    0xFFFFFFFFU
#define PAU_MEM_ADDR_M  (PAU_MEM_ADDR_V << PAU_MEM_ADDR_S)
#define PAU_MEM_ADDR_V  0xFFFFFFFFU
#define PAU_MEM_ADDR_S  0

/** PAU_INT_ENA_REG register
 *  Read only register for error and done
 */
#define PAU_INT_ENA_REG (DR_REG_PAU_BASE + 0x18)
/** PAU_DONE_INT_ENA : R/W; bitpos: [0]; default: 0;
 *  backup done flag
 */
#define PAU_DONE_INT_ENA    (BIT(0))
#define PAU_DONE_INT_ENA_M  (PAU_DONE_INT_ENA_V << PAU_DONE_INT_ENA_S)
#define PAU_DONE_INT_ENA_V  0x00000001U
#define PAU_DONE_INT_ENA_S  0
/** PAU_ERROR_INT_ENA : R/W; bitpos: [1]; default: 0;
 *  error flag
 */
#define PAU_ERROR_INT_ENA    (BIT(1))
#define PAU_ERROR_INT_ENA_M  (PAU_ERROR_INT_ENA_V << PAU_ERROR_INT_ENA_S)
#define PAU_ERROR_INT_ENA_V  0x00000001U
#define PAU_ERROR_INT_ENA_S  1

/** PAU_INT_RAW_REG register
 *  Read only register for error and done
 */
#define PAU_INT_RAW_REG (DR_REG_PAU_BASE + 0x1c)
/** PAU_DONE_INT_RAW : R/WTC/SS; bitpos: [0]; default: 0;
 *  backup done flag
 */
#define PAU_DONE_INT_RAW    (BIT(0))
#define PAU_DONE_INT_RAW_M  (PAU_DONE_INT_RAW_V << PAU_DONE_INT_RAW_S)
#define PAU_DONE_INT_RAW_V  0x00000001U
#define PAU_DONE_INT_RAW_S  0
/** PAU_ERROR_INT_RAW : R/WTC/SS; bitpos: [1]; default: 0;
 *  error flag
 */
#define PAU_ERROR_INT_RAW    (BIT(1))
#define PAU_ERROR_INT_RAW_M  (PAU_ERROR_INT_RAW_V << PAU_ERROR_INT_RAW_S)
#define PAU_ERROR_INT_RAW_V  0x00000001U
#define PAU_ERROR_INT_RAW_S  1

/** PAU_INT_CLR_REG register
 *  Read only register for error and done
 */
#define PAU_INT_CLR_REG (DR_REG_PAU_BASE + 0x20)
/** PAU_DONE_INT_CLR : WT; bitpos: [0]; default: 0;
 *  backup done flag
 */
#define PAU_DONE_INT_CLR    (BIT(0))
#define PAU_DONE_INT_CLR_M  (PAU_DONE_INT_CLR_V << PAU_DONE_INT_CLR_S)
#define PAU_DONE_INT_CLR_V  0x00000001U
#define PAU_DONE_INT_CLR_S  0
/** PAU_ERROR_INT_CLR : WT; bitpos: [1]; default: 0;
 *  error flag
 */
#define PAU_ERROR_INT_CLR    (BIT(1))
#define PAU_ERROR_INT_CLR_M  (PAU_ERROR_INT_CLR_V << PAU_ERROR_INT_CLR_S)
#define PAU_ERROR_INT_CLR_V  0x00000001U
#define PAU_ERROR_INT_CLR_S  1

/** PAU_INT_ST_REG register
 *  Read only register for error and done
 */
#define PAU_INT_ST_REG (DR_REG_PAU_BASE + 0x24)
/** PAU_DONE_INT_ST : RO; bitpos: [0]; default: 0;
 *  backup done flag
 */
#define PAU_DONE_INT_ST    (BIT(0))
#define PAU_DONE_INT_ST_M  (PAU_DONE_INT_ST_V << PAU_DONE_INT_ST_S)
#define PAU_DONE_INT_ST_V  0x00000001U
#define PAU_DONE_INT_ST_S  0
/** PAU_ERROR_INT_ST : RO; bitpos: [1]; default: 0;
 *  error flag
 */
#define PAU_ERROR_INT_ST    (BIT(1))
#define PAU_ERROR_INT_ST_M  (PAU_ERROR_INT_ST_V << PAU_ERROR_INT_ST_S)
#define PAU_ERROR_INT_ST_V  0x00000001U
#define PAU_ERROR_INT_ST_S  1

/** PAU_REGDMA_GRANT_RESULT_REG register
 *  Read only register for error and done
 */
#define PAU_REGDMA_GRANT_RESULT_REG (DR_REG_PAU_BASE + 0x28)
/** PAU_GRANT_START_RESULT : RO; bitpos: [6:0]; default: 0;
 *  Grant start result
 */
#define PAU_GRANT_START_RESULT    0x0000007FU
#define PAU_GRANT_START_RESULT_M  (PAU_GRANT_START_RESULT_V << PAU_GRANT_START_RESULT_S)
#define PAU_GRANT_START_RESULT_V  0x0000007FU
#define PAU_GRANT_START_RESULT_S  0
/** PAU_GRANT_DONE_RESULT : RO; bitpos: [13:7]; default: 0;
 *  Grant done result
 */
#define PAU_GRANT_DONE_RESULT    0x0000007FU
#define PAU_GRANT_DONE_RESULT_M  (PAU_GRANT_DONE_RESULT_V << PAU_GRANT_DONE_RESULT_S)
#define PAU_GRANT_DONE_RESULT_V  0x0000007FU
#define PAU_GRANT_DONE_RESULT_S  7
/** PAU_GRANT_RESULT_CLR : WT; bitpos: [14]; default: 0;
 *  Grant result clear
 */
#define PAU_GRANT_RESULT_CLR    (BIT(14))
#define PAU_GRANT_RESULT_CLR_M  (PAU_GRANT_RESULT_CLR_V << PAU_GRANT_RESULT_CLR_S)
#define PAU_GRANT_RESULT_CLR_V  0x00000001U
#define PAU_GRANT_RESULT_CLR_S  14

/** PAU_DATE_REG register
 *  Date register.
 */
#define PAU_DATE_REG (DR_REG_PAU_BASE + 0x3fc)
/** PAU_DATE : R/W; bitpos: [27:0]; default: 37765760;
 *  REGDMA date information/ REGDMA version information.
 */
#define PAU_DATE    0x0FFFFFFFU
#define PAU_DATE_M  (PAU_DATE_V << PAU_DATE_S)
#define PAU_DATE_V  0x0FFFFFFFU
#define PAU_DATE_S  0

#ifdef __cplusplus
}
#endif
