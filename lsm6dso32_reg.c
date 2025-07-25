/**
  ******************************************************************************
  * @file    lsm6dso32_reg.c
  * @author  Sensors Software Solution Team
  * @brief   LSM6DSO32 driver file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include "lsm6dso32_reg.h"

/**
  * @defgroup  LSM6DSO32
  * @brief     This file provides a set of functions needed to drive the
  *            lsm6dso32 enhanced inertial module.
  * @{
  *
  */

/**
  * @defgroup  LSM6DSO32_Interfaces_Functions
  * @brief     This section provide a set of functions used to read and
  *            write a generic register of the device.
  *            MANDATORY: return 0 -> no Error.
  * @{
  *
  */

/**
  * @brief  Read generic device register
  *
  * @param  ctx   read / write interface definitions(ptr)
  * @param  reg   register to read
  * @param  data  pointer to buffer that store the data read(ptr)
  * @param  len   number of consecutive register to read
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t __weak lsm6dso32_read_reg(const stmdev_ctx_t *ctx, uint8_t reg,
                                  uint8_t *data,
                                  uint16_t len)
{
  int32_t ret;

  if (ctx == NULL) return -1;

  ret = ctx->read_reg(ctx->handle, reg, data, len);

  return ret;
}

/**
  * @brief  Write generic device register
  *
  * @param  ctx   read / write interface definitions(ptr)
  * @param  reg   register to write
  * @param  data  pointer to data to write in register reg(ptr)
  * @param  len   number of consecutive register to write
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t __weak lsm6dso32_write_reg(const stmdev_ctx_t *ctx, uint8_t reg,
                                   uint8_t *data,
                                   uint16_t len)
{
  int32_t ret;

  if (ctx == NULL) return -1;

  ret = ctx->write_reg(ctx->handle, reg, data, len);

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  LSM6DSO32_Sensitivity
  * @brief     These functions convert raw-data into engineering units.
  * @{
  *
  */
float_t lsm6dso32_from_fs4_to_mg(int16_t lsb)
{
  return ((float_t)lsb) * 0.122f;
}

float_t lsm6dso32_from_fs8_to_mg(int16_t lsb)
{
  return ((float_t)lsb) * 0.244f;
}

float_t lsm6dso32_from_fs16_to_mg(int16_t lsb)
{
  return ((float_t)lsb) * 0.488f;
}

float_t lsm6dso32_from_fs32_to_mg(int16_t lsb)
{
  return ((float_t)lsb) * 0.976f;
}

float_t lsm6dso32_from_fs125_to_mdps(int16_t lsb)
{
  return ((float_t)lsb) * 4.375f;
}

float_t lsm6dso32_from_fs250_to_mdps(int16_t lsb)
{
  return ((float_t)lsb) * 8.75f;
}

float_t lsm6dso32_from_fs500_to_mdps(int16_t lsb)
{
  return ((float_t)lsb) * 17.50f;
}

float_t lsm6dso32_from_fs1000_to_mdps(int16_t lsb)
{
  return ((float_t)lsb) * 35.0f;
}

float_t lsm6dso32_from_fs2000_to_mdps(int16_t lsb)
{
  return ((float_t)lsb) * 70.0f;
}

float_t lsm6dso32_from_lsb_to_celsius(int16_t lsb)
{
  return (((float_t)lsb / 256.0f) + 25.0f);
}

float_t lsm6dso32_from_lsb_to_nsec(int16_t lsb)
{
  return ((float_t)lsb * 25000.0f);
}

/**
  * @}
  *
  */

/**
  * @defgroup  LSM6DSO32_Data_Generation
  * @brief     This section groups all the functions concerning
  *            data generation.
  *
  */

/**
  * @brief  Accelerometer full-scale selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of fs_xl in reg CTRL1_XL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_full_scale_set(const stmdev_ctx_t *ctx,
                                    lsm6dso32_fs_xl_t val)
{
  lsm6dso32_ctrl1_xl_t ctrl1_xl;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL1_XL,
                           (uint8_t *)&ctrl1_xl, 1);

  if (ret == 0)
  {
    ctrl1_xl.fs_xl = (uint8_t) val & 0x03U;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL1_XL,
                              (uint8_t *)&ctrl1_xl, 1);
  }

  return ret;
}

/**
  * @brief  Accelerometer full-scale selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of fs_xl in reg CTRL1_XL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_full_scale_get(const stmdev_ctx_t *ctx,
                                    lsm6dso32_fs_xl_t *val)
{
  lsm6dso32_ctrl1_xl_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL1_XL, (uint8_t *)&reg, 1);

  switch (reg.fs_xl)
  {
    case LSM6DSO32_4g:
      *val = LSM6DSO32_4g;
      break;

    case LSM6DSO32_8g:
      *val = LSM6DSO32_8g;
      break;

    case LSM6DSO32_16g:
      *val = LSM6DSO32_16g;
      break;

    case LSM6DSO32_32g:
      *val = LSM6DSO32_32g;
      break;

    default:
      *val = LSM6DSO32_4g;
      break;
  }

  return ret;
}

/**
  * @brief  Accelerometer UI data rate and power mode selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Change the data rate and the power mode of
  *                  the accelerometer
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_data_rate_set(const stmdev_ctx_t *ctx,
                                   lsm6dso32_odr_xl_t val)
{
  lsm6dso32_ctrl1_xl_t ctrl1_xl;
  lsm6dso32_ctrl5_c_t ctrl5_c;
  lsm6dso32_ctrl6_c_t ctrl6_c;
  lsm6dso32_func_cfg_access_t func_cfg_access;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL1_XL,
                           (uint8_t *)&ctrl1_xl, 1);

  if (ret == 0)
  {
    ctrl1_xl.odr_xl = (uint8_t) LSM6DSO32_XL_ODR_OFF & 0x0FU;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL1_XL,
                              (uint8_t *)&ctrl1_xl, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FUNC_CFG_ACCESS,
                             (uint8_t *)&func_cfg_access, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL5_C, (uint8_t *) &ctrl5_c, 1);
  }

  if (ret == 0)
  {
    ctrl5_c.xl_ulp_en = ((uint8_t)val & 0x20U) >> 5;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL5_C,
                              (uint8_t *) &ctrl5_c, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL6_C, (uint8_t *) &ctrl6_c, 1);
  }

  if (ret == 0)
  {
    ctrl6_c.xl_hm_mode = ((uint8_t)val & 0x10U) >> 4;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL6_C,
                              (uint8_t *) &ctrl6_c, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL1_XL,
                             (uint8_t *)&ctrl1_xl, 1);
  }

  if (ret == 0)
  {
    ctrl1_xl.odr_xl = (uint8_t) val & 0x0FU;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL1_XL,
                              (uint8_t *)&ctrl1_xl, 1);
  }

  return ret;
}

/**
  * @brief  Accelerometer UI data rate selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the data rate and the power mode of
  *                  the accelerometer
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_data_rate_get(const stmdev_ctx_t *ctx,
                                   lsm6dso32_odr_xl_t *val)
{
  lsm6dso32_ctrl1_xl_t ctrl1_xl;
  lsm6dso32_ctrl5_c_t ctrl5_c;
  lsm6dso32_ctrl6_c_t ctrl6_c;
  lsm6dso32_func_cfg_access_t func_cfg_access;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL1_XL,
                           (uint8_t *)&ctrl1_xl, 1);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FUNC_CFG_ACCESS,
                             (uint8_t *)&func_cfg_access, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL5_C, (uint8_t *) &ctrl5_c, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL6_C, (uint8_t *) &ctrl6_c, 1);
  }

  switch ((ctrl5_c.xl_ulp_en << 5) + (ctrl6_c.xl_hm_mode << 4) +
          ctrl1_xl.odr_xl)
  {
    case LSM6DSO32_XL_ODR_OFF:
      *val = LSM6DSO32_XL_ODR_OFF;
      break;

    case LSM6DSO32_XL_ODR_1Hz6_LOW_PW:
      *val = LSM6DSO32_XL_ODR_1Hz6_LOW_PW;
      break;

    case LSM6DSO32_XL_ODR_12Hz5_LOW_PW:
      *val = LSM6DSO32_XL_ODR_12Hz5_LOW_PW;
      break;

    case LSM6DSO32_XL_ODR_26Hz_LOW_PW:
      *val = LSM6DSO32_XL_ODR_26Hz_LOW_PW;
      break;

    case LSM6DSO32_XL_ODR_52Hz_LOW_PW:
      *val = LSM6DSO32_XL_ODR_52Hz_LOW_PW;
      break;

    case LSM6DSO32_XL_ODR_104Hz_NORMAL_MD:
      *val = LSM6DSO32_XL_ODR_104Hz_NORMAL_MD;
      break;

    case LSM6DSO32_XL_ODR_208Hz_NORMAL_MD:
      *val = LSM6DSO32_XL_ODR_208Hz_NORMAL_MD;
      break;

    case LSM6DSO32_XL_ODR_12Hz5_HIGH_PERF:
      *val = LSM6DSO32_XL_ODR_12Hz5_HIGH_PERF;
      break;

    case LSM6DSO32_XL_ODR_26Hz_HIGH_PERF:
      *val = LSM6DSO32_XL_ODR_26Hz_HIGH_PERF;
      break;

    case LSM6DSO32_XL_ODR_52Hz_HIGH_PERF:
      *val = LSM6DSO32_XL_ODR_52Hz_HIGH_PERF;
      break;

    case LSM6DSO32_XL_ODR_104Hz_HIGH_PERF:
      *val = LSM6DSO32_XL_ODR_104Hz_HIGH_PERF;
      break;

    case LSM6DSO32_XL_ODR_208Hz_HIGH_PERF:
      *val = LSM6DSO32_XL_ODR_208Hz_HIGH_PERF;
      break;

    case LSM6DSO32_XL_ODR_417Hz_HIGH_PERF:
      *val = LSM6DSO32_XL_ODR_417Hz_HIGH_PERF;
      break;

    case LSM6DSO32_XL_ODR_833Hz_HIGH_PERF:
      *val = LSM6DSO32_XL_ODR_833Hz_HIGH_PERF;
      break;

    case LSM6DSO32_XL_ODR_1667Hz_HIGH_PERF:
      *val = LSM6DSO32_XL_ODR_1667Hz_HIGH_PERF;
      break;

    case LSM6DSO32_XL_ODR_3333Hz_HIGH_PERF:
      *val = LSM6DSO32_XL_ODR_3333Hz_HIGH_PERF;
      break;

    case LSM6DSO32_XL_ODR_6667Hz_HIGH_PERF:
      *val = LSM6DSO32_XL_ODR_6667Hz_HIGH_PERF;
      break;

    case LSM6DSO32_XL_ODR_1Hz6_ULTRA_LOW_PW:
      *val = LSM6DSO32_XL_ODR_1Hz6_ULTRA_LOW_PW;
      break;

    case LSM6DSO32_XL_ODR_12Hz5_ULTRA_LOW_PW:
      *val = LSM6DSO32_XL_ODR_12Hz5_ULTRA_LOW_PW;
      break;

    case LSM6DSO32_XL_ODR_26Hz_ULTRA_LOW_PW:
      *val = LSM6DSO32_XL_ODR_26Hz_ULTRA_LOW_PW;
      break;

    case LSM6DSO32_XL_ODR_52Hz_ULTRA_LOW_PW:
      *val = LSM6DSO32_XL_ODR_52Hz_ULTRA_LOW_PW;
      break;

    case LSM6DSO32_XL_ODR_104Hz_ULTRA_LOW_PW:
      *val = LSM6DSO32_XL_ODR_104Hz_ULTRA_LOW_PW;
      break;

    case LSM6DSO32_XL_ODR_208Hz_ULTRA_LOW_PW:
      *val = LSM6DSO32_XL_ODR_208Hz_ULTRA_LOW_PW;
      break;

    default:
      *val = LSM6DSO32_XL_ODR_OFF;
      break;
  }

  return ret;
}

/**
  * @brief  Gyroscope UI chain full-scale selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of fs_g in reg CTRL2_G
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_gy_full_scale_set(const stmdev_ctx_t *ctx,
                                    lsm6dso32_fs_g_t val)
{
  lsm6dso32_ctrl2_g_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL2_G, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.fs_g = (uint8_t) val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL2_G, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Gyroscope UI chain full-scale selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of fs_g in reg CTRL2_G
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_gy_full_scale_get(const stmdev_ctx_t *ctx,
                                    lsm6dso32_fs_g_t *val)
{
  lsm6dso32_ctrl2_g_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL2_G, (uint8_t *)&reg, 1);

  switch (reg.fs_g)
  {
    case LSM6DSO32_250dps:
      *val = LSM6DSO32_250dps;
      break;

    case LSM6DSO32_125dps:
      *val = LSM6DSO32_125dps;
      break;

    case LSM6DSO32_500dps:
      *val = LSM6DSO32_500dps;
      break;

    case LSM6DSO32_1000dps:
      *val = LSM6DSO32_1000dps;
      break;

    case LSM6DSO32_2000dps:
      *val = LSM6DSO32_2000dps;
      break;

    default:
      *val = LSM6DSO32_250dps;
      break;
  }

  return ret;
}

/**
  * @brief  Gyroscope UI data rate selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of odr_g in reg CTRL2_G
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_gy_data_rate_set(const stmdev_ctx_t *ctx,
                                   lsm6dso32_odr_g_t val)
{
  lsm6dso32_ctrl2_g_t ctrl2_g;
  lsm6dso32_ctrl7_g_t ctrl7_g;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL2_G, (uint8_t *)&ctrl2_g, 1);

  if (ret == 0)
  {
    ctrl2_g.odr_g = (uint8_t) LSM6DSO32_GY_ODR_OFF & 0x0FU;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL2_G, (uint8_t *)&ctrl2_g, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL7_G, (uint8_t *)&ctrl7_g, 1);
  }

  if (ret == 0)
  {
    ctrl7_g.g_hm_mode = ((uint8_t)val & 0x10U) >> 4;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL7_G, (uint8_t *)&ctrl7_g, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL2_G, (uint8_t *)&ctrl2_g, 1);
  }

  if (ret == 0)
  {
    ctrl2_g.odr_g = (uint8_t)val & 0x0FU;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL2_G, (uint8_t *)&ctrl2_g, 1);
  }

  return ret;
}

/**
  * @brief  Gyroscope UI data rate selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of odr_g in reg CTRL2_G
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_gy_data_rate_get(const stmdev_ctx_t *ctx,
                                   lsm6dso32_odr_g_t *val)
{
  lsm6dso32_ctrl2_g_t ctrl2_g;
  lsm6dso32_ctrl7_g_t ctrl7_g;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL7_G, (uint8_t *)&ctrl7_g, 1);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL2_G, (uint8_t *)&ctrl2_g, 1);
  }

  switch ((ctrl7_g.g_hm_mode << 4) + ctrl2_g.odr_g)
  {
    case LSM6DSO32_GY_ODR_OFF:
      *val = LSM6DSO32_GY_ODR_OFF;
      break;

    case LSM6DSO32_GY_ODR_12Hz5_HIGH_PERF:
      *val = LSM6DSO32_GY_ODR_12Hz5_HIGH_PERF;
      break;

    case LSM6DSO32_GY_ODR_26Hz_HIGH_PERF:
      *val = LSM6DSO32_GY_ODR_26Hz_HIGH_PERF;
      break;

    case LSM6DSO32_GY_ODR_52Hz_HIGH_PERF:
      *val = LSM6DSO32_GY_ODR_52Hz_HIGH_PERF;
      break;

    case LSM6DSO32_GY_ODR_104Hz_HIGH_PERF:
      *val = LSM6DSO32_GY_ODR_104Hz_HIGH_PERF;
      break;

    case LSM6DSO32_GY_ODR_208Hz_HIGH_PERF:
      *val = LSM6DSO32_GY_ODR_208Hz_HIGH_PERF;
      break;

    case LSM6DSO32_GY_ODR_417Hz_HIGH_PERF:
      *val = LSM6DSO32_GY_ODR_417Hz_HIGH_PERF;
      break;

    case LSM6DSO32_GY_ODR_833Hz_HIGH_PERF:
      *val = LSM6DSO32_GY_ODR_833Hz_HIGH_PERF;
      break;

    case LSM6DSO32_GY_ODR_1667Hz_HIGH_PERF:
      *val = LSM6DSO32_GY_ODR_1667Hz_HIGH_PERF;
      break;

    case LSM6DSO32_GY_ODR_3333Hz_HIGH_PERF:
      *val = LSM6DSO32_GY_ODR_3333Hz_HIGH_PERF;
      break;

    case LSM6DSO32_GY_ODR_6667Hz_HIGH_PERF:
      *val = LSM6DSO32_GY_ODR_6667Hz_HIGH_PERF;
      break;

    case LSM6DSO32_GY_ODR_104Hz_NORMAL_MD:
      *val = LSM6DSO32_GY_ODR_104Hz_NORMAL_MD;
      break;

    case LSM6DSO32_GY_ODR_208Hz_NORMAL_MD:
      *val = LSM6DSO32_GY_ODR_208Hz_NORMAL_MD;
      break;

    case LSM6DSO32_GY_ODR_12Hz5_LOW_PW:
      *val = LSM6DSO32_GY_ODR_12Hz5_LOW_PW;
      break;

    case LSM6DSO32_GY_ODR_26Hz_LOW_PW:
      *val = LSM6DSO32_GY_ODR_26Hz_LOW_PW;
      break;

    case LSM6DSO32_GY_ODR_52Hz_LOW_PW:
      *val = LSM6DSO32_GY_ODR_52Hz_LOW_PW;
      break;

    default:
      *val = LSM6DSO32_GY_ODR_OFF;
      break;
  }

  return ret;
}

/**
  * @brief  Block data update.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of bdu in reg CTRL3_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_block_data_update_set(const stmdev_ctx_t *ctx,
                                        uint8_t val)
{
  lsm6dso32_ctrl3_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL3_C, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.bdu = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL3_C, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Block data update.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of bdu in reg CTRL3_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_block_data_update_get(const stmdev_ctx_t *ctx,
                                        uint8_t *val)
{
  lsm6dso32_ctrl3_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL3_C, (uint8_t *)&reg, 1);
  *val = reg.bdu;

  return ret;
}

/**
  * @brief  Weight of XL user offset bits of registers X_OFS_USR (73h),
  *         Y_OFS_USR (74h), Z_OFS_USR (75h).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of usr_off_w in reg CTRL6_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_offset_weight_set(const stmdev_ctx_t *ctx,
                                       lsm6dso32_usr_off_w_t val)
{
  lsm6dso32_ctrl6_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL6_C, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.usr_off_w = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL6_C, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief    Weight of XL user offset bits of registers X_OFS_USR (73h),
  *           Y_OFS_USR (74h), Z_OFS_USR (75h).[get]
  *
  * @param    ctx      read / write interface definitions
  * @param    val      Get the values of usr_off_w in reg CTRL6_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_offset_weight_get(const stmdev_ctx_t *ctx,
                                       lsm6dso32_usr_off_w_t *val)
{
  lsm6dso32_ctrl6_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL6_C, (uint8_t *)&reg, 1);

  switch (reg.usr_off_w)
  {
    case LSM6DSO32_LSb_1mg:
      *val = LSM6DSO32_LSb_1mg;
      break;

    case LSM6DSO32_LSb_16mg:
      *val = LSM6DSO32_LSb_16mg;
      break;

    default:
      *val = LSM6DSO32_LSb_1mg;
      break;
  }

  return ret;
}

/**
  * @brief  Read all the interrupt flag of the device.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      registers ALL_INT_SRC; WAKE_UP_SRC;
  *                              TAP_SRC; D6D_SRC; STATUS_REG;
  *                              EMB_FUNC_STATUS; FSM_STATUS_A/B
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_all_sources_get(const stmdev_ctx_t *ctx,
                                  lsm6dso32_all_sources_t *val)
{
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_ALL_INT_SRC,
                           (uint8_t *)&val->all_int_src, 1);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_WAKE_UP_SRC,
                             (uint8_t *)&val->wake_up_src, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_SRC,
                             (uint8_t *)&val->tap_src, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_D6D_SRC,
                             (uint8_t *)&val->d6d_src, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_STATUS_REG,
                             (uint8_t *)&val->status_reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_STATUS,
                             (uint8_t *)&val->emb_func_status, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FSM_STATUS_A,
                             (uint8_t *)&val->fsm_status_a, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FSM_STATUS_B,
                             (uint8_t *)&val->fsm_status_b, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  The STATUS_REG register is read by the primary interface.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      register STATUS_REG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_status_reg_get(const stmdev_ctx_t *ctx,
                                 lsm6dso32_status_reg_t *val)
{
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_STATUS_REG, (uint8_t *) val, 1);

  return ret;
}

/**
  * @brief  Accelerometer new data available.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of xlda in reg STATUS_REG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_flag_data_ready_get(const stmdev_ctx_t *ctx,
                                         uint8_t *val)
{
  lsm6dso32_status_reg_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_STATUS_REG, (uint8_t *)&reg, 1);
  *val = reg.xlda;

  return ret;
}

/**
  * @brief  Gyroscope new data available.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of gda in reg STATUS_REG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_gy_flag_data_ready_get(const stmdev_ctx_t *ctx,
                                         uint8_t *val)
{
  lsm6dso32_status_reg_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_STATUS_REG, (uint8_t *)&reg, 1);
  *val = reg.gda;

  return ret;
}

/**
  * @brief  Temperature new data available.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of tda in reg STATUS_REG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_temp_flag_data_ready_get(const stmdev_ctx_t *ctx,
                                           uint8_t *val)
{
  lsm6dso32_status_reg_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_STATUS_REG, (uint8_t *)&reg, 1);
  *val = reg.tda;

  return ret;
}

/**
  * @brief  Accelerometer X-axis user offset correction expressed in
  *         two's complement, weight depends on USR_OFF_W in CTRL6_C (15h).
  *         The value must be in the range [-127 127].[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that contains data to write
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_usr_offset_x_set(const stmdev_ctx_t *ctx,
                                      uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dso32_write_reg(ctx, LSM6DSO32_X_OFS_USR, buff, 1);

  return ret;
}

/**
  * @brief  Accelerometer X-axis user offset correction expressed in two's
  *         complement, weight depends on USR_OFF_W in CTRL6_C (15h).
  *         The value must be in the range [-127 127].[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that stores data read
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_usr_offset_x_get(const stmdev_ctx_t *ctx,
                                      uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_X_OFS_USR, buff, 1);

  return ret;
}

/**
  * @brief  Accelerometer Y-axis user offset correction expressed in two's
  *         complement, weight depends on USR_OFF_W in CTRL6_C (15h).
  *         The value must be in the range [-127 127].[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that contains data to write
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_usr_offset_y_set(const stmdev_ctx_t *ctx,
                                      uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dso32_write_reg(ctx, LSM6DSO32_Y_OFS_USR, buff, 1);

  return ret;
}

/**
  * @brief  Accelerometer Y-axis user offset correction expressed in two's
  *         complement, weight depends on USR_OFF_W in CTRL6_C (15h).
  *         The value must be in the range [-127 127].[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that stores data read
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_usr_offset_y_get(const stmdev_ctx_t *ctx,
                                      uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_Y_OFS_USR, buff, 1);

  return ret;
}

/**
  * @brief  Accelerometer Z-axis user offset correction expressed in two's
  *         complement, weight depends on USR_OFF_W in CTRL6_C (15h).
  *         The value must be in the range [-127 127].[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that contains data to write
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_usr_offset_z_set(const stmdev_ctx_t *ctx,
                                      uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dso32_write_reg(ctx, LSM6DSO32_Z_OFS_USR, buff, 1);

  return ret;
}

/**
  * @brief  Accelerometer Z-axis user offset correction expressed in two's
  *         complement, weight depends on USR_OFF_W in CTRL6_C (15h).
  *         The value must be in the range [-127 127].[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that stores data read
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_usr_offset_z_get(const stmdev_ctx_t *ctx,
                                      uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_Z_OFS_USR, buff, 1);

  return ret;
}

/**
  * @brief  Enables user offset on out.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of usr_off_on_out in reg CTRL7_G
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_usr_offset_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_ctrl7_g_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL7_G, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.usr_off_on_out = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL7_G, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  User offset on out flag.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      values of usr_off_on_out in reg CTRL7_G
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_usr_offset_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_ctrl7_g_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL7_G, (uint8_t *)&reg, 1);
  *val = reg.usr_off_on_out;

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  LSM6DSO32_Timestamp
  * @brief     This section groups all the functions that manage the
  *            timestamp generation.
  * @{
  *
  */

/**
  * @brief  Enables timestamp counter.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of timestamp_en in reg CTRL10_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_timestamp_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_ctrl10_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL10_C, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.timestamp_en = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL10_C, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Enables timestamp counter.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of timestamp_en in reg CTRL10_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_timestamp_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_ctrl10_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL10_C, (uint8_t *)&reg, 1);
  *val = reg.timestamp_en;

  return ret;
}

/**
  * @brief  Timestamp first data output register (r).
  *         The value is expressed as a 32-bit word and the bit
  *         resolution is 25 μs.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that stores data read
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_timestamp_raw_get(const stmdev_ctx_t *ctx, uint32_t *val)
{
  uint8_t buff[4];
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TIMESTAMP0, buff, 4);
  *val = buff[3];
  *val = (*val * 256U) +  buff[2];
  *val = (*val * 256U) +  buff[1];
  *val = (*val * 256U) +  buff[0];

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  LSM6DSO32_Data output
  * @brief     This section groups all the data output functions.
  * @{
  *
  */

/**
  * @brief  Circular burst-mode (rounding) read of the output
  *         registers.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of rounding in reg CTRL5_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_rounding_mode_set(const stmdev_ctx_t *ctx,
                                    lsm6dso32_rounding_t val)
{
  lsm6dso32_ctrl5_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL5_C, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.rounding = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL5_C, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Gyroscope UI chain full-scale selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of rounding in reg CTRL5_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_rounding_mode_get(const stmdev_ctx_t *ctx,
                                    lsm6dso32_rounding_t *val)
{
  lsm6dso32_ctrl5_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL5_C, (uint8_t *)&reg, 1);

  switch (reg.rounding)
  {
    case LSM6DSO32_NO_ROUND:
      *val = LSM6DSO32_NO_ROUND;
      break;

    case LSM6DSO32_ROUND_XL:
      *val = LSM6DSO32_ROUND_XL;
      break;

    case LSM6DSO32_ROUND_GY:
      *val = LSM6DSO32_ROUND_GY;
      break;

    case LSM6DSO32_ROUND_GY_XL:
      *val = LSM6DSO32_ROUND_GY_XL;
      break;

    default:
      *val = LSM6DSO32_NO_ROUND;
      break;
  }

  return ret;
}

/**
  * @brief  Temperature data output register (r).
  *         L and H registers together express a 16-bit word in two's
  *         complement.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that stores data read
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_temperature_raw_get(const stmdev_ctx_t *ctx, int16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_OUT_TEMP_L, buff, 2);
  val[0] = (int16_t)buff[1];
  val[0] = (val[0] * 256) + (int16_t)buff[0];

  return ret;
}

/**
  * @brief  Angular rate sensor. The value is expressed as a 16-bit
  *         word in two's complement.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that stores data read
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_angular_rate_raw_get(const stmdev_ctx_t *ctx,
                                       int16_t *val)
{
  uint8_t buff[6];
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_OUTX_L_G, buff, 6);
  val[0] = (int16_t)buff[1];
  val[0] = (val[0] * 256) + (int16_t)buff[0];
  val[1] = (int16_t)buff[3];
  val[1] = (val[1] * 256) + (int16_t)buff[2];
  val[2] = (int16_t)buff[5];
  val[2] = (val[2] * 256) + (int16_t)buff[4];

  return ret;
}

/**
  * @brief  Linear acceleration output register.
  *         The value is expressed as a 16-bit word in two's complement.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that stores data read
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_acceleration_raw_get(const stmdev_ctx_t *ctx,
                                       int16_t *val)
{
  uint8_t buff[6];
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_OUTX_L_A, buff, 6);
  val[0] = (int16_t)buff[1];
  val[0] = (val[0] * 256) + (int16_t)buff[0];
  val[1] = (int16_t)buff[3];
  val[1] = (val[1] * 256) + (int16_t)buff[2];
  val[2] = (int16_t)buff[5];
  val[2] = (val[2] * 256) + (int16_t)buff[4];

  return ret;
}

/**
  * @brief  FIFO data output [get]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that stores data read
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fifo_out_raw_get(const stmdev_ctx_t *ctx, uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_DATA_OUT_X_L, buff, 6);

  return ret;
}

/**
  * @brief  Step counter output register.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that stores data read
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_number_of_steps_get(const stmdev_ctx_t *ctx,
                                      uint16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_STEP_COUNTER_L, buff, 2);
  }

  if (ret == 0)
  {
    *val = buff[1];
    *val = (*val * 256U) +  buff[0];
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Reset step counter register.[get]
  *
  * @param  ctx      read / write interface definitions
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_steps_reset(const stmdev_ctx_t *ctx)
{
  lsm6dso32_emb_func_src_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_SRC, (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    reg.pedo_rst_step = PROPERTY_ENABLE;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_EMB_FUNC_SRC,
                              (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  LSM6DSO32_common
  * @brief   This section groups common useful functions.
  * @{
  *
  */

/**
  * @brief  Difference in percentage of the effective ODR(and timestamp rate)
  *         with respect to the typical.
  *         Step:  0.15%. 8-bit format, 2's complement.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of freq_fine in reg
  *                  INTERNAL_FREQ_FINE
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_odr_cal_reg_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_internal_freq_fine_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_INTERNAL_FREQ_FINE,
                           (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.freq_fine = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_INTERNAL_FREQ_FINE,
                              (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Difference in percentage of the effective ODR(and timestamp rate)
  *         with respect to the typical.
  *         Step:  0.15%. 8-bit format, 2's complement.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of freq_fine in reg INTERNAL_FREQ_FINE
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_odr_cal_reg_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_internal_freq_fine_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_INTERNAL_FREQ_FINE,
                           (uint8_t *)&reg, 1);
  *val = reg.freq_fine;

  return ret;
}


/**
  * @brief  Enable access to the embedded functions/sensor
  *         hub configuration registers.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of reg_access in reg FUNC_CFG_ACCESS
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_mem_bank_set(const stmdev_ctx_t *ctx,
                               lsm6dso32_reg_access_t val)
{
  lsm6dso32_func_cfg_access_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FUNC_CFG_ACCESS,
                           (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.reg_access = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_FUNC_CFG_ACCESS,
                              (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Enable access to the embedded functions/sensor
  *         hub configuration registers.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of reg_access in reg FUNC_CFG_ACCESS
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_mem_bank_get(const stmdev_ctx_t *ctx,
                               lsm6dso32_reg_access_t *val)
{
  lsm6dso32_func_cfg_access_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FUNC_CFG_ACCESS,
                           (uint8_t *)&reg, 1);

  switch (reg.reg_access)
  {
    case LSM6DSO32_USER_BANK:
      *val = LSM6DSO32_USER_BANK;
      break;

    case LSM6DSO32_SENSOR_HUB_BANK:
      *val = LSM6DSO32_SENSOR_HUB_BANK;
      break;

    case LSM6DSO32_EMBEDDED_FUNC_BANK:
      *val = LSM6DSO32_EMBEDDED_FUNC_BANK;
      break;

    default:
      *val = LSM6DSO32_USER_BANK;
      break;
  }

  return ret;
}

/**
  * @brief  Write a line(byte) in a page.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  uint8_t address: page line address
  * @param  val      value to write
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_ln_pg_write_byte(const stmdev_ctx_t *ctx, uint16_t address, uint8_t *val)
{
  return lsm6dso32_ln_pg_write(ctx, address, val, 1);
}

/**
  * @brief  Write buffer in a page.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  uint8_t address: page line address
  * @param  uint8_t *buf: buffer to write
  * @param  uint8_t len: buffer len
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_ln_pg_write(const stmdev_ctx_t *ctx, uint16_t address,
                              uint8_t *buf, uint8_t len)
{
  lsm6dso32_page_rw_t page_rw;
  lsm6dso32_page_sel_t page_sel;
  lsm6dso32_page_address_t  page_address;
  uint8_t msb;
  uint8_t lsb;
  int32_t ret;
  uint8_t i ;

  msb = ((uint8_t)(address >> 8) & 0x0FU);
  lsb = (uint8_t)address & 0xFFU;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);
  if (ret != 0) { return ret; }

  /* set page write */
  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_PAGE_RW, (uint8_t *) &page_rw, 1);
  page_rw.page_rw = 0x02; /* page_write enable*/
  ret += lsm6dso32_write_reg(ctx, LSM6DSO32_PAGE_RW, (uint8_t *) &page_rw, 1);
  if (ret != 0) { goto exit; }

  /* select page */
  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_PAGE_SEL, (uint8_t *) &page_sel, 1);
  page_sel.page_sel = msb;
  page_sel.not_used_01 = 1;
  ret += lsm6dso32_write_reg(ctx, LSM6DSO32_PAGE_SEL, (uint8_t *) &page_sel, 1);
  if (ret != 0) { goto exit; }

  /* set page addr */
  page_address.page_addr = lsb;
  ret += lsm6dso32_write_reg(ctx, LSM6DSO32_PAGE_ADDRESS,
                           (uint8_t *)&page_address, 1);
  if (ret != 0) { goto exit; }

  for (i = 0; ((i < len) && (ret == 0)); i++)
  {
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_PAGE_VALUE, &buf[i], 1);
    if (ret != 0) { goto exit; }

    lsb++;

    /* Check if page wrap */
    if (((lsb & 0xFFU) == 0x00U) && (ret == 0))
    {
      msb++;
      ret += lsm6dso32_read_reg(ctx, LSM6DSO32_PAGE_SEL, (uint8_t *)&page_sel, 1);
      if (ret != 0) { goto exit; }

      page_sel.page_sel = msb;
      page_sel.not_used_01 = 1;
      ret = lsm6dso32_write_reg(ctx, LSM6DSO32_PAGE_SEL, (uint8_t *)&page_sel, 1);
      if (ret != 0) { goto exit; }
    }
  }

  page_sel.page_sel = 0;
  page_sel.not_used_01 = 1;
  ret = lsm6dso32_write_reg(ctx, LSM6DSO32_PAGE_SEL, (uint8_t *) &page_sel, 1);
  if (ret != 0) { goto exit; }

  /* unset page write */
  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_PAGE_RW, (uint8_t *) &page_rw, 1);
  page_rw.page_rw = 0x00; /* page_write disable */
  ret += lsm6dso32_write_reg(ctx, LSM6DSO32_PAGE_RW, (uint8_t *) &page_rw, 1);

exit:
  ret += lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);

  return ret;
}

/**
  * @brief  Read a line(byte) in a page.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  uint8_t address: page line address
  * @param  val      read value
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_ln_pg_read_byte(const stmdev_ctx_t *ctx, uint16_t address, uint8_t *val)
{
  return lsm6dso32_ln_pg_read(ctx, address, val, 1);
}

int32_t lsm6dso32_ln_pg_read(const stmdev_ctx_t *ctx, uint16_t address, uint8_t *buf,
                             uint8_t len)
{
  lsm6dso32_page_rw_t page_rw;
  lsm6dso32_page_sel_t page_sel;
  lsm6dso32_page_address_t  page_address;
  uint8_t msb;
  uint8_t lsb;
  int32_t ret;
  uint8_t i ;

  msb = ((uint8_t)(address >> 8) & 0x0FU);
  lsb = (uint8_t)address & 0xFFU;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);
  if (ret != 0) { return ret; }

  /* set page write */
  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_PAGE_RW, (uint8_t *) &page_rw, 1);
  page_rw.page_rw = 0x01; /* page_read enable*/
  ret += lsm6dso32_write_reg(ctx, LSM6DSO32_PAGE_RW, (uint8_t *) &page_rw, 1);
  if (ret != 0) { goto exit; }

  /* select page */
  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_PAGE_SEL, (uint8_t *) &page_sel, 1);
  page_sel.page_sel = msb;
  page_sel.not_used_01 = 1;
  ret += lsm6dso32_write_reg(ctx, LSM6DSO32_PAGE_SEL, (uint8_t *) &page_sel, 1);
  if (ret != 0) { goto exit; }

  for (i = 0; ((i < len) && (ret == 0)); i++)
  {
    /* set page addr */
    page_address.page_addr = lsb;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_PAGE_ADDRESS,
                            (uint8_t *)&page_address, 1);
    if (ret != 0) { goto exit; }

    ret += lsm6dso32_read_reg(ctx, LSM6DSO32_PAGE_VALUE, &buf[i], 1);
    if (ret != 0) { goto exit; }

    lsb++;

    /* Check if page wrap */
    if (((lsb & 0xFFU) == 0x00U) && (ret == 0))
    {
      msb++;
      ret += lsm6dso32_read_reg(ctx, LSM6DSO32_PAGE_SEL, (uint8_t *)&page_sel, 1);
      if (ret != 0) { goto exit; }

      page_sel.page_sel = msb;
      page_sel.not_used_01 = 1;
      ret += lsm6dso32_write_reg(ctx, LSM6DSO32_PAGE_SEL, (uint8_t *)&page_sel, 1);
      if (ret != 0) { goto exit; }
    }
  }

  page_sel.page_sel = 0;
  page_sel.not_used_01 = 1;
  ret = lsm6dso32_write_reg(ctx, LSM6DSO32_PAGE_SEL, (uint8_t *) &page_sel, 1);
  if (ret != 0) { goto exit; }

  /* unset page write */
  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_PAGE_RW, (uint8_t *) &page_rw, 1);
  page_rw.page_rw = 0x00; /* page_write disable */
  ret += lsm6dso32_write_reg(ctx, LSM6DSO32_PAGE_RW, (uint8_t *) &page_rw, 1);

exit:
  ret += lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);

  return ret;
}

/**
  * @brief  Data-ready pulsed / letched mode.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of dataready_pulsed in
  *                  reg COUNTER_BDR_REG1
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_data_ready_mode_set(const stmdev_ctx_t *ctx,
                                      lsm6dso32_dataready_pulsed_t val)
{
  lsm6dso32_counter_bdr_reg1_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_COUNTER_BDR_REG1,
                           (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.dataready_pulsed = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_COUNTER_BDR_REG1,
                              (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Data-ready pulsed / letched mode.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of
  *                                     dataready_pulsed in
  *                                     reg COUNTER_BDR_REG1
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_data_ready_mode_get(const stmdev_ctx_t *ctx,
                                      lsm6dso32_dataready_pulsed_t *val)
{
  lsm6dso32_counter_bdr_reg1_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_COUNTER_BDR_REG1,
                           (uint8_t *)&reg, 1);

  switch (reg.dataready_pulsed)
  {
    case LSM6DSO32_DRDY_LATCHED:
      *val = LSM6DSO32_DRDY_LATCHED;
      break;

    case LSM6DSO32_DRDY_PULSED:
      *val = LSM6DSO32_DRDY_PULSED;
      break;

    default:
      *val = LSM6DSO32_DRDY_LATCHED;
      break;
  }

  return ret;
}

/**
  * @brief  Device "Who am I".[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that stores data read
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_device_id_get(const stmdev_ctx_t *ctx, uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_WHO_AM_I, buff, 1);

  return ret;
}

/**
  * @brief  Software reset. Restore the default values
  *         in user registers[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of sw_reset in reg CTRL3_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_reset_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_ctrl3_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL3_C, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.sw_reset = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL3_C, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Software reset. Restore the default values in user registers.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of sw_reset in reg CTRL3_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_reset_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_ctrl3_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL3_C, (uint8_t *)&reg, 1);
  *val = reg.sw_reset;

  return ret;
}

/**
  * @brief  Register address automatically incremented during a multiple byte
  *         access with a serial interface.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of if_inc in reg CTRL3_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_auto_increment_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_ctrl3_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL3_C, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.if_inc = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL3_C, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Register address automatically incremented during a multiple byte
  *         access with a serial interface.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of if_inc in reg CTRL3_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_auto_increment_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_ctrl3_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL3_C, (uint8_t *)&reg, 1);
  *val = reg.if_inc;

  return ret;
}

/**
  * @brief  Reboot memory content. Reload the calibration parameters.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of boot in reg CTRL3_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_boot_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_ctrl3_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL3_C, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.boot = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL3_C, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Reboot memory content. Reload the calibration parameters.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of boot in reg CTRL3_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_boot_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_ctrl3_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL3_C, (uint8_t *)&reg, 1);
  *val = reg.boot;

  return ret;
}

/**
  * @brief  Linear acceleration sensor self-test enable.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of st_xl in reg CTRL5_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_self_test_set(const stmdev_ctx_t *ctx,
                                   lsm6dso32_st_xl_t val)
{
  lsm6dso32_ctrl5_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL5_C, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.st_xl = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL5_C, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Linear acceleration sensor self-test enable.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of st_xl in reg CTRL5_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_self_test_get(const stmdev_ctx_t *ctx,
                                   lsm6dso32_st_xl_t *val)
{
  lsm6dso32_ctrl5_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL5_C, (uint8_t *)&reg, 1);

  switch (reg.st_xl)
  {
    case LSM6DSO32_XL_ST_DISABLE:
      *val = LSM6DSO32_XL_ST_DISABLE;
      break;

    case LSM6DSO32_XL_ST_POSITIVE:
      *val = LSM6DSO32_XL_ST_POSITIVE;
      break;

    case LSM6DSO32_XL_ST_NEGATIVE:
      *val = LSM6DSO32_XL_ST_NEGATIVE;
      break;

    default:
      *val = LSM6DSO32_XL_ST_DISABLE;
      break;
  }

  return ret;
}

/**
  * @brief  Angular rate sensor self-test enable.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of st_g in reg CTRL5_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_gy_self_test_set(const stmdev_ctx_t *ctx,
                                   lsm6dso32_st_g_t val)
{
  lsm6dso32_ctrl5_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL5_C, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.st_g = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL5_C, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Angular rate sensor self-test enable.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of st_g in reg CTRL5_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_gy_self_test_get(const stmdev_ctx_t *ctx,
                                   lsm6dso32_st_g_t *val)
{
  lsm6dso32_ctrl5_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL5_C, (uint8_t *)&reg, 1);

  switch (reg.st_g)
  {
    case LSM6DSO32_GY_ST_DISABLE:
      *val = LSM6DSO32_GY_ST_DISABLE;
      break;

    case LSM6DSO32_GY_ST_POSITIVE:
      *val = LSM6DSO32_GY_ST_POSITIVE;
      break;

    case LSM6DSO32_GY_ST_NEGATIVE:
      *val = LSM6DSO32_GY_ST_NEGATIVE;
      break;

    default:
      *val = LSM6DSO32_GY_ST_DISABLE;
      break;
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  LSM6DSO32_filters
  * @brief     This section group all the functions concerning the
  *            filters configuration
  * @{
  *
  */

/**
  * @brief  Accelerometer output from LPF2 filtering stage selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of lpf2_xl_en in reg CTRL1_XL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_filter_lp2_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_ctrl1_xl_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL1_XL, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.lpf2_xl_en = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL1_XL, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Accelerometer output from LPF2 filtering stage selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of lpf2_xl_en in reg CTRL1_XL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_filter_lp2_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_ctrl1_xl_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL1_XL, (uint8_t *)&reg, 1);
  *val = reg.lpf2_xl_en;

  return ret;
}

/**
  * @brief  Enables gyroscope digital LPF1 if auxiliary SPI is disabled;
  *         the bandwidth can be selected through FTYPE [2:0]
  *         in CTRL6_C (15h).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of lpf1_sel_g in reg CTRL4_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_gy_filter_lp1_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_ctrl4_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL4_C, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.lpf1_sel_g = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL4_C, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Enables gyroscope digital LPF1 if auxiliary SPI is disabled;
  *         the bandwidth can be selected through FTYPE [2:0]
  *         in CTRL6_C (15h).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of lpf1_sel_g in reg CTRL4_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_gy_filter_lp1_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_ctrl4_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL4_C, (uint8_t *)&reg, 1);
  *val = reg.lpf1_sel_g;

  return ret;
}

/**
  * @brief  Mask DRDY on pin (both XL & Gyro) until filter settling ends
  *         (XL and Gyro independently masked).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of drdy_mask in reg CTRL4_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_filter_settling_mask_set(const stmdev_ctx_t *ctx,
                                           uint8_t val)
{
  lsm6dso32_ctrl4_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL4_C, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.drdy_mask = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL4_C, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Mask DRDY on pin (both XL & Gyro) until filter settling ends
  *         (XL and Gyro independently masked).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of drdy_mask in reg CTRL4_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_filter_settling_mask_get(const stmdev_ctx_t *ctx,
                                           uint8_t *val)
{
  lsm6dso32_ctrl4_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL4_C, (uint8_t *)&reg, 1);
  *val = reg.drdy_mask;

  return ret;
}

/**
  * @brief  Gyroscope lp1 bandwidth.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of ftype in reg CTRL6_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_gy_lp1_bandwidth_set(const stmdev_ctx_t *ctx,
                                       lsm6dso32_ftype_t val)
{
  lsm6dso32_ctrl6_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL6_C, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.ftype = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL6_C, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Gyroscope lp1 bandwidth.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val       Get the values of ftype in reg CTRL6_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_gy_lp1_bandwidth_get(const stmdev_ctx_t *ctx,
                                       lsm6dso32_ftype_t *val)
{
  lsm6dso32_ctrl6_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL6_C, (uint8_t *)&reg, 1);

  switch (reg.ftype)
  {
    case LSM6DSO32_ULTRA_LIGHT:
      *val = LSM6DSO32_ULTRA_LIGHT;
      break;

    case LSM6DSO32_VERY_LIGHT:
      *val = LSM6DSO32_VERY_LIGHT;
      break;

    case LSM6DSO32_LIGHT:
      *val = LSM6DSO32_LIGHT;
      break;

    case LSM6DSO32_MEDIUM:
      *val = LSM6DSO32_MEDIUM;
      break;

    case LSM6DSO32_STRONG:
      *val = LSM6DSO32_STRONG;
      break;

    case LSM6DSO32_VERY_STRONG:
      *val = LSM6DSO32_VERY_STRONG;
      break;

    case LSM6DSO32_AGGRESSIVE:
      *val = LSM6DSO32_AGGRESSIVE;
      break;

    case LSM6DSO32_XTREME:
      *val = LSM6DSO32_XTREME;
      break;

    default:
      *val = LSM6DSO32_ULTRA_LIGHT;
      break;
  }

  return ret;
}

/**
  * @brief  Low pass filter 2 on 6D function selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of low_pass_on_6d in reg CTRL8_XL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_lp2_on_6d_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_ctrl8_xl_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL8_XL, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.low_pass_on_6d = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL8_XL, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Low pass filter 2 on 6D function selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of low_pass_on_6d in reg CTRL8_XL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_lp2_on_6d_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_ctrl8_xl_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL8_XL, (uint8_t *)&reg, 1);
  *val = reg.low_pass_on_6d;

  return ret;
}

/**
  * @brief  Accelerometer slope filter / high-pass filter selection
  *         on output.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of hp_slope_xl_en
  *                                   in reg CTRL8_XL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_hp_path_on_out_set(const stmdev_ctx_t *ctx,
                                        lsm6dso32_hp_slope_xl_en_t val)
{
  lsm6dso32_ctrl8_xl_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL8_XL, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.hp_slope_xl_en = ((uint8_t)val & 0x10U) >> 4;
    reg.hp_ref_mode_xl = ((uint8_t)val & 0x20U) >> 5;
    reg.hpcf_xl = (uint8_t)val & 0x07U;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL8_XL, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Accelerometer slope filter / high-pass filter selection
  *         on output.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of hp_slope_xl_en in reg CTRL8_XL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_hp_path_on_out_get(const stmdev_ctx_t *ctx,
                                        lsm6dso32_hp_slope_xl_en_t *val)
{
  lsm6dso32_ctrl8_xl_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL8_XL, (uint8_t *)&reg, 1);

  switch ((reg.hp_ref_mode_xl << 5) | (reg.hp_slope_xl_en << 4) |
          reg.hpcf_xl)
  {
    case LSM6DSO32_HP_PATH_DISABLE_ON_OUT:
      *val = LSM6DSO32_HP_PATH_DISABLE_ON_OUT;
      break;

    case LSM6DSO32_SLOPE_ODR_DIV_4:
      *val = LSM6DSO32_SLOPE_ODR_DIV_4;
      break;

    case LSM6DSO32_HP_ODR_DIV_10:
      *val = LSM6DSO32_HP_ODR_DIV_10;
      break;

    case LSM6DSO32_HP_ODR_DIV_20:
      *val = LSM6DSO32_HP_ODR_DIV_20;
      break;

    case LSM6DSO32_HP_ODR_DIV_45:
      *val = LSM6DSO32_HP_ODR_DIV_45;
      break;

    case LSM6DSO32_HP_ODR_DIV_100:
      *val = LSM6DSO32_HP_ODR_DIV_100;
      break;

    case LSM6DSO32_HP_ODR_DIV_200:
      *val = LSM6DSO32_HP_ODR_DIV_200;
      break;

    case LSM6DSO32_HP_ODR_DIV_400:
      *val = LSM6DSO32_HP_ODR_DIV_400;
      break;

    case LSM6DSO32_HP_ODR_DIV_800:
      *val = LSM6DSO32_HP_ODR_DIV_800;
      break;

    case LSM6DSO32_HP_REF_MD_ODR_DIV_10:
      *val = LSM6DSO32_HP_REF_MD_ODR_DIV_10;
      break;

    case LSM6DSO32_HP_REF_MD_ODR_DIV_20:
      *val = LSM6DSO32_HP_REF_MD_ODR_DIV_20;
      break;

    case LSM6DSO32_HP_REF_MD_ODR_DIV_45:
      *val = LSM6DSO32_HP_REF_MD_ODR_DIV_45;
      break;

    case LSM6DSO32_HP_REF_MD_ODR_DIV_100:
      *val = LSM6DSO32_HP_REF_MD_ODR_DIV_100;
      break;

    case LSM6DSO32_HP_REF_MD_ODR_DIV_200:
      *val = LSM6DSO32_HP_REF_MD_ODR_DIV_200;
      break;

    case LSM6DSO32_HP_REF_MD_ODR_DIV_400:
      *val = LSM6DSO32_HP_REF_MD_ODR_DIV_400;
      break;

    case LSM6DSO32_HP_REF_MD_ODR_DIV_800:
      *val = LSM6DSO32_HP_REF_MD_ODR_DIV_800;
      break;

    case LSM6DSO32_LP_ODR_DIV_10:
      *val = LSM6DSO32_LP_ODR_DIV_10;
      break;

    case LSM6DSO32_LP_ODR_DIV_20:
      *val = LSM6DSO32_LP_ODR_DIV_20;
      break;

    case LSM6DSO32_LP_ODR_DIV_45:
      *val = LSM6DSO32_LP_ODR_DIV_45;
      break;

    case LSM6DSO32_LP_ODR_DIV_100:
      *val = LSM6DSO32_LP_ODR_DIV_100;
      break;

    case LSM6DSO32_LP_ODR_DIV_200:
      *val = LSM6DSO32_LP_ODR_DIV_200;
      break;

    case LSM6DSO32_LP_ODR_DIV_400:
      *val = LSM6DSO32_LP_ODR_DIV_400;
      break;

    case LSM6DSO32_LP_ODR_DIV_800:
      *val = LSM6DSO32_LP_ODR_DIV_800;
      break;

    default:
      *val = LSM6DSO32_HP_PATH_DISABLE_ON_OUT;
      break;
  }

  return ret;
}

/**
  * @brief  Enables accelerometer LPF2 and HPF fast-settling mode.
  *         The filter sets the second samples after writing this bit.
  *         Active only during device exit from power-down mode.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of fastsettl_mode_xl in
  *                  reg CTRL8_XL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_fast_settling_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_ctrl8_xl_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL8_XL, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.fastsettl_mode_xl = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL8_XL, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Enables accelerometer LPF2 and HPF fast-settling mode.
  *         The filter sets the second samples after writing this bit.
  *         Active only during device exit from power-down mode.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of fastsettl_mode_xl in reg CTRL8_XL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_fast_settling_get(const stmdev_ctx_t *ctx,
                                       uint8_t *val)
{
  lsm6dso32_ctrl8_xl_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL8_XL, (uint8_t *)&reg, 1);
  *val = reg.fastsettl_mode_xl;

  return ret;
}

/**
  * @brief  HPF or SLOPE filter selection on wake-up and Activity/Inactivity
  *         functions.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of slope_fds in reg TAP_CFG0
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_hp_path_internal_set(const stmdev_ctx_t *ctx,
                                          lsm6dso32_slope_fds_t val)
{
  lsm6dso32_tap_cfg0_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_CFG0, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.slope_fds = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_TAP_CFG0, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  HPF or SLOPE filter selection on wake-up and Activity/Inactivity
  *         functions.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of slope_fds in reg TAP_CFG0
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_hp_path_internal_get(const stmdev_ctx_t *ctx,
                                          lsm6dso32_slope_fds_t *val)
{
  lsm6dso32_tap_cfg0_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_CFG0, (uint8_t *)&reg, 1);

  switch (reg.slope_fds)
  {
    case LSM6DSO32_USE_SLOPE:
      *val = LSM6DSO32_USE_SLOPE;
      break;

    case LSM6DSO32_USE_HPF:
      *val = LSM6DSO32_USE_HPF;
      break;

    default:
      *val = LSM6DSO32_USE_SLOPE;
      break;
  }

  return ret;
}

/**
  * @brief  Enables gyroscope digital high-pass filter. The filter is
  *         enabled only if the gyro is in HP mode.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of hp_en_g and hp_en_g in reg CTRL7_G
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_gy_hp_path_internal_set(const stmdev_ctx_t *ctx,
                                          lsm6dso32_hpm_g_t val)
{
  lsm6dso32_ctrl7_g_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL7_G, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.hp_en_g = ((uint8_t)val & 0x80U) >> 7;
    reg.hpm_g = (uint8_t)val & 0x03U;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL7_G, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Enables gyroscope digital high-pass filter. The filter is
  *         enabled only if the gyro is in HP mode.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of hp_en_g and hp_en_g in reg CTRL7_G
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_gy_hp_path_internal_get(const stmdev_ctx_t *ctx,
                                          lsm6dso32_hpm_g_t *val)
{
  lsm6dso32_ctrl7_g_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL7_G, (uint8_t *)&reg, 1);

  switch ((reg.hp_en_g << 7) + reg.hpm_g)
  {
    case LSM6DSO32_HP_FILTER_NONE:
      *val = LSM6DSO32_HP_FILTER_NONE;
      break;

    case LSM6DSO32_HP_FILTER_16mHz:
      *val = LSM6DSO32_HP_FILTER_16mHz;
      break;

    case LSM6DSO32_HP_FILTER_65mHz:
      *val = LSM6DSO32_HP_FILTER_65mHz;
      break;

    case LSM6DSO32_HP_FILTER_260mHz:
      *val = LSM6DSO32_HP_FILTER_260mHz;
      break;

    case LSM6DSO32_HP_FILTER_1Hz04:
      *val = LSM6DSO32_HP_FILTER_1Hz04;
      break;

    default:
      *val = LSM6DSO32_HP_FILTER_NONE;
      break;
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  LSM6DSO32 main_serial_interface
  * @brief     This section groups all the functions concerning main
  *            serial interface management (not auxiliary)
  * @{
  *
  */

/**
  * @brief  Connect/Disconnect SDO/SA0 internal pull-up.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of sdo_pu_en in
  *                              reg PIN_CTRL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sdo_sa0_mode_set(const stmdev_ctx_t *ctx,
                                   lsm6dso32_sdo_pu_en_t val)
{
  lsm6dso32_pin_ctrl_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_PIN_CTRL, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.sdo_pu_en = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_PIN_CTRL, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Connect/Disconnect SDO/SA0 internal pull-up.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of sdo_pu_en in reg PIN_CTRL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sdo_sa0_mode_get(const stmdev_ctx_t *ctx,
                                   lsm6dso32_sdo_pu_en_t *val)
{
  lsm6dso32_pin_ctrl_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_PIN_CTRL, (uint8_t *)&reg, 1);

  switch (reg.sdo_pu_en)
  {
    case LSM6DSO32_PULL_UP_DISC:
      *val = LSM6DSO32_PULL_UP_DISC;
      break;

    case LSM6DSO32_PULL_UP_CONNECT:
      *val = LSM6DSO32_PULL_UP_CONNECT;
      break;

    default:
      *val = LSM6DSO32_PULL_UP_DISC;
      break;
  }

  return ret;
}

/**
  * @brief  SPI Serial Interface Mode selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of sim in reg CTRL3_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_spi_mode_set(const stmdev_ctx_t *ctx, lsm6dso32_sim_t val)
{
  lsm6dso32_ctrl3_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL3_C, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.sim = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL3_C, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  SPI Serial Interface Mode selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of sim in reg CTRL3_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_spi_mode_get(const stmdev_ctx_t *ctx,
                               lsm6dso32_sim_t *val)
{
  lsm6dso32_ctrl3_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL3_C, (uint8_t *)&reg, 1);

  switch (reg.sim)
  {
    case LSM6DSO32_SPI_4_WIRE:
      *val = LSM6DSO32_SPI_4_WIRE;
      break;

    case LSM6DSO32_SPI_3_WIRE:
      *val = LSM6DSO32_SPI_3_WIRE;
      break;

    default:
      *val = LSM6DSO32_SPI_4_WIRE;
      break;
  }

  return ret;
}

/**
  * @brief  Disable / Enable I2C interface.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of i2c_disable in
  *                                reg CTRL4_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_i2c_interface_set(const stmdev_ctx_t *ctx,
                                    lsm6dso32_i2c_disable_t val)
{
  lsm6dso32_ctrl4_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL4_C, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.i2c_disable = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL4_C, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Disable / Enable I2C interface.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of i2c_disable in
  *                                reg CTRL4_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_i2c_interface_get(const stmdev_ctx_t *ctx,
                                    lsm6dso32_i2c_disable_t *val)
{
  lsm6dso32_ctrl4_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL4_C, (uint8_t *)&reg, 1);

  switch (reg.i2c_disable)
  {
    case LSM6DSO32_I2C_ENABLE:
      *val = LSM6DSO32_I2C_ENABLE;
      break;

    case LSM6DSO32_I2C_DISABLE:
      *val = LSM6DSO32_I2C_DISABLE;
      break;

    default:
      *val = LSM6DSO32_I2C_ENABLE;
      break;
  }

  return ret;
}

/**
  * @brief  I3C Enable/Disable communication protocol[.set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of i3c_disable in reg CTRL9_XL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_i3c_disable_set(const stmdev_ctx_t *ctx,
                                  lsm6dso32_i3c_disable_t val)
{
  lsm6dso32_i3c_bus_avb_t i3c_bus_avb;
  lsm6dso32_ctrl9_xl_t ctrl9_xl;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL9_XL,
                           (uint8_t *)&ctrl9_xl, 1);

  if (ret == 0)
  {
    ctrl9_xl.i3c_disable = ((uint8_t)val & 0x80U) >> 7;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL9_XL,
                              (uint8_t *)&ctrl9_xl, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_I3C_BUS_AVB,
                             (uint8_t *)&i3c_bus_avb, 1);
  }

  if (ret == 0)
  {
    i3c_bus_avb.i3c_bus_avb_sel = (uint8_t)val & 0x03U;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_I3C_BUS_AVB,
                              (uint8_t *)&i3c_bus_avb, 1);
  }

  return ret;
}

/**
  * @brief  I3C Enable/Disable communication protocol.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of i3c_disable in reg CTRL9_XL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_i3c_disable_get(const stmdev_ctx_t *ctx,
                                  lsm6dso32_i3c_disable_t *val)
{
  lsm6dso32_ctrl9_xl_t ctrl9_xl;
  lsm6dso32_i3c_bus_avb_t i3c_bus_avb;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL9_XL,
                           (uint8_t *)&ctrl9_xl, 1);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_I3C_BUS_AVB,
                             (uint8_t *)&i3c_bus_avb, 1);

    switch ((ctrl9_xl.i3c_disable << 7) | i3c_bus_avb.i3c_bus_avb_sel)
    {
      case LSM6DSO32_I3C_DISABLE:
        *val = LSM6DSO32_I3C_DISABLE;
        break;

      case LSM6DSO32_I3C_ENABLE_T_50us:
        *val = LSM6DSO32_I3C_ENABLE_T_50us;
        break;

      case LSM6DSO32_I3C_ENABLE_T_2us:
        *val = LSM6DSO32_I3C_ENABLE_T_2us;
        break;

      case LSM6DSO32_I3C_ENABLE_T_1ms:
        *val = LSM6DSO32_I3C_ENABLE_T_1ms;
        break;

      case LSM6DSO32_I3C_ENABLE_T_25ms:
        *val = LSM6DSO32_I3C_ENABLE_T_25ms;
        break;

      default:
        *val = LSM6DSO32_I3C_DISABLE;
        break;
    }
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  LSM6DSO32_interrupt_pins
  * @brief     This section groups all the functions that manage interrupt pins
  * @{
  *
  */

/**
  * @brief  Connect/Disconnect INT1 internal pull-down.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of pd_dis_int1 in reg I3C_BUS_AVB
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_int1_mode_set(const stmdev_ctx_t *ctx,
                                lsm6dso32_int1_pd_en_t val)
{
  lsm6dso32_i3c_bus_avb_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_I3C_BUS_AVB, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.pd_dis_int1 = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_I3C_BUS_AVB, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Connect/Disconnect INT1 internal pull-down.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of pd_dis_int1 in reg I3C_BUS_AVB
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_int1_mode_get(const stmdev_ctx_t *ctx,
                                lsm6dso32_int1_pd_en_t *val)
{
  lsm6dso32_i3c_bus_avb_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_I3C_BUS_AVB, (uint8_t *)&reg, 1);

  switch (reg.pd_dis_int1)
  {
    case LSM6DSO32_PULL_DOWN_DISC:
      *val = LSM6DSO32_PULL_DOWN_DISC;
      break;

    case LSM6DSO32_PULL_DOWN_CONNECT:
      *val = LSM6DSO32_PULL_DOWN_CONNECT;
      break;

    default:
      *val = LSM6DSO32_PULL_DOWN_DISC;
      break;
  }

  return ret;
}

/**
  * @brief  Select the signal that need to route on int1 pad.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      struct of registers: INT1_CTRL,
  *                  MD1_CFG, EMB_FUNC_INT1, FSM_INT1_A,
  *                  FSM_INT1_B
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_pin_int1_route_set(const stmdev_ctx_t *ctx,
                                     lsm6dso32_pin_int1_route_t *val)
{
  lsm6dso32_pin_int2_route_t pin_int2_route;
  lsm6dso32_tap_cfg2_t tap_cfg2;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_EMB_FUNC_INT1,
                              (uint8_t *)&val->emb_func_int1, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_FSM_INT1_A,
                              (uint8_t *)&val->fsm_int1_a, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_FSM_INT1_B,
                              (uint8_t *)&val->fsm_int1_b, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  if (ret == 0)
  {
    if ((val->emb_func_int1.int1_fsm_lc
         | val->emb_func_int1.int1_sig_mot
         | val->emb_func_int1.int1_step_detector
         | val->emb_func_int1.int1_tilt
         | val->fsm_int1_a.int1_fsm1
         | val->fsm_int1_a.int1_fsm2
         | val->fsm_int1_a.int1_fsm3
         | val->fsm_int1_a.int1_fsm4
         | val->fsm_int1_a.int1_fsm5
         | val->fsm_int1_a.int1_fsm6
         | val->fsm_int1_a.int1_fsm7
         | val->fsm_int1_a.int1_fsm8
         | val->fsm_int1_b.int1_fsm9
         | val->fsm_int1_b.int1_fsm10
         | val->fsm_int1_b.int1_fsm11
         | val->fsm_int1_b.int1_fsm12
         | val->fsm_int1_b.int1_fsm13
         | val->fsm_int1_b.int1_fsm14
         | val->fsm_int1_b.int1_fsm15
         | val->fsm_int1_b.int1_fsm16) != PROPERTY_DISABLE)
    {
      val->md1_cfg.int1_emb_func = PROPERTY_ENABLE;
    }

    else
    {
      val->md1_cfg.int1_emb_func = PROPERTY_DISABLE;
    }

    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_INT1_CTRL,
                              (uint8_t *)&val->int1_ctrl, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_MD1_CFG,
                              (uint8_t *)&val->md1_cfg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_CFG2,
                             (uint8_t *) &tap_cfg2, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_pin_int2_route_get(ctx, &pin_int2_route);
  }

  if (ret == 0)
  {
    if ((pin_int2_route.int2_ctrl.int2_cnt_bdr
         | pin_int2_route.int2_ctrl.int2_drdy_g
         | pin_int2_route.int2_ctrl.int2_drdy_temp
         | pin_int2_route.int2_ctrl.int2_drdy_xl
         | pin_int2_route.int2_ctrl.int2_fifo_full
         | pin_int2_route.int2_ctrl.int2_fifo_ovr
         | pin_int2_route.int2_ctrl.int2_fifo_th
         | pin_int2_route.md2_cfg.int2_6d
         | pin_int2_route.md2_cfg.int2_double_tap
         | pin_int2_route.md2_cfg.int2_ff
         | pin_int2_route.md2_cfg.int2_wu
         | pin_int2_route.md2_cfg.int2_single_tap
         | pin_int2_route.md2_cfg.int2_sleep_change
         | val->int1_ctrl.den_drdy_flag
         | val->int1_ctrl.int1_boot
         | val->int1_ctrl.int1_cnt_bdr
         | val->int1_ctrl.int1_drdy_g
         | val->int1_ctrl.int1_drdy_xl
         | val->int1_ctrl.int1_fifo_full
         | val->int1_ctrl.int1_fifo_ovr
         | val->int1_ctrl.int1_fifo_th
         | val->md1_cfg.int1_6d
         | val->md1_cfg.int1_double_tap
         | val->md1_cfg.int1_ff
         | val->md1_cfg.int1_wu
         | val->md1_cfg.int1_single_tap
         | val->md1_cfg.int1_sleep_change) != PROPERTY_DISABLE)
    {
      tap_cfg2.interrupts_enable = PROPERTY_ENABLE;
    }

    else
    {
      tap_cfg2.interrupts_enable = PROPERTY_DISABLE;
    }

    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_TAP_CFG2,
                              (uint8_t *) &tap_cfg2, 1);
  }

  return ret;
}

/**
  * @brief  Select the signal that need to route on int1 pad.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      struct of registers: INT1_CTRL, MD1_CFG,
  *                  EMB_FUNC_INT1, FSM_INT1_A, FSM_INT1_B
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_pin_int1_route_get(const stmdev_ctx_t *ctx,
                                     lsm6dso32_pin_int1_route_t *val)
{
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_INT1,
                             (uint8_t *)&val->emb_func_int1, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FSM_INT1_A,
                             (uint8_t *)&val->fsm_int1_a, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FSM_INT1_B,
                             (uint8_t *)&val->fsm_int1_b, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_INT1_CTRL,
                             (uint8_t *)&val->int1_ctrl, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_MD1_CFG,
                             (uint8_t *)&val->md1_cfg, 1);
  }

  return ret;
}

/**
  * @brief  Select the signal that need to route on int2 pad.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      union of registers INT2_CTRL,  MD2_CFG,
  *                  EMB_FUNC_INT2, FSM_INT2_A, FSM_INT2_B
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_pin_int2_route_set(const stmdev_ctx_t *ctx,
                                     lsm6dso32_pin_int2_route_t *val)
{
  lsm6dso32_pin_int1_route_t pin_int1_route;
  lsm6dso32_tap_cfg2_t tap_cfg2;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_EMB_FUNC_INT2,
                              (uint8_t *)&val->emb_func_int2, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_FSM_INT2_A,
                              (uint8_t *)&val->fsm_int2_a, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_FSM_INT2_B,
                              (uint8_t *)&val->fsm_int2_b, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  if (ret == 0)
  {
    if ((val->emb_func_int2.int2_fsm_lc
         | val->emb_func_int2.int2_sig_mot
         | val->emb_func_int2.int2_step_detector
         | val->emb_func_int2.int2_tilt
         | val->fsm_int2_a.int2_fsm1
         | val->fsm_int2_a.int2_fsm2
         | val->fsm_int2_a.int2_fsm3
         | val->fsm_int2_a.int2_fsm4
         | val->fsm_int2_a.int2_fsm5
         | val->fsm_int2_a.int2_fsm6
         | val->fsm_int2_a.int2_fsm7
         | val->fsm_int2_a.int2_fsm8
         | val->fsm_int2_b.int2_fsm9
         | val->fsm_int2_b.int2_fsm10
         | val->fsm_int2_b.int2_fsm11
         | val->fsm_int2_b.int2_fsm12
         | val->fsm_int2_b.int2_fsm13
         | val->fsm_int2_b.int2_fsm14
         | val->fsm_int2_b.int2_fsm15
         | val->fsm_int2_b.int2_fsm16) != PROPERTY_DISABLE)
    {
      val->md2_cfg.int2_emb_func = PROPERTY_ENABLE;
    }

    else
    {
      val->md2_cfg.int2_emb_func = PROPERTY_DISABLE;
    }

    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_INT2_CTRL,
                              (uint8_t *)&val->int2_ctrl, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_MD2_CFG,
                              (uint8_t *)&val->md2_cfg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_CFG2,
                             (uint8_t *) &tap_cfg2, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_pin_int1_route_get(ctx, &pin_int1_route);
  }

  if (ret == 0)
  {
    if ((val->int2_ctrl.int2_cnt_bdr
         | val->int2_ctrl.int2_drdy_g
         | val->int2_ctrl.int2_drdy_temp
         | val->int2_ctrl.int2_drdy_xl
         | val->int2_ctrl.int2_fifo_full
         | val->int2_ctrl.int2_fifo_ovr
         | val->int2_ctrl.int2_fifo_th
         | val->md2_cfg.int2_6d
         | val->md2_cfg.int2_double_tap
         | val->md2_cfg.int2_ff
         | val->md2_cfg.int2_wu
         | val->md2_cfg.int2_single_tap
         | val->md2_cfg.int2_sleep_change
         | pin_int1_route.int1_ctrl.den_drdy_flag
         | pin_int1_route.int1_ctrl.int1_boot
         | pin_int1_route.int1_ctrl.int1_cnt_bdr
         | pin_int1_route.int1_ctrl.int1_drdy_g
         | pin_int1_route.int1_ctrl.int1_drdy_xl
         | pin_int1_route.int1_ctrl.int1_fifo_full
         | pin_int1_route.int1_ctrl.int1_fifo_ovr
         | pin_int1_route.int1_ctrl.int1_fifo_th
         | pin_int1_route.md1_cfg.int1_6d
         | pin_int1_route.md1_cfg.int1_double_tap
         | pin_int1_route.md1_cfg.int1_ff
         | pin_int1_route.md1_cfg.int1_wu
         | pin_int1_route.md1_cfg.int1_single_tap
         | pin_int1_route.md1_cfg.int1_sleep_change) != PROPERTY_DISABLE)
    {
      tap_cfg2.interrupts_enable = PROPERTY_ENABLE;
    }

    else
    {
      tap_cfg2.interrupts_enable = PROPERTY_DISABLE;
    }

    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_TAP_CFG2,
                              (uint8_t *) &tap_cfg2, 1);
  }

  return ret;
}

/**
  * @brief  Select the signal that need to route on int2 pad.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      union of registers INT2_CTRL,  MD2_CFG,
  *                  EMB_FUNC_INT2, FSM_INT2_A, FSM_INT2_B
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_pin_int2_route_get(const stmdev_ctx_t *ctx,
                                     lsm6dso32_pin_int2_route_t *val)
{
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_INT2,
                             (uint8_t *)&val->emb_func_int2, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FSM_INT2_A,
                             (uint8_t *)&val->fsm_int2_a, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FSM_INT2_B,
                             (uint8_t *)&val->fsm_int2_b, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_INT2_CTRL,
                             (uint8_t *)&val->int2_ctrl, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_MD2_CFG,
                             (uint8_t *)&val->md2_cfg, 1);
  }

  return ret;
}

/**
  * @brief  Push-pull/open drain selection on interrupt pads.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of pp_od in reg CTRL3_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_pin_mode_set(const stmdev_ctx_t *ctx,
                               lsm6dso32_pp_od_t val)
{
  lsm6dso32_ctrl3_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL3_C, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.pp_od = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL3_C, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Push-pull/open drain selection on interrupt pads.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of pp_od in reg CTRL3_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_pin_mode_get(const stmdev_ctx_t *ctx,
                               lsm6dso32_pp_od_t *val)
{
  lsm6dso32_ctrl3_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL3_C, (uint8_t *)&reg, 1);

  switch (reg.pp_od)
  {
    case LSM6DSO32_PUSH_PULL:
      *val = LSM6DSO32_PUSH_PULL;
      break;

    case LSM6DSO32_OPEN_DRAIN:
      *val = LSM6DSO32_OPEN_DRAIN;
      break;

    default:
      *val = LSM6DSO32_PUSH_PULL;
      break;
  }

  return ret;
}

/**
  * @brief  Interrupt active-high/low.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of h_lactive in reg CTRL3_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_pin_polarity_set(const stmdev_ctx_t *ctx,
                                   lsm6dso32_h_lactive_t val)
{
  lsm6dso32_ctrl3_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL3_C, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.h_lactive = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL3_C, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Interrupt active-high/low.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of h_lactive in reg CTRL3_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_pin_polarity_get(const stmdev_ctx_t *ctx,
                                   lsm6dso32_h_lactive_t *val)
{
  lsm6dso32_ctrl3_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL3_C, (uint8_t *)&reg, 1);

  switch (reg.h_lactive)
  {
    case LSM6DSO32_ACTIVE_HIGH:
      *val = LSM6DSO32_ACTIVE_HIGH;
      break;

    case LSM6DSO32_ACTIVE_LOW:
      *val = LSM6DSO32_ACTIVE_LOW;
      break;

    default:
      *val = LSM6DSO32_ACTIVE_HIGH;
      break;
  }

  return ret;
}

/**
  * @brief  All interrupt signals become available on INT1 pin.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of int2_on_int1 in reg CTRL4_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_all_on_int1_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_ctrl4_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL4_C, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.int2_on_int1 = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL4_C, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  All interrupt signals become available on INT1 pin.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of int2_on_int1 in reg CTRL4_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_all_on_int1_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_ctrl4_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL4_C, (uint8_t *)&reg, 1);
  *val = reg.int2_on_int1;

  return ret;
}

/**
  * @brief  Interrupt notification mode.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of lir in reg TAP_CFG0
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_int_notification_set(const stmdev_ctx_t *ctx,
                                       lsm6dso32_lir_t val)
{
  lsm6dso32_tap_cfg0_t tap_cfg0;
  lsm6dso32_page_rw_t page_rw;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_CFG0,
                           (uint8_t *) &tap_cfg0, 1);

  if (ret == 0)
  {
    tap_cfg0.lir = (uint8_t)val & 0x01U;
    tap_cfg0.int_clr_on_read = (uint8_t)val & 0x01U;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_TAP_CFG0,
                              (uint8_t *) &tap_cfg0, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_PAGE_RW, (uint8_t *) &page_rw, 1);
  }

  if (ret == 0)
  {
    page_rw.emb_func_lir = ((uint8_t)val & 0x02U) >> 1;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_PAGE_RW,
                              (uint8_t *) &page_rw, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Interrupt notification mode.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of lir in reg TAP_CFG0
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_int_notification_get(const stmdev_ctx_t *ctx,
                                       lsm6dso32_lir_t *val)
{
  lsm6dso32_tap_cfg0_t tap_cfg0;
  lsm6dso32_page_rw_t page_rw;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_CFG0,
                           (uint8_t *) &tap_cfg0, 1);

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_PAGE_RW, (uint8_t *) &page_rw, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  if (ret == 0)
  {
    switch ((page_rw.emb_func_lir << 1) | tap_cfg0.lir)
    {
      case LSM6DSO32_ALL_INT_PULSED:
        *val = LSM6DSO32_ALL_INT_PULSED;
        break;

      case LSM6DSO32_BASE_LATCHED_EMB_PULSED:
        *val = LSM6DSO32_BASE_LATCHED_EMB_PULSED;
        break;

      case LSM6DSO32_BASE_PULSED_EMB_LATCHED:
        *val = LSM6DSO32_BASE_PULSED_EMB_LATCHED;
        break;

      case LSM6DSO32_ALL_INT_LATCHED:
        *val = LSM6DSO32_ALL_INT_LATCHED;
        break;

      default:
        *val = LSM6DSO32_ALL_INT_PULSED;
        break;
    }

    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_PAGE_RW, (uint8_t *) &page_rw, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  LSM6DSO32_Wake_Up_event
  * @brief     This section groups all the functions that manage the Wake Up
  *            event generation.
  * @{
  *
  */

/**
  * @brief  Weight of 1 LSB of wakeup threshold.[set]
  *         0: 1 LSB =FS_XL  /  64
  *         1: 1 LSB = FS_XL / 256
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of wake_ths_w in
  *                                 reg WAKE_UP_DUR
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_wkup_ths_weight_set(const stmdev_ctx_t *ctx,
                                      lsm6dso32_wake_ths_w_t val)
{
  lsm6dso32_wake_up_dur_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_WAKE_UP_DUR, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.wake_ths_w = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_WAKE_UP_DUR, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Weight of 1 LSB of wakeup threshold.[get]
  *         0: 1 LSB =FS_XL  /  64
  *         1: 1 LSB = FS_XL / 256
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of wake_ths_w in
  *                                 reg WAKE_UP_DUR
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_wkup_ths_weight_get(const stmdev_ctx_t *ctx,
                                      lsm6dso32_wake_ths_w_t *val)
{
  lsm6dso32_wake_up_dur_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_WAKE_UP_DUR, (uint8_t *)&reg, 1);

  switch (reg.wake_ths_w)
  {
    case LSM6DSO32_LSb_FS_DIV_64:
      *val = LSM6DSO32_LSb_FS_DIV_64;
      break;

    case LSM6DSO32_LSb_FS_DIV_256:
      *val = LSM6DSO32_LSb_FS_DIV_256;
      break;

    default:
      *val = LSM6DSO32_LSb_FS_DIV_64;
      break;
  }

  return ret;
}

/**
  * @brief  Threshold for wakeup: 1 LSB weight depends on WAKE_THS_W in
  *         WAKE_UP_DUR.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of wk_ths in reg WAKE_UP_THS
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_wkup_threshold_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_wake_up_ths_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_WAKE_UP_THS, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.wk_ths = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_WAKE_UP_THS, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Threshold for wakeup: 1 LSB weight depends on WAKE_THS_W in
  *         WAKE_UP_DUR.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of wk_ths in reg WAKE_UP_THS
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_wkup_threshold_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_wake_up_ths_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_WAKE_UP_THS, (uint8_t *)&reg, 1);
  *val = reg.wk_ths;

  return ret;
}

/**
  * @brief  Wake up duration event.[set]
  *         1LSb = 1 / ODR
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of usr_off_on_wu in reg WAKE_UP_THS
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_usr_offset_on_wkup_set(const stmdev_ctx_t *ctx,
                                            uint8_t val)
{
  lsm6dso32_wake_up_ths_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_WAKE_UP_THS, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.usr_off_on_wu = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_WAKE_UP_THS, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Wake up duration event.[get]
  *         1LSb = 1 / ODR
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of usr_off_on_wu in reg WAKE_UP_THS
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_xl_usr_offset_on_wkup_get(const stmdev_ctx_t *ctx,
                                            uint8_t *val)
{
  lsm6dso32_wake_up_ths_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_WAKE_UP_THS, (uint8_t *)&reg, 1);
  *val = reg.usr_off_on_wu;

  return ret;
}

/**
  * @brief  Wake up duration event.[set]
  *         1LSb = 1 / ODR
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of wake_dur in reg WAKE_UP_DUR
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_wkup_dur_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_wake_up_dur_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_WAKE_UP_DUR, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.wake_dur = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_WAKE_UP_DUR, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Wake up duration event.[get]
  *         1LSb = 1 / ODR
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of wake_dur in reg WAKE_UP_DUR
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_wkup_dur_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_wake_up_dur_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_WAKE_UP_DUR, (uint8_t *)&reg, 1);
  *val = reg.wake_dur;

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  LSM6DSO32_ Activity/Inactivity_detection
  * @brief     This section groups all the functions concerning
  *            activity/inactivity detection.
  * @{
  *
  */

/**
  * @brief  Enables gyroscope Sleep mode.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of sleep_g in reg CTRL4_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_gy_sleep_mode_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_ctrl4_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL4_C, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.sleep_g = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL4_C, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Enables gyroscope Sleep mode.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of sleep_g in reg CTRL4_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_gy_sleep_mode_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_ctrl4_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL4_C, (uint8_t *)&reg, 1);
  *val = reg.sleep_g;

  return ret;
}

/**
  * @brief  Drives the sleep status instead of
  *         sleep change on INT pins
  *         (only if INT1_SLEEP_CHANGE or
  *         INT2_SLEEP_CHANGE bits are enabled).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of sleep_status_on_int in reg TAP_CFG0
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_act_pin_notification_set(const stmdev_ctx_t *ctx,
                                           lsm6dso32_sleep_status_on_int_t val)
{
  lsm6dso32_tap_cfg0_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_CFG0, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.sleep_status_on_int = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_TAP_CFG0, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Drives the sleep status instead of
  *         sleep change on INT pins (only if
  *         INT1_SLEEP_CHANGE or
  *         INT2_SLEEP_CHANGE bits are enabled).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of sleep_status_on_int in reg TAP_CFG0
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_act_pin_notification_get(const stmdev_ctx_t *ctx,
                                           lsm6dso32_sleep_status_on_int_t *val)
{
  lsm6dso32_tap_cfg0_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_CFG0, (uint8_t *)&reg, 1);

  switch (reg.sleep_status_on_int)
  {
    case LSM6DSO32_DRIVE_SLEEP_CHG_EVENT:
      *val = LSM6DSO32_DRIVE_SLEEP_CHG_EVENT;
      break;

    case LSM6DSO32_DRIVE_SLEEP_STATUS:
      *val = LSM6DSO32_DRIVE_SLEEP_STATUS;
      break;

    default:
      *val = LSM6DSO32_DRIVE_SLEEP_CHG_EVENT;
      break;
  }

  return ret;
}

/**
  * @brief  Enable inactivity function.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of inact_en in reg TAP_CFG2
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_act_mode_set(const stmdev_ctx_t *ctx,
                               lsm6dso32_inact_en_t val)
{
  lsm6dso32_tap_cfg2_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_CFG2, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.inact_en = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_TAP_CFG2, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Enable inactivity function.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of inact_en in reg TAP_CFG2
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_act_mode_get(const stmdev_ctx_t *ctx,
                               lsm6dso32_inact_en_t *val)
{
  lsm6dso32_tap_cfg2_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_CFG2, (uint8_t *)&reg, 1);

  switch (reg.inact_en)
  {
    case LSM6DSO32_XL_AND_GY_NOT_AFFECTED:
      *val = LSM6DSO32_XL_AND_GY_NOT_AFFECTED;
      break;

    case LSM6DSO32_XL_12Hz5_GY_NOT_AFFECTED:
      *val = LSM6DSO32_XL_12Hz5_GY_NOT_AFFECTED;
      break;

    case LSM6DSO32_XL_12Hz5_GY_SLEEP:
      *val = LSM6DSO32_XL_12Hz5_GY_SLEEP;
      break;

    case LSM6DSO32_XL_12Hz5_GY_PD:
      *val = LSM6DSO32_XL_12Hz5_GY_PD;
      break;

    default:
      *val = LSM6DSO32_XL_AND_GY_NOT_AFFECTED;
      break;
  }

  return ret;
}

/**
  * @brief  Duration to go in sleep mode.[set]
  *         1 LSb = 512 / ODR
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of sleep_dur in reg WAKE_UP_DUR
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_act_sleep_dur_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_wake_up_dur_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_WAKE_UP_DUR, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.sleep_dur = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_WAKE_UP_DUR, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Duration to go in sleep mode.[get]
  *         1 LSb = 512 / ODR
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of sleep_dur in reg WAKE_UP_DUR
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_act_sleep_dur_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_wake_up_dur_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_WAKE_UP_DUR, (uint8_t *)&reg, 1);
  *val = reg.sleep_dur;

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  LSM6DSO32_tap_generator
  * @brief     This section groups all the functions that manage the
  *            tap and double tap event generation.
  * @{
  *
  */

/**
  * @brief  Enable Z direction in tap recognition.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of tap_z_en in reg TAP_CFG0
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_tap_detection_on_z_set(const stmdev_ctx_t *ctx,
                                         uint8_t val)
{
  lsm6dso32_tap_cfg0_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_CFG0, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.tap_z_en = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_TAP_CFG0, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Enable Z direction in tap recognition.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of tap_z_en in reg TAP_CFG0
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_tap_detection_on_z_get(const stmdev_ctx_t *ctx,
                                         uint8_t *val)
{
  lsm6dso32_tap_cfg0_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_CFG0, (uint8_t *)&reg, 1);
  *val = reg.tap_z_en;

  return ret;
}

/**
  * @brief  Enable Y direction in tap recognition.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of tap_y_en in reg TAP_CFG0
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_tap_detection_on_y_set(const stmdev_ctx_t *ctx,
                                         uint8_t val)
{
  lsm6dso32_tap_cfg0_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_CFG0, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.tap_y_en = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_TAP_CFG0, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Enable Y direction in tap recognition.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of tap_y_en in reg TAP_CFG0
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_tap_detection_on_y_get(const stmdev_ctx_t *ctx,
                                         uint8_t *val)
{
  lsm6dso32_tap_cfg0_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_CFG0, (uint8_t *)&reg, 1);
  *val = reg.tap_y_en;

  return ret;
}

/**
  * @brief  Enable X direction in tap recognition.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of tap_x_en in reg TAP_CFG0
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_tap_detection_on_x_set(const stmdev_ctx_t *ctx,
                                         uint8_t val)
{
  lsm6dso32_tap_cfg0_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_CFG0, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.tap_x_en = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_TAP_CFG0, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Enable X direction in tap recognition.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of tap_x_en in reg TAP_CFG0
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_tap_detection_on_x_get(const stmdev_ctx_t *ctx,
                                         uint8_t *val)
{
  lsm6dso32_tap_cfg0_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_CFG0, (uint8_t *)&reg, 1);
  *val = reg.tap_x_en;

  return ret;
}

/**
  * @brief  X-axis tap recognition threshold.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of tap_ths_x in reg TAP_CFG1
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_tap_threshold_x_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_tap_cfg1_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_CFG1, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.tap_ths_x = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_TAP_CFG1, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  X-axis tap recognition threshold.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of tap_ths_x in reg TAP_CFG1
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_tap_threshold_x_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_tap_cfg1_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_CFG1, (uint8_t *)&reg, 1);
  *val = reg.tap_ths_x;

  return ret;
}

/**
  * @brief  Selection of axis priority for TAP detection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of tap_priority in reg TAP_CFG1
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_tap_axis_priority_set(const stmdev_ctx_t *ctx,
                                        lsm6dso32_tap_priority_t val)
{
  lsm6dso32_tap_cfg1_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_CFG1, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.tap_priority = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_TAP_CFG1, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Selection of axis priority for TAP detection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of tap_priority in reg TAP_CFG1
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_tap_axis_priority_get(const stmdev_ctx_t *ctx,
                                        lsm6dso32_tap_priority_t *val)
{
  lsm6dso32_tap_cfg1_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_CFG1, (uint8_t *)&reg, 1);

  switch (reg.tap_priority)
  {
    case LSM6DSO32_XYZ:
      *val = LSM6DSO32_XYZ;
      break;

    case LSM6DSO32_YXZ:
      *val = LSM6DSO32_YXZ;
      break;

    case LSM6DSO32_XZY:
      *val = LSM6DSO32_XZY;
      break;

    case LSM6DSO32_ZYX:
      *val = LSM6DSO32_ZYX;
      break;

    case LSM6DSO32_YZX:
      *val = LSM6DSO32_YZX;
      break;

    case LSM6DSO32_ZXY:
      *val = LSM6DSO32_ZXY;
      break;

    default:
      *val = LSM6DSO32_XYZ;
      break;
  }

  return ret;
}

/**
  * @brief  Y-axis tap recognition threshold.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of tap_ths_y in reg TAP_CFG2
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_tap_threshold_y_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_tap_cfg2_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_CFG2, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.tap_ths_y = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_TAP_CFG2, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Y-axis tap recognition threshold.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of tap_ths_y in reg TAP_CFG2
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_tap_threshold_y_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_tap_cfg2_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_CFG2, (uint8_t *)&reg, 1);
  *val = reg.tap_ths_y;

  return ret;
}

/**
  * @brief  Z-axis recognition threshold.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of tap_ths_z in reg TAP_THS_6D
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_tap_threshold_z_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_tap_ths_6d_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_THS_6D, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.tap_ths_z = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_TAP_THS_6D, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Z-axis recognition threshold.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of tap_ths_z in reg TAP_THS_6D
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_tap_threshold_z_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_tap_ths_6d_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_THS_6D, (uint8_t *)&reg, 1);
  *val = reg.tap_ths_z;

  return ret;
}

/**
  * @brief  Maximum duration is the maximum time of an
  *         over threshold signal detection to be recognized
  *         as a tap event. The default value of these bits
  *         is 00b which corresponds to 4*ODR_XL time.
  *         If the SHOCK[1:0] bits are set to a different
  *         value, 1LSB corresponds to 8*ODR_XL time.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of shock in reg INT_DUR2
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_tap_shock_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_int_dur2_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_INT_DUR2, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.shock = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_INT_DUR2, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Maximum duration is the maximum time of an
  *         over threshold signal detection to be recognized
  *         as a tap event. The default value of these bits
  *         is 00b which corresponds to 4*ODR_XL time.
  *         If the SHOCK[1:0] bits are set to a different
  *         value, 1LSB corresponds to 8*ODR_XL time.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of shock in reg INT_DUR2
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_tap_shock_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_int_dur2_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_INT_DUR2, (uint8_t *)&reg, 1);
  *val = reg.shock;

  return ret;
}

/**
  * @brief   Quiet time is the time after the first detected
  *          tap in which there must not be any over threshold
  *          event.
  *          The default value of these bits is 00b which
  *          corresponds to 2*ODR_XL time. If the QUIET[1:0]
  *          bits are set to a different value,
  *          1LSB corresponds to 4*ODR_XL time.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of quiet in reg INT_DUR2
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_tap_quiet_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_int_dur2_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_INT_DUR2, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.quiet = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_INT_DUR2, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Quiet time is the time after the first detected
  *         tap in which there must not be any over threshold
  *         event.
  *         The default value of these bits is 00b which
  *         corresponds to 2*ODR_XL time.
  *         If the QUIET[1:0] bits are set to a different
  *         value, 1LSB corresponds to 4*ODR_XL time.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of quiet in reg INT_DUR2
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_tap_quiet_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_int_dur2_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_INT_DUR2, (uint8_t *)&reg, 1);
  *val = reg.quiet;

  return ret;
}

/**
  * @brief  When double tap recognition is enabled,
  *         this register expresses the maximum time
  *         between two consecutive detected taps to
  *         determine a double tap event.
  *         The default value of these bits is 0000b which
  *         corresponds to 16*ODR_XL time.
  *         If the DUR[3:0] bits are set to a different value,
  *         1LSB corresponds to 32*ODR_XL time.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of dur in reg INT_DUR2
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_tap_dur_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_int_dur2_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_INT_DUR2, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.dur = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_INT_DUR2, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  When double tap recognition is enabled,
  *         this register expresses the maximum time
  *         between two consecutive detected taps to
  *         determine a double tap event.
  *         The default value of these bits is 0000b which
  *         corresponds to 16*ODR_XL time. If the DUR[3:0]
  *         bits are set to a different value,
  *         1LSB corresponds to 32*ODR_XL time.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of dur in reg INT_DUR2
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_tap_dur_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_int_dur2_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_INT_DUR2, (uint8_t *)&reg, 1);
  *val = reg.dur;

  return ret;
}

/**
  * @brief  Single/double-tap event enable.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of single_double_tap in reg WAKE_UP_THS
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_tap_mode_set(const stmdev_ctx_t *ctx,
                               lsm6dso32_single_double_tap_t val)
{
  lsm6dso32_wake_up_ths_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_WAKE_UP_THS, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.single_double_tap = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_WAKE_UP_THS, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Single/double-tap event enable.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of single_double_tap in reg WAKE_UP_THS
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_tap_mode_get(const stmdev_ctx_t *ctx,
                               lsm6dso32_single_double_tap_t *val)
{
  lsm6dso32_wake_up_ths_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_WAKE_UP_THS, (uint8_t *)&reg, 1);

  switch (reg.single_double_tap)
  {
    case LSM6DSO32_ONLY_SINGLE:
      *val = LSM6DSO32_ONLY_SINGLE;
      break;

    case LSM6DSO32_BOTH_SINGLE_DOUBLE:
      *val = LSM6DSO32_BOTH_SINGLE_DOUBLE;
      break;

    default:
      *val = LSM6DSO32_ONLY_SINGLE;
      break;
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  LSM6DSO32_ Six_position_detection(6D/4D)
  * @brief   This section groups all the functions concerning six position
  *          detection (6D).
  * @{
  *
  */

/**
  * @brief  Threshold for 4D/6D function.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of sixd_ths in reg TAP_THS_6D
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_6d_threshold_set(const stmdev_ctx_t *ctx,
                                   lsm6dso32_sixd_ths_t val)
{
  lsm6dso32_tap_ths_6d_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_THS_6D, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.sixd_ths = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_TAP_THS_6D, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Threshold for 4D/6D function.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of sixd_ths in reg TAP_THS_6D
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_6d_threshold_get(const stmdev_ctx_t *ctx,
                                   lsm6dso32_sixd_ths_t *val)
{
  lsm6dso32_tap_ths_6d_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_THS_6D, (uint8_t *)&reg, 1);

  switch (reg.sixd_ths)
  {
    case LSM6DSO32_DEG_68:
      *val = LSM6DSO32_DEG_68;
      break;

    case LSM6DSO32_DEG_47:
      *val = LSM6DSO32_DEG_47;
      break;

    default:
      *val = LSM6DSO32_DEG_68;
      break;
  }

  return ret;
}

/**
  * @brief  4D orientation detection enable.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of d4d_en in reg TAP_THS_6D
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_4d_mode_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_tap_ths_6d_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_THS_6D, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.d4d_en = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_TAP_THS_6D, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  4D orientation detection enable.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of d4d_en in reg TAP_THS_6D
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_4d_mode_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_tap_ths_6d_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_TAP_THS_6D, (uint8_t *)&reg, 1);
  *val = reg.d4d_en;

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  LSM6DSO32_free_fall
  * @brief   This section group all the functions concerning the free
  *          fall detection.
  * @{
  *
  */

/**
  * @brief  Free fall threshold setting.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of ff_ths in reg FREE_FALL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_ff_threshold_set(const stmdev_ctx_t *ctx,
                                   lsm6dso32_ff_ths_t val)
{
  lsm6dso32_free_fall_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FREE_FALL, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.ff_ths = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_FREE_FALL, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Free fall threshold setting.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of ff_ths in reg FREE_FALL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_ff_threshold_get(const stmdev_ctx_t *ctx,
                                   lsm6dso32_ff_ths_t *val)
{
  lsm6dso32_free_fall_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FREE_FALL, (uint8_t *)&reg, 1);

  switch (reg.ff_ths)
  {
    case LSM6DSO32_FF_TSH_312mg:
      *val = LSM6DSO32_FF_TSH_312mg;
      break;

    case LSM6DSO32_FF_TSH_438mg:
      *val = LSM6DSO32_FF_TSH_438mg;
      break;

    case LSM6DSO32_FF_TSH_500mg:
      *val = LSM6DSO32_FF_TSH_500mg;
      break;

    default:
      *val = LSM6DSO32_FF_TSH_312mg;
      break;
  }

  return ret;
}

/**
  * @brief  Free-fall duration event.[set]
  *         1LSb = 1 / ODR
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of ff_dur in reg FREE_FALL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_ff_dur_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_wake_up_dur_t wake_up_dur;
  lsm6dso32_free_fall_t free_fall;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_WAKE_UP_DUR,
                           (uint8_t *)&wake_up_dur, 1);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FREE_FALL,
                             (uint8_t *)&free_fall, 1);
  }

  if (ret == 0)
  {
    wake_up_dur.ff_dur = ((uint8_t)val & 0x20U) >> 5;
    free_fall.ff_dur = (uint8_t)val & 0x1FU;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_WAKE_UP_DUR,
                              (uint8_t *)&wake_up_dur, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_FREE_FALL,
                              (uint8_t *)&free_fall, 1);
  }

  return ret;
}

/**
  * @brief  Free-fall duration event.[get]
  *         1LSb = 1 / ODR
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of ff_dur in reg FREE_FALL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_ff_dur_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_wake_up_dur_t wake_up_dur;
  lsm6dso32_free_fall_t free_fall;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_WAKE_UP_DUR,
                           (uint8_t *)&wake_up_dur, 1);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FREE_FALL,
                             (uint8_t *)&free_fall, 1);
    *val = (wake_up_dur.ff_dur << 5) + free_fall.ff_dur;
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  LSM6DSO32_fifo
  * @brief   This section group all the functions concerning the fifo usage
  * @{
  *
  */

/**
  * @brief  FIFO watermark level selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of wtm in reg FIFO_CTRL1
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fifo_watermark_set(const stmdev_ctx_t *ctx, uint16_t val)
{
  lsm6dso32_fifo_ctrl1_t fifo_ctrl1;
  lsm6dso32_fifo_ctrl2_t fifo_ctrl2;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_CTRL2,
                           (uint8_t *)&fifo_ctrl2, 1);

  if (ret == 0)
  {
    fifo_ctrl1.wtm = 0x00FFU & (uint8_t)val;
    fifo_ctrl2.wtm = (uint8_t)((0x0100U & val) >> 8);
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_FIFO_CTRL1,
                              (uint8_t *)&fifo_ctrl1, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_FIFO_CTRL2,
                              (uint8_t *)&fifo_ctrl2, 1);
  }

  return ret;
}

/**
  * @brief  FIFO watermark level selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of wtm in reg FIFO_CTRL1
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fifo_watermark_get(const stmdev_ctx_t *ctx, uint16_t *val)
{
  lsm6dso32_fifo_ctrl1_t fifo_ctrl1;
  lsm6dso32_fifo_ctrl2_t fifo_ctrl2;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_CTRL1,
                           (uint8_t *)&fifo_ctrl1, 1);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_CTRL2,
                             (uint8_t *)&fifo_ctrl2, 1);
    *val = ((uint16_t)fifo_ctrl2.wtm << 8) + (uint16_t)fifo_ctrl1.wtm;
  }

  return ret;
}

/**
  * @brief  FIFO compression feature initialization request [set].
  *
  * @param  ctx       read / write interface definitions
  * @param  val       change the values of FIFO_COMPR_INIT in
  *                   reg EMB_FUNC_INIT_B
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_compression_algo_init_set(const stmdev_ctx_t *ctx,
                                            uint8_t val)
{
  lsm6dso32_emb_func_init_b_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_INIT_B,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    reg.fifo_compr_init = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_EMB_FUNC_INIT_B,
                              (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  FIFO compression feature initialization request [get].
  *
  * @param  ctx    read / write interface definitions
  * @param  val    change the values of FIFO_COMPR_INIT in
  *                reg EMB_FUNC_INIT_B
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_compression_algo_init_get(const stmdev_ctx_t *ctx,
                                            uint8_t *val)
{
  lsm6dso32_emb_func_init_b_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_INIT_B,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    *val = reg.fifo_compr_init;
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Enable and configure compression algo.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of uncoptr_rate in
  *                  reg FIFO_CTRL2
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_compression_algo_set(const stmdev_ctx_t *ctx,
                                       lsm6dso32_uncoptr_rate_t val)
{
  lsm6dso32_emb_func_en_b_t emb_func_en_b;
  lsm6dso32_fifo_ctrl2_t fifo_ctrl2;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_EN_B,
                             (uint8_t *)&emb_func_en_b, 1);
  }

  if (ret == 0)
  {
    emb_func_en_b.fifo_compr_en = ((uint8_t)val & 0x04U) >> 2;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_EMB_FUNC_EN_B,
                              (uint8_t *)&emb_func_en_b, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_CTRL2,
                             (uint8_t *)&fifo_ctrl2, 1);
  }

  if (ret == 0)
  {
    fifo_ctrl2.fifo_compr_rt_en = ((uint8_t)val & 0x04U) >> 2;
    fifo_ctrl2.uncoptr_rate = (uint8_t)val & 0x03U;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_FIFO_CTRL2,
                              (uint8_t *)&fifo_ctrl2, 1);
  }

  return ret;
}

/**
  * @brief  Enable and configure compression algo.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of uncoptr_rate in
  *                  reg FIFO_CTRL2
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_compression_algo_get(const stmdev_ctx_t *ctx,
                                       lsm6dso32_uncoptr_rate_t *val)
{
  lsm6dso32_fifo_ctrl2_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_CTRL2, (uint8_t *)&reg, 1);

  switch ((reg.fifo_compr_rt_en << 2) | reg.uncoptr_rate)
  {
    case LSM6DSO32_CMP_DISABLE:
      *val = LSM6DSO32_CMP_DISABLE;
      break;

    case LSM6DSO32_CMP_ALWAYS:
      *val = LSM6DSO32_CMP_ALWAYS;
      break;

    case LSM6DSO32_CMP_8_TO_1:
      *val = LSM6DSO32_CMP_8_TO_1;
      break;

    case LSM6DSO32_CMP_16_TO_1:
      *val = LSM6DSO32_CMP_16_TO_1;
      break;

    case LSM6DSO32_CMP_32_TO_1:
      *val = LSM6DSO32_CMP_32_TO_1;
      break;

    default:
      *val = LSM6DSO32_CMP_DISABLE;
      break;
  }

  return ret;
}

/**
  * @brief  Enables ODR CHANGE virtual sensor to be batched in FIFO.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of odrchg_en in reg FIFO_CTRL2
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fifo_virtual_sens_odr_chg_set(const stmdev_ctx_t *ctx,
                                                uint8_t val)
{
  lsm6dso32_fifo_ctrl2_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_CTRL2, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.odrchg_en = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_FIFO_CTRL2, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Enables ODR CHANGE virtual sensor to be batched in FIFO.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of odrchg_en in reg FIFO_CTRL2
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fifo_virtual_sens_odr_chg_get(const stmdev_ctx_t *ctx,
                                                uint8_t *val)
{
  lsm6dso32_fifo_ctrl2_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_CTRL2, (uint8_t *)&reg, 1);
  *val = reg.odrchg_en;

  return ret;
}

/**
  * @brief  Enables/Disables compression algorithm runtime.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of fifo_compr_rt_en in
  *                  reg FIFO_CTRL2
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_compression_algo_real_time_set(const stmdev_ctx_t *ctx,
                                                 uint8_t val)
{
  lsm6dso32_fifo_ctrl2_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_CTRL2, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.fifo_compr_rt_en = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_FIFO_CTRL2, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief   Enables/Disables compression algorithm runtime.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of fifo_compr_rt_en in reg FIFO_CTRL2
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_compression_algo_real_time_get(const stmdev_ctx_t *ctx,
                                                 uint8_t *val)
{
  lsm6dso32_fifo_ctrl2_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_CTRL2, (uint8_t *)&reg, 1);
  *val = reg.fifo_compr_rt_en;

  return ret;
}

/**
  * @brief  Sensing chain FIFO stop values memorization at
  *         threshold level.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of stop_on_wtm in reg FIFO_CTRL2
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fifo_stop_on_wtm_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_fifo_ctrl2_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_CTRL2, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.stop_on_wtm = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_FIFO_CTRL2, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Sensing chain FIFO stop values memorization at
  *         threshold level.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of stop_on_wtm in reg FIFO_CTRL2
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fifo_stop_on_wtm_get(const stmdev_ctx_t *ctx,
                                       uint8_t *val)
{
  lsm6dso32_fifo_ctrl2_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_CTRL2, (uint8_t *)&reg, 1);
  *val = reg.stop_on_wtm;

  return ret;
}

/**
  * @brief  Selects Batching Data Rate (writing frequency in FIFO)
  *         for accelerometer data.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of bdr_xl in reg FIFO_CTRL3
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fifo_xl_batch_set(const stmdev_ctx_t *ctx,
                                    lsm6dso32_bdr_xl_t val)
{
  lsm6dso32_fifo_ctrl3_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_CTRL3, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.bdr_xl = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_FIFO_CTRL3, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Selects Batching Data Rate (writing frequency in FIFO)
  *         for accelerometer data.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of bdr_xl in reg FIFO_CTRL3
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fifo_xl_batch_get(const stmdev_ctx_t *ctx,
                                    lsm6dso32_bdr_xl_t *val)
{
  lsm6dso32_fifo_ctrl3_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_CTRL3, (uint8_t *)&reg, 1);

  switch (reg.bdr_xl)
  {
    case LSM6DSO32_XL_NOT_BATCHED:
      *val = LSM6DSO32_XL_NOT_BATCHED;
      break;

    case LSM6DSO32_XL_BATCHED_AT_12Hz5:
      *val = LSM6DSO32_XL_BATCHED_AT_12Hz5;
      break;

    case LSM6DSO32_XL_BATCHED_AT_26Hz:
      *val = LSM6DSO32_XL_BATCHED_AT_26Hz;
      break;

    case LSM6DSO32_XL_BATCHED_AT_52Hz:
      *val = LSM6DSO32_XL_BATCHED_AT_52Hz;
      break;

    case LSM6DSO32_XL_BATCHED_AT_104Hz:
      *val = LSM6DSO32_XL_BATCHED_AT_104Hz;
      break;

    case LSM6DSO32_XL_BATCHED_AT_208Hz:
      *val = LSM6DSO32_XL_BATCHED_AT_208Hz;
      break;

    case LSM6DSO32_XL_BATCHED_AT_417Hz:
      *val = LSM6DSO32_XL_BATCHED_AT_417Hz;
      break;

    case LSM6DSO32_XL_BATCHED_AT_833Hz:
      *val = LSM6DSO32_XL_BATCHED_AT_833Hz;
      break;

    case LSM6DSO32_XL_BATCHED_AT_1667Hz:
      *val = LSM6DSO32_XL_BATCHED_AT_1667Hz;
      break;

    case LSM6DSO32_XL_BATCHED_AT_3333Hz:
      *val = LSM6DSO32_XL_BATCHED_AT_3333Hz;
      break;

    case LSM6DSO32_XL_BATCHED_AT_6667Hz:
      *val = LSM6DSO32_XL_BATCHED_AT_6667Hz;
      break;

    case LSM6DSO32_XL_BATCHED_AT_6Hz5:
      *val = LSM6DSO32_XL_BATCHED_AT_6Hz5;
      break;

    default:
      *val = LSM6DSO32_XL_NOT_BATCHED;
      break;
  }

  return ret;
}

/**
  * @brief  Selects Batching Data Rate (writing frequency in FIFO)
  *         for gyroscope data.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of bdr_gy in reg FIFO_CTRL3
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fifo_gy_batch_set(const stmdev_ctx_t *ctx,
                                    lsm6dso32_bdr_gy_t val)
{
  lsm6dso32_fifo_ctrl3_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_CTRL3, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.bdr_gy = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_FIFO_CTRL3, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Selects Batching Data Rate (writing frequency in FIFO)
  *         for gyroscope data.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of bdr_gy in reg FIFO_CTRL3
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fifo_gy_batch_get(const stmdev_ctx_t *ctx,
                                    lsm6dso32_bdr_gy_t *val)
{
  lsm6dso32_fifo_ctrl3_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_CTRL3, (uint8_t *)&reg, 1);

  switch (reg.bdr_gy)
  {
    case LSM6DSO32_GY_NOT_BATCHED:
      *val = LSM6DSO32_GY_NOT_BATCHED;
      break;

    case LSM6DSO32_GY_BATCHED_AT_12Hz5:
      *val = LSM6DSO32_GY_BATCHED_AT_12Hz5;
      break;

    case LSM6DSO32_GY_BATCHED_AT_26Hz:
      *val = LSM6DSO32_GY_BATCHED_AT_26Hz;
      break;

    case LSM6DSO32_GY_BATCHED_AT_52Hz:
      *val = LSM6DSO32_GY_BATCHED_AT_52Hz;
      break;

    case LSM6DSO32_GY_BATCHED_AT_104Hz:
      *val = LSM6DSO32_GY_BATCHED_AT_104Hz;
      break;

    case LSM6DSO32_GY_BATCHED_AT_208Hz:
      *val = LSM6DSO32_GY_BATCHED_AT_208Hz;
      break;

    case LSM6DSO32_GY_BATCHED_AT_417Hz:
      *val = LSM6DSO32_GY_BATCHED_AT_417Hz;
      break;

    case LSM6DSO32_GY_BATCHED_AT_833Hz:
      *val = LSM6DSO32_GY_BATCHED_AT_833Hz;
      break;

    case LSM6DSO32_GY_BATCHED_AT_1667Hz:
      *val = LSM6DSO32_GY_BATCHED_AT_1667Hz;
      break;

    case LSM6DSO32_GY_BATCHED_AT_3333Hz:
      *val = LSM6DSO32_GY_BATCHED_AT_3333Hz;
      break;

    case LSM6DSO32_GY_BATCHED_AT_6667Hz:
      *val = LSM6DSO32_GY_BATCHED_AT_6667Hz;
      break;

    case LSM6DSO32_GY_BATCHED_AT_6Hz5:
      *val = LSM6DSO32_GY_BATCHED_AT_6Hz5;
      break;

    default:
      *val = LSM6DSO32_GY_NOT_BATCHED;
      break;
  }

  return ret;
}

/**
  * @brief  FIFO mode selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of fifo_mode in reg FIFO_CTRL4
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fifo_mode_set(const stmdev_ctx_t *ctx,
                                lsm6dso32_fifo_mode_t val)
{
  lsm6dso32_fifo_ctrl4_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_CTRL4, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.fifo_mode = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_FIFO_CTRL4, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  FIFO mode selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of fifo_mode in reg FIFO_CTRL4
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fifo_mode_get(const stmdev_ctx_t *ctx,
                                lsm6dso32_fifo_mode_t *val)
{
  lsm6dso32_fifo_ctrl4_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_CTRL4, (uint8_t *)&reg, 1);

  switch (reg.fifo_mode)
  {
    case LSM6DSO32_BYPASS_MODE:
      *val = LSM6DSO32_BYPASS_MODE;
      break;

    case LSM6DSO32_FIFO_MODE:
      *val = LSM6DSO32_FIFO_MODE;
      break;

    case LSM6DSO32_STREAM_TO_FIFO_MODE:
      *val = LSM6DSO32_STREAM_TO_FIFO_MODE;
      break;

    case LSM6DSO32_BYPASS_TO_STREAM_MODE:
      *val = LSM6DSO32_BYPASS_TO_STREAM_MODE;
      break;

    case LSM6DSO32_STREAM_MODE:
      *val = LSM6DSO32_STREAM_MODE;
      break;

    case LSM6DSO32_BYPASS_TO_FIFO_MODE:
      *val = LSM6DSO32_BYPASS_TO_FIFO_MODE;
      break;

    default:
      *val = LSM6DSO32_BYPASS_MODE;
      break;
  }

  return ret;
}

/**
  * @brief  Selects Batching Data Rate (writing frequency in FIFO)
  *         for temperature data.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of odr_t_batch in reg FIFO_CTRL4
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fifo_temp_batch_set(const stmdev_ctx_t *ctx,
                                      lsm6dso32_odr_t_batch_t val)
{
  lsm6dso32_fifo_ctrl4_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_CTRL4, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.odr_t_batch = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_FIFO_CTRL4, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Selects Batching Data Rate (writing frequency in FIFO)
  *         for temperature data.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of odr_t_batch in reg FIFO_CTRL4
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fifo_temp_batch_get(const stmdev_ctx_t *ctx,
                                      lsm6dso32_odr_t_batch_t *val)
{
  lsm6dso32_fifo_ctrl4_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_CTRL4, (uint8_t *)&reg, 1);

  switch (reg.odr_t_batch)
  {
    case LSM6DSO32_TEMP_NOT_BATCHED:
      *val = LSM6DSO32_TEMP_NOT_BATCHED;
      break;

    case LSM6DSO32_TEMP_BATCHED_AT_1Hz6:
      *val = LSM6DSO32_TEMP_BATCHED_AT_1Hz6;
      break;

    case LSM6DSO32_TEMP_BATCHED_AT_12Hz5:
      *val = LSM6DSO32_TEMP_BATCHED_AT_12Hz5;
      break;

    case LSM6DSO32_TEMP_BATCHED_AT_52Hz:
      *val = LSM6DSO32_TEMP_BATCHED_AT_52Hz;
      break;

    default:
      *val = LSM6DSO32_TEMP_NOT_BATCHED;
      break;
  }

  return ret;
}

/**
  * @brief  Selects decimation for timestamp batching in FIFO.
  *         Writing rate will be the maximum rate between XL and
  *         GYRO BDR divided by decimation decoder.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of odr_ts_batch in reg FIFO_CTRL4
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fifo_timestamp_decimation_set(const stmdev_ctx_t *ctx,
                                                lsm6dso32_odr_ts_batch_t val)
{
  lsm6dso32_fifo_ctrl4_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_CTRL4, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.odr_ts_batch = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_FIFO_CTRL4, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief   Selects decimation for timestamp batching in FIFO.
  *          Writing rate will be the maximum rate between XL and
  *          GYRO BDR divided by decimation decoder.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of odr_ts_batch in reg FIFO_CTRL4
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fifo_timestamp_decimation_get(const stmdev_ctx_t *ctx,
                                                lsm6dso32_odr_ts_batch_t *val)
{
  lsm6dso32_fifo_ctrl4_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_CTRL4, (uint8_t *)&reg, 1);

  switch (reg.odr_ts_batch)
  {
    case LSM6DSO32_NO_DECIMATION:
      *val = LSM6DSO32_NO_DECIMATION;
      break;

    case LSM6DSO32_DEC_1:
      *val = LSM6DSO32_DEC_1;
      break;

    case LSM6DSO32_DEC_8:
      *val = LSM6DSO32_DEC_8;
      break;

    case LSM6DSO32_DEC_32:
      *val = LSM6DSO32_DEC_32;
      break;

    default:
      *val = LSM6DSO32_NO_DECIMATION;
      break;
  }

  return ret;
}

/**
  * @brief  Selects the trigger for the internal counter of batching events
  *         between XL and gyro.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of trig_counter_bdr
  *                  in reg COUNTER_BDR_REG1
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fifo_cnt_event_batch_set(const stmdev_ctx_t *ctx,
                                           lsm6dso32_trig_counter_bdr_t val)
{
  lsm6dso32_counter_bdr_reg1_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_COUNTER_BDR_REG1,
                           (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.trig_counter_bdr = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_COUNTER_BDR_REG1,
                              (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Selects the trigger for the internal counter of batching events
  *         between XL and gyro.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of trig_counter_bdr
  *                                     in reg COUNTER_BDR_REG1
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fifo_cnt_event_batch_get(const stmdev_ctx_t *ctx,
                                           lsm6dso32_trig_counter_bdr_t *val)
{
  lsm6dso32_counter_bdr_reg1_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_COUNTER_BDR_REG1,
                           (uint8_t *)&reg, 1);

  switch (reg.trig_counter_bdr)
  {
    case LSM6DSO32_XL_BATCH_EVENT:
      *val = LSM6DSO32_XL_BATCH_EVENT;
      break;

    case LSM6DSO32_GYRO_BATCH_EVENT:
      *val = LSM6DSO32_GYRO_BATCH_EVENT;
      break;

    default:
      *val = LSM6DSO32_XL_BATCH_EVENT;
      break;
  }

  return ret;
}

/**
  * @brief  Resets the internal counter of batching vents for a single sensor.
  *         This bit is automatically reset to zero if it was set to ‘1’.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of rst_counter_bdr in
  *                  reg COUNTER_BDR_REG1
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_rst_batch_counter_set(const stmdev_ctx_t *ctx,
                                        uint8_t val)
{
  lsm6dso32_counter_bdr_reg1_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_COUNTER_BDR_REG1,
                           (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.rst_counter_bdr = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_COUNTER_BDR_REG1,
                              (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  Resets the internal counter of batching events for a single sensor.
  *         This bit is automatically reset to zero if it was set to ‘1’.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of rst_counter_bdr in
  *                  reg COUNTER_BDR_REG1
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_rst_batch_counter_get(const stmdev_ctx_t *ctx,
                                        uint8_t *val)
{
  lsm6dso32_counter_bdr_reg1_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_COUNTER_BDR_REG1,
                           (uint8_t *)&reg, 1);
  *val = reg.rst_counter_bdr;

  return ret;
}

/**
  * @brief  Batch data rate counter.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of cnt_bdr_th in
  *                  reg COUNTER_BDR_REG2 and COUNTER_BDR_REG1.
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_batch_counter_threshold_set(const stmdev_ctx_t *ctx,
                                              uint16_t val)
{
  lsm6dso32_counter_bdr_reg1_t counter_bdr_reg1;
  lsm6dso32_counter_bdr_reg2_t counter_bdr_reg2;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_COUNTER_BDR_REG1,
                           (uint8_t *)&counter_bdr_reg1, 1);

  if (ret == 0)
  {
    counter_bdr_reg2.cnt_bdr_th =  0x00FFU & (uint8_t)val;
    counter_bdr_reg1.cnt_bdr_th = (uint8_t)(0x0700U & val) >> 8;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_COUNTER_BDR_REG1,
                              (uint8_t *)&counter_bdr_reg1, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_COUNTER_BDR_REG2,
                              (uint8_t *)&counter_bdr_reg2, 1);
  }

  return ret;
}

/**
  * @brief  Batch data rate counter.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of cnt_bdr_th in
  *                  reg COUNTER_BDR_REG2 and COUNTER_BDR_REG1.
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_batch_counter_threshold_get(const stmdev_ctx_t *ctx,
                                              uint16_t *val)
{
  lsm6dso32_counter_bdr_reg1_t counter_bdr_reg1;
  lsm6dso32_counter_bdr_reg2_t counter_bdr_reg2;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_COUNTER_BDR_REG1,
                           (uint8_t *)&counter_bdr_reg1, 1);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_COUNTER_BDR_REG2,
                             (uint8_t *)&counter_bdr_reg2, 1);
    *val = ((uint16_t)counter_bdr_reg1.cnt_bdr_th << 8)
           + (uint16_t)counter_bdr_reg2.cnt_bdr_th;
  }

  return ret;
}

/**
  * @brief  Number of unread sensor data (TAG + 6 bytes) stored in FIFO.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Read the value of diff_fifo in reg FIFO_STATUS1 and FIFO_STATUS2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dso32_fifo_data_level_get(const stmdev_ctx_t *ctx,
                                     uint16_t *val)
{
  uint8_t reg[2];
  lsm6dso32_fifo_status1_t *fifo_status1 = (lsm6dso32_fifo_status1_t *)&reg[0];
  lsm6dso32_fifo_status2_t *fifo_status2 = (lsm6dso32_fifo_status2_t *)&reg[1];
  int32_t ret;

  /* read both FIFO_STATUS1 + FIFO_STATUS2 regs */
  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_STATUS1, (uint8_t *)reg, 2);
  if (ret == 0)
  {
    *val = fifo_status2->diff_fifo;
    *val = (*val * 256U) + fifo_status1->diff_fifo;
  }

  return ret;
}

/**
  * @brief  Smart FIFO status.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Read registers FIFO_STATUS2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dso32_fifo_status_get(const stmdev_ctx_t *ctx,
                                 lsm6dso32_fifo_status2_t *val)
{
  uint8_t reg[2];
  lsm6dso32_fifo_status2_t *fifo_status2 = (lsm6dso32_fifo_status2_t *)&reg[1];
  int32_t ret;

  /* read both FIFO_STATUS1 + FIFO_STATUS2 regs */
  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_STATUS1, (uint8_t *)reg, 2);
  if (ret == 0)
  {
    *val = *fifo_status2;
  }

  return ret;
}

/**
  * @brief  Smart FIFO full status.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Read the values of fifo_full_ia in reg FIFO_STATUS2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dso32_fifo_full_flag_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  uint8_t reg[2];
  lsm6dso32_fifo_status2_t *fifo_status2 = (lsm6dso32_fifo_status2_t *)&reg[1];
  int32_t ret;

  /* read both FIFO_STATUS1 + FIFO_STATUS2 regs */
  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_STATUS1, (uint8_t *)reg, 2);
  if (ret == 0)
  {
    *val = fifo_status2->fifo_full_ia;
  }

  return ret;
}

/**
  * @brief  FIFO overrun status.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Read the values of  fifo_over_run_latched in
  *                reg FIFO_STATUS2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dso32_fifo_ovr_flag_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  uint8_t reg[2];
  lsm6dso32_fifo_status2_t *fifo_status2 = (lsm6dso32_fifo_status2_t *)&reg[1];
  int32_t ret;

  /* read both FIFO_STATUS1 + FIFO_STATUS2 regs */
  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_STATUS1, (uint8_t *)reg, 2);
  if (ret == 0)
  {
    *val = fifo_status2->fifo_ovr_ia;
  }

  return ret;
}

/**
  * @brief  FIFO watermark status.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Read the values of fifo_wtm_ia in reg FIFO_STATUS2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dso32_fifo_wtm_flag_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  uint8_t reg[2];
  lsm6dso32_fifo_status2_t *fifo_status2 = (lsm6dso32_fifo_status2_t *)&reg[1];
  int32_t ret;

  /* read both FIFO_STATUS1 + FIFO_STATUS2 regs */
  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_STATUS1, (uint8_t *)reg, 2);
  if (ret == 0)
  {
    *val = fifo_status2->fifo_wtm_ia;
  }

  return ret;
}

/**
  * @brief  Identifies the sensor in FIFO_DATA_OUT.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of tag_sensor in reg FIFO_DATA_OUT_TAG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fifo_sensor_tag_get(const stmdev_ctx_t *ctx,
                                      lsm6dso32_fifo_tag_t *val)
{
  lsm6dso32_fifo_data_out_tag_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FIFO_DATA_OUT_TAG,
                           (uint8_t *)&reg, 1);

  switch (reg.tag_sensor)
  {
    case LSM6DSO32_GYRO_NC_TAG:
      *val = LSM6DSO32_GYRO_NC_TAG;
      break;

    case LSM6DSO32_XL_NC_TAG:
      *val = LSM6DSO32_XL_NC_TAG;
      break;

    case LSM6DSO32_TEMPERATURE_TAG:
      *val = LSM6DSO32_TEMPERATURE_TAG;
      break;

    case LSM6DSO32_TIMESTAMP_TAG:
      *val = LSM6DSO32_TIMESTAMP_TAG;
      break;

    case LSM6DSO32_CFG_CHANGE_TAG:
      *val = LSM6DSO32_CFG_CHANGE_TAG;
      break;

    case LSM6DSO32_XL_NC_T_2_TAG:
      *val = LSM6DSO32_XL_NC_T_2_TAG;
      break;

    case LSM6DSO32_XL_NC_T_1_TAG:
      *val = LSM6DSO32_XL_NC_T_1_TAG;
      break;

    case LSM6DSO32_XL_2XC_TAG:
      *val = LSM6DSO32_XL_2XC_TAG;
      break;

    case LSM6DSO32_XL_3XC_TAG:
      *val = LSM6DSO32_XL_3XC_TAG;
      break;

    case LSM6DSO32_GYRO_NC_T_2_TAG:
      *val = LSM6DSO32_GYRO_NC_T_2_TAG;
      break;

    case LSM6DSO32_GYRO_NC_T_1_TAG:
      *val = LSM6DSO32_GYRO_NC_T_1_TAG;
      break;

    case LSM6DSO32_GYRO_2XC_TAG:
      *val = LSM6DSO32_GYRO_2XC_TAG;
      break;

    case LSM6DSO32_GYRO_3XC_TAG:
      *val = LSM6DSO32_GYRO_3XC_TAG;
      break;

    case LSM6DSO32_SENSORHUB_SLAVE0_TAG:
      *val = LSM6DSO32_SENSORHUB_SLAVE0_TAG;
      break;

    case LSM6DSO32_SENSORHUB_SLAVE1_TAG:
      *val = LSM6DSO32_SENSORHUB_SLAVE1_TAG;
      break;

    case LSM6DSO32_SENSORHUB_SLAVE2_TAG:
      *val = LSM6DSO32_SENSORHUB_SLAVE2_TAG;
      break;

    case LSM6DSO32_SENSORHUB_SLAVE3_TAG:
      *val = LSM6DSO32_SENSORHUB_SLAVE3_TAG;
      break;

    case LSM6DSO32_STEP_COUNTER_TAG:
      *val = LSM6DSO32_STEP_COUNTER_TAG;
      break;

    case LSM6DSO32_SENSORHUB_NACK_TAG:
      *val = LSM6DSO32_SENSORHUB_NACK_TAG;
      break;

    default:
      *val = LSM6DSO32_GYRO_NC_TAG;
      break;
  }

  return ret;
}

/**
  * @brief  :  Enable FIFO batching of pedometer embedded
  *            function values.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of gbias_fifo_en in
  *                  reg LSM6DSO32_EMB_FUNC_FIFO_CFG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fifo_pedo_batch_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_emb_func_fifo_cfg_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_FIFO_CFG,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    reg.pedo_fifo_en = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_EMB_FUNC_FIFO_CFG,
                              (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Enable FIFO batching of pedometer embedded function values.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of pedo_fifo_en in
  *                  reg LSM6DSO32_EMB_FUNC_FIFO_CFG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fifo_pedo_batch_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_emb_func_fifo_cfg_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_FIFO_CFG,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    *val = reg.pedo_fifo_en;
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief   Enable FIFO batching data of first slave.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of  batch_ext_sens_0_en in
  *                  reg SLV0_CONFIG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_batch_slave_0_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_slv0_config_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_SLV0_CONFIG, (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    reg.batch_ext_sens_0_en = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_SLV0_CONFIG, (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Enable FIFO batching data of first slave.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of  batch_ext_sens_0_en in
  *                  reg SLV0_CONFIG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_batch_slave_0_get(const stmdev_ctx_t *ctx,
                                       uint8_t *val)
{
  lsm6dso32_slv0_config_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_SLV0_CONFIG, (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    *val = reg.batch_ext_sens_0_en;
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Enable FIFO batching data of second slave.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of  batch_ext_sens_1_en in
  *                  reg SLV1_CONFIG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_batch_slave_1_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_slv1_config_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_SLV1_CONFIG, (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    reg.batch_ext_sens_1_en = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_SLV1_CONFIG, (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief   Enable FIFO batching data of second slave.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of  batch_ext_sens_1_en in
  *                  reg SLV1_CONFIG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_batch_slave_1_get(const stmdev_ctx_t *ctx,
                                       uint8_t *val)
{
  lsm6dso32_slv1_config_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_SLV1_CONFIG, (uint8_t *)&reg, 1);
    *val = reg.batch_ext_sens_1_en;
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Enable FIFO batching data of third slave.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of  batch_ext_sens_2_en in
  *                  reg SLV2_CONFIG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_batch_slave_2_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_slv2_config_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_SLV2_CONFIG, (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    reg.batch_ext_sens_2_en = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_SLV2_CONFIG, (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Enable FIFO batching data of third slave.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of  batch_ext_sens_2_en in
  *                  reg SLV2_CONFIG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_batch_slave_2_get(const stmdev_ctx_t *ctx,
                                       uint8_t *val)
{
  lsm6dso32_slv2_config_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_SLV2_CONFIG, (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    *val = reg.batch_ext_sens_2_en;
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief   Enable FIFO batching data of fourth slave.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of  batch_ext_sens_3_en
  *                  in reg SLV3_CONFIG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_batch_slave_3_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_slv3_config_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_SLV3_CONFIG, (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    reg.batch_ext_sens_3_en = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_SLV3_CONFIG, (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Enable FIFO batching data of fourth slave.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of  batch_ext_sens_3_en in
  *                  reg SLV3_CONFIG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_batch_slave_3_get(const stmdev_ctx_t *ctx,
                                       uint8_t *val)
{
  lsm6dso32_slv3_config_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_SLV3_CONFIG, (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    *val = reg.batch_ext_sens_3_en;
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  LSM6DSO32_DEN_functionality
  * @brief     This section groups all the functions concerning
  *            DEN functionality.
  * @{
  *
  */

/**
  * @brief  DEN functionality marking mode.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of den_mode in reg CTRL6_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_den_mode_set(const stmdev_ctx_t *ctx,
                               lsm6dso32_den_mode_t val)
{
  lsm6dso32_ctrl6_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL6_C, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.den_mode = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL6_C, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  DEN functionality marking mode.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of den_mode in reg CTRL6_C
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_den_mode_get(const stmdev_ctx_t *ctx,
                               lsm6dso32_den_mode_t *val)
{
  lsm6dso32_ctrl6_c_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL6_C, (uint8_t *)&reg, 1);

  switch (reg.den_mode)
  {
    case LSM6DSO32_DEN_DISABLE:
      *val = LSM6DSO32_DEN_DISABLE;
      break;

    case LSM6DSO32_LEVEL_FIFO:
      *val = LSM6DSO32_LEVEL_FIFO;
      break;

    case LSM6DSO32_LEVEL_LETCHED:
      *val = LSM6DSO32_LEVEL_LETCHED;
      break;

    case LSM6DSO32_LEVEL_TRIGGER:
      *val = LSM6DSO32_LEVEL_TRIGGER;
      break;

    case LSM6DSO32_EDGE_TRIGGER:
      *val = LSM6DSO32_EDGE_TRIGGER;
      break;

    default:
      *val = LSM6DSO32_DEN_DISABLE;
      break;
  }

  return ret;
}

/**
  * @brief  DEN active level configuration.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of den_lh in reg CTRL9_XL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_den_polarity_set(const stmdev_ctx_t *ctx,
                                   lsm6dso32_den_lh_t val)
{
  lsm6dso32_ctrl9_xl_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL9_XL, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.den_lh = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL9_XL, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  DEN active level configuration.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of den_lh in reg CTRL9_XL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_den_polarity_get(const stmdev_ctx_t *ctx,
                                   lsm6dso32_den_lh_t *val)
{
  lsm6dso32_ctrl9_xl_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL9_XL, (uint8_t *)&reg, 1);

  switch (reg.den_lh)
  {
    case LSM6DSO32_DEN_ACT_LOW:
      *val = LSM6DSO32_DEN_ACT_LOW;
      break;

    case LSM6DSO32_DEN_ACT_HIGH:
      *val = LSM6DSO32_DEN_ACT_HIGH;
      break;

    default:
      *val = LSM6DSO32_DEN_ACT_LOW;
      break;
  }

  return ret;
}

/**
  * @brief  DEN enable.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of den_xl_g in reg CTRL9_XL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_den_enable_set(const stmdev_ctx_t *ctx,
                                 lsm6dso32_den_xl_g_t val)
{
  lsm6dso32_ctrl9_xl_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL9_XL, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.den_xl_g = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL9_XL, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  DEN enable.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of den_xl_g in reg CTRL9_XL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_den_enable_get(const stmdev_ctx_t *ctx,
                                 lsm6dso32_den_xl_g_t *val)
{
  lsm6dso32_ctrl9_xl_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL9_XL, (uint8_t *)&reg, 1);

  switch (reg.den_xl_g)
  {
    case LSM6DSO32_STAMP_IN_GY_DATA:
      *val = LSM6DSO32_STAMP_IN_GY_DATA;
      break;

    case LSM6DSO32_STAMP_IN_XL_DATA:
      *val = LSM6DSO32_STAMP_IN_XL_DATA;
      break;

    case LSM6DSO32_STAMP_IN_GY_XL_DATA:
      *val = LSM6DSO32_STAMP_IN_GY_XL_DATA;
      break;

    default:
      *val = LSM6DSO32_STAMP_IN_GY_DATA;
      break;
  }

  return ret;
}

/**
  * @brief  DEN value stored in LSB of X-axis.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of den_z in reg CTRL9_XL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_den_mark_axis_x_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_ctrl9_xl_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL9_XL, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.den_z = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL9_XL, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  DEN value stored in LSB of X-axis.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of den_z in reg CTRL9_XL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_den_mark_axis_x_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_ctrl9_xl_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL9_XL, (uint8_t *)&reg, 1);
  *val = reg.den_z;

  return ret;
}

/**
  * @brief  DEN value stored in LSB of Y-axis.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of den_y in reg CTRL9_XL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_den_mark_axis_y_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_ctrl9_xl_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL9_XL, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.den_y = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL9_XL, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  DEN value stored in LSB of Y-axis.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of den_y in reg CTRL9_XL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_den_mark_axis_y_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_ctrl9_xl_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL9_XL, (uint8_t *)&reg, 1);
  *val = reg.den_y;

  return ret;
}

/**
  * @brief  DEN value stored in LSB of Z-axis.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of den_x in reg CTRL9_XL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_den_mark_axis_z_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_ctrl9_xl_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL9_XL, (uint8_t *)&reg, 1);

  if (ret == 0)
  {
    reg.den_x = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_CTRL9_XL, (uint8_t *)&reg, 1);
  }

  return ret;
}

/**
  * @brief  DEN value stored in LSB of Z-axis.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of den_x in reg CTRL9_XL
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_den_mark_axis_z_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_ctrl9_xl_t reg;
  int32_t ret;

  ret = lsm6dso32_read_reg(ctx, LSM6DSO32_CTRL9_XL, (uint8_t *)&reg, 1);
  *val = reg.den_x;

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  LSM6DSO32_Pedometer
  * @brief     This section groups all the functions that manage pedometer.
  * @{
  *
  */

/**
  * @brief  Enable pedometer algorithm.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      turn on and configure pedometer
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_pedo_sens_set(const stmdev_ctx_t *ctx,
                                lsm6dso32_pedo_md_t val)
{
  lsm6dso32_emb_func_en_a_t emb_func_en_a;
  lsm6dso32_emb_func_en_b_t emb_func_en_b;
  lsm6dso32_pedo_cmd_reg_t pedo_cmd_reg;
  int32_t ret;

  ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_PEDO_CMD_REG,
                                  (uint8_t *)&pedo_cmd_reg);

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_EN_A,
                             (uint8_t *)&emb_func_en_a, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_EN_B,
                             (uint8_t *)&emb_func_en_b, 1);
    emb_func_en_a.pedo_en = (uint8_t)val & 0x01U;
    emb_func_en_b.pedo_adv_en = ((uint8_t)val & 0x02U) >> 1;
    pedo_cmd_reg.fp_rejection_en = ((uint8_t)val & 0x10U) >> 4;
    pedo_cmd_reg.ad_det_en = ((uint8_t)val & 0x20U) >> 5;
  }

  if (ret == 0)
  {
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_EMB_FUNC_EN_A,
                              (uint8_t *)&emb_func_en_a, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_EMB_FUNC_EN_B,
                              (uint8_t *)&emb_func_en_b, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_PEDO_CMD_REG,
                                     (uint8_t *)&pedo_cmd_reg);
  }

  return ret;
}

/**
  * @brief  Enable pedometer algorithm.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      turn on and configure pedometer
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_pedo_sens_get(const stmdev_ctx_t *ctx,
                                lsm6dso32_pedo_md_t *val)
{
  lsm6dso32_emb_func_en_a_t emb_func_en_a;
  lsm6dso32_emb_func_en_b_t emb_func_en_b;
  lsm6dso32_pedo_cmd_reg_t pedo_cmd_reg;
  int32_t ret;

  ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_PEDO_CMD_REG,
                                  (uint8_t *)&pedo_cmd_reg);

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_EN_A,
                             (uint8_t *)&emb_func_en_a, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_EN_B,
                             (uint8_t *)&emb_func_en_b, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  switch ((pedo_cmd_reg.ad_det_en << 5) | (pedo_cmd_reg.fp_rejection_en
                                           << 4) |
          (emb_func_en_b.pedo_adv_en << 1) | emb_func_en_a.pedo_en)
  {
    case LSM6DSO32_PEDO_DISABLE:
      *val = LSM6DSO32_PEDO_DISABLE;
      break;

    case LSM6DSO32_PEDO_BASE_MODE:
      *val = LSM6DSO32_PEDO_BASE_MODE;
      break;

    case LSM6DSO32_PEDO_ADV_MODE:
      *val = LSM6DSO32_PEDO_ADV_MODE;
      break;

    case LSM6DSO32_FALSE_STEP_REJ:
      *val = LSM6DSO32_FALSE_STEP_REJ;
      break;

    case LSM6DSO32_FALSE_STEP_REJ_ADV_MODE:
      *val = LSM6DSO32_FALSE_STEP_REJ_ADV_MODE;
      break;

    default:
      *val = LSM6DSO32_PEDO_DISABLE;
      break;
  }

  return ret;
}

/**
  * @brief  Interrupt status bit for step detection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of is_step_det in reg EMB_FUNC_STATUS
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_pedo_step_detect_get(const stmdev_ctx_t *ctx,
                                       uint8_t *val)
{
  lsm6dso32_emb_func_status_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_STATUS,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    *val = reg.is_step_det;
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Pedometer debounce configuration register (r/w).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that contains data to write
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_pedo_debounce_steps_set(const stmdev_ctx_t *ctx,
                                          uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_PEDO_DEB_STEPS_CONF,
                                   buff);

  return ret;
}

/**
  * @brief  Pedometer debounce configuration register (r/w).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that stores data read
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_pedo_debounce_steps_get(const stmdev_ctx_t *ctx,
                                          uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_PEDO_DEB_STEPS_CONF,
                                  buff);

  return ret;
}

/**
  * @brief  Time period register for step detection on delta time (r/w).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that contains data to write
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_pedo_steps_period_set(const stmdev_ctx_t *ctx,
                                        uint16_t val)
{
  uint8_t buff[2];
  int32_t ret;

  buff[1] = (uint8_t)(val / 256U);
  buff[0] = (uint8_t)(val - (buff[1] * 256U));
  ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_PEDO_SC_DELTAT_L,
                                   &buff[0]);

  if (ret == 0)
  {
    ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_PEDO_SC_DELTAT_H,
                                     &buff[1]);
  }

  return ret;
}

/**
  * @brief   Time period register for step detection on delta time (r/w).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that stores data read
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_pedo_steps_period_get(const stmdev_ctx_t *ctx,
                                        uint16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_PEDO_SC_DELTAT_L,
                                  &buff[0]);

  if (ret == 0)
  {
    ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_PEDO_SC_DELTAT_H,
                                    &buff[1]);
    *val = buff[1];
    *val = (*val * 256U) +  buff[0];
  }

  return ret;
}

/**
  * @brief  Set when user wants to generate interrupt on count overflow
  *         event/every step.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of carry_count_en in reg PEDO_CMD_REG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_pedo_int_mode_set(const stmdev_ctx_t *ctx,
                                    lsm6dso32_carry_count_en_t val)
{
  lsm6dso32_pedo_cmd_reg_t reg;
  int32_t ret;

  ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_PEDO_CMD_REG,
                                  (uint8_t *)&reg);

  if (ret == 0)
  {
    reg.carry_count_en = (uint8_t)val;
    ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_PEDO_CMD_REG,
                                     (uint8_t *)&reg);
  }

  return ret;
}

/**
  * @brief  Set when user wants to generate interrupt on count overflow
  *         event/every step.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of carry_count_en in reg PEDO_CMD_REG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_pedo_int_mode_get(const stmdev_ctx_t *ctx,
                                    lsm6dso32_carry_count_en_t *val)
{
  lsm6dso32_pedo_cmd_reg_t reg;
  int32_t ret;

  ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_PEDO_CMD_REG,
                                  (uint8_t *)&reg);

  switch (reg.carry_count_en)
  {
    case LSM6DSO32_EVERY_STEP:
      *val = LSM6DSO32_EVERY_STEP;
      break;

    case LSM6DSO32_COUNT_OVERFLOW:
      *val = LSM6DSO32_COUNT_OVERFLOW;
      break;

    default:
      *val = LSM6DSO32_EVERY_STEP;
      break;
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  LSM6DSO32_significant_motion
  * @brief   This section groups all the functions that manage the
  *          significant motion detection.
  * @{
  *
  */

/**
  * @brief  Enable significant motion detection function.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of sign_motion_en in reg EMB_FUNC_EN_A
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_motion_sens_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_emb_func_en_a_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_EN_A,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    reg.sign_motion_en = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_EMB_FUNC_EN_A,
                              (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Enable significant motion detection function.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of sign_motion_en in reg EMB_FUNC_EN_A
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_motion_sens_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_emb_func_en_a_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_EN_A,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    *val = reg.sign_motion_en;
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief   Interrupt status bit for significant motion detection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of is_sigmot in reg EMB_FUNC_STATUS
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_motion_flag_data_ready_get(const stmdev_ctx_t *ctx,
                                             uint8_t *val)
{
  lsm6dso32_emb_func_status_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_STATUS,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    *val = reg.is_sigmot;
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  LSM6DSO32_tilt_detection
  * @brief     This section groups all the functions that manage the tilt
  *            event detection.
  * @{
  *
  */

/**
  * @brief  Enable tilt calculation.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of tilt_en in reg EMB_FUNC_EN_A
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_tilt_sens_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_emb_func_en_a_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_EN_A,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    reg.tilt_en = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_EMB_FUNC_EN_A,
                              (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Enable tilt calculation.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of tilt_en in reg EMB_FUNC_EN_A
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_tilt_sens_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_emb_func_en_a_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_EN_A,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    *val = reg.tilt_en;
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Interrupt status bit for tilt detection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of is_tilt in reg EMB_FUNC_STATUS
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_tilt_flag_data_ready_get(const stmdev_ctx_t *ctx,
                                           uint8_t *val)
{
  lsm6dso32_emb_func_status_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_STATUS,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    *val = reg.is_tilt;
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  LSM6DSO32_ magnetometer_sensor
  * @brief     This section groups all the functions that manage additional
  *            magnetometer sensor.
  * @{
  *
  */

/**
  * @brief  External magnetometer sensitivity value register.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that contains data to write
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_mag_sensitivity_set(const stmdev_ctx_t *ctx, uint16_t val)
{
  uint8_t buff[2];
  int32_t ret;

  buff[1] = (uint8_t)(val / 256U);
  buff[0] = (uint8_t)(val - (buff[1] * 256U));
  ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_MAG_SENSITIVITY_L,
                                   &buff[0]);

  if (ret == 0)
  {
    ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_MAG_SENSITIVITY_H,
                                     &buff[1]);
  }

  return ret;
}

/**
  * @brief  External magnetometer sensitivity value register.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that stores data read
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_mag_sensitivity_get(const stmdev_ctx_t *ctx,
                                      uint16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_MAG_SENSITIVITY_L,
                                  &buff[0]);

  if (ret == 0)
  {
    ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_MAG_SENSITIVITY_H,
                                    &buff[1]);
    *val = buff[1];
    *val = (*val * 256U) +  buff[0];
  }

  return ret;
}

/**
  * @brief  Offset for hard-iron compensation register (r/w).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that contains data to write
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_mag_offset_set(const stmdev_ctx_t *ctx, int16_t *val)
{
  uint8_t buff[6];
  int32_t ret;

  buff[1] = (uint8_t)((uint16_t)val[0] / 256U);
  buff[0] = (uint8_t)((uint16_t)val[0] - (buff[1] * 256U));
  buff[3] = (uint8_t)((uint16_t)val[1] / 256U);
  buff[2] = (uint8_t)((uint16_t)val[1] - (buff[3] * 256U));
  buff[5] = (uint8_t)((uint16_t)val[2] / 256U);
  buff[4] = (uint8_t)((uint16_t)val[2] - (buff[5] * 256U));
  ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_MAG_OFFX_L,
                                   &buff[0]);

  if (ret == 0)
  {
    ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_MAG_OFFX_H,
                                     &buff[1]);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_MAG_OFFY_L,
                                     &buff[2]);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_MAG_OFFY_H,
                                     &buff[3]);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_MAG_OFFZ_L,
                                     &buff[4]);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_MAG_OFFZ_H,
                                     &buff[5]);
  }

  return ret;
}

/**
  * @brief  Offset for hard-iron compensation register (r/w).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that stores data read
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_mag_offset_get(const stmdev_ctx_t *ctx, int16_t *val)
{
  uint8_t buff[6];
  int32_t ret;

  ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_MAG_OFFX_L,
                                  &buff[0]);

  if (ret == 0)
  {
    ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_MAG_OFFX_H,
                                    &buff[1]);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_MAG_OFFY_L,
                                    &buff[2]);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_MAG_OFFY_H,
                                    &buff[3]);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_MAG_OFFZ_L,
                                    &buff[4]);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_MAG_OFFZ_H,
                                    &buff[5]);
    val[0] = (int16_t)buff[1];
    val[0] = (val[0] * 256) + (int16_t)buff[0];
    val[1] = (int16_t)buff[3];
    val[1] = (val[1] * 256) + (int16_t)buff[2];
    val[2] = (int16_t)buff[5];
    val[2] = (val[2] * 256) + (int16_t)buff[4];
  }

  return ret;
}

/**
  * @brief  Soft-iron (3x3 symmetric) matrix correction
  *         register (r/w). The value is expressed as
  *         half-precision floating-point format:
  *         SEEEEEFFFFFFFFFF
  *         S: 1 sign bit;
  *         E: 5 exponent bits;
  *         F: 10 fraction bits).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that contains data to write
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_mag_soft_iron_set(const stmdev_ctx_t *ctx, int16_t *val)
{
  uint8_t buff[12];
  int32_t ret;

  uint8_t index;
  buff[1] = (uint8_t)((uint16_t)val[0] / 256U);
  buff[0] = (uint8_t)((uint16_t)val[0] - (buff[1] * 256U));
  buff[3] = (uint8_t)((uint16_t)val[1] / 256U);
  buff[2] = (uint8_t)((uint16_t)val[1] - (buff[3] * 256U));
  buff[5] = (uint8_t)((uint16_t)val[2] / 256U);
  buff[4] = (uint8_t)((uint16_t)val[2] - (buff[5] * 256U));
  buff[7] = (uint8_t)((uint16_t)val[3] / 256U);
  buff[6] = (uint8_t)((uint16_t)val[3] - (buff[7] * 256U));
  buff[9] = (uint8_t)((uint16_t)val[4] / 256U);
  buff[8] = (uint8_t)((uint16_t)val[4] - (buff[9] * 256U));
  buff[11] = (uint8_t)((uint16_t)val[5] / 256U);
  buff[10] = (uint8_t)((uint16_t)val[5] - (buff[11] * 256U));
  index = 0x00U;
  ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_MAG_SI_XX_L,
                                   &buff[index]);

  if (ret == 0)
  {
    index++;
    ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_MAG_SI_XX_H,
                                     &buff[index]);
  }

  if (ret == 0)
  {
    index++;
    ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_MAG_SI_XY_L,
                                     &buff[index]);
  }

  if (ret == 0)
  {
    index++;
    ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_MAG_SI_XY_H,
                                     &buff[index]);
  }

  if (ret == 0)
  {
    index++;
    ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_MAG_SI_XZ_L,
                                     &buff[index]);
  }

  if (ret == 0)
  {
    index++;
    ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_MAG_SI_XZ_H,
                                     &buff[index]);
  }

  if (ret == 0)
  {
    index++;
    ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_MAG_SI_YY_L,
                                     &buff[index]);
  }

  if (ret == 0)
  {
    index++;
    ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_MAG_SI_YY_H,
                                     &buff[index]);
  }

  if (ret == 0)
  {
    index++;
    ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_MAG_SI_YZ_L,
                                     &buff[index]);
  }

  if (ret == 0)
  {
    index++;
    ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_MAG_SI_YZ_H,
                                     &buff[index]);
  }

  if (ret == 0)
  {
    index++;
    ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_MAG_SI_ZZ_L,
                                     &buff[index]);
  }

  if (ret == 0)
  {
    index++;
    ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_MAG_SI_ZZ_H,
                                     &buff[index]);
  }

  return ret;
}

/**
  * @brief  Soft-iron (3x3 symmetric) matrix
  *         correction register (r/w).
  *         The value is expressed as half-precision
  *         floating-point format:
  *         SEEEEEFFFFFFFFFF
  *         S: 1 sign bit;
  *         E: 5 exponent bits;
  *         F: 10 fraction bits.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that stores data read
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_mag_soft_iron_get(const stmdev_ctx_t *ctx, int16_t *val)
{
  uint8_t buff[12];
  int32_t ret;

  uint8_t index;
  index = 0x00U;
  ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_MAG_SI_XX_L,
                                  &buff[index]);

  if (ret == 0)
  {
    index++;
    ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_MAG_SI_XX_H,
                                    &buff[index]);
  }

  if (ret == 0)
  {
    index++;
    ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_MAG_SI_XY_L,
                                    &buff[index]);
  }

  if (ret == 0)
  {
    index++;
    ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_MAG_SI_XY_H,
                                    &buff[index]);
  }

  if (ret == 0)
  {
    index++;
    ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_MAG_SI_XZ_L,
                                    &buff[index]);
  }

  if (ret == 0)
  {
    index++;
    ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_MAG_SI_XZ_H,
                                    &buff[index]);
  }

  if (ret == 0)
  {
    index++;
    ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_MAG_SI_YY_L,
                                    &buff[index]);
  }

  if (ret == 0)
  {
    index++;
    ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_MAG_SI_YY_H,
                                    &buff[index]);
  }

  if (ret == 0)
  {
    index++;
    ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_MAG_SI_YZ_L,
                                    &buff[index]);
  }

  if (ret == 0)
  {
    index++;
    ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_MAG_SI_YZ_H,
                                    &buff[index]);
  }

  if (ret == 0)
  {
    index++;
    ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_MAG_SI_ZZ_L,
                                    &buff[index]);
  }

  if (ret == 0)
  {
    index++;
    ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_MAG_SI_ZZ_H,
                                    &buff[index]);
  }

  val[0] = (int16_t)buff[1];
  val[0] = (val[0] * 256) + (int16_t)buff[0];
  val[1] = (int16_t)buff[3];
  val[1] = (val[1] * 256) + (int16_t)buff[2];
  val[2] = (int16_t)buff[5];
  val[2] = (val[2] * 256) + (int16_t)buff[4];
  val[3] = (int16_t)buff[7];
  val[3] = (val[3] * 256) + (int16_t)buff[6];
  val[4] = (int16_t)buff[9];
  val[4] = (val[4] * 256) + (int16_t)buff[8];
  val[5] = (int16_t)buff[11];
  val[5] = (val[5] * 256) + (int16_t)buff[10];

  return ret;
}

/**
  * @brief  Magnetometer Z-axis coordinates
  *         rotation (to be aligned to
  *         accelerometer/gyroscope axes
  *         orientation).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of mag_z_axis in reg MAG_CFG_A
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_mag_z_orient_set(const stmdev_ctx_t *ctx,
                                   lsm6dso32_mag_z_axis_t val)
{
  lsm6dso32_mag_cfg_a_t reg;
  int32_t ret;

  ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_MAG_CFG_A,
                                  (uint8_t *)&reg);

  if (ret == 0)
  {
    reg.mag_z_axis = (uint8_t) val;
    ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_MAG_CFG_A,
                                     (uint8_t *)&reg);
  }

  return ret;
}

/**
  * @brief  Magnetometer Z-axis coordinates
  *         rotation (to be aligned to
  *         accelerometer/gyroscope axes
  *         orientation).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of mag_z_axis in reg MAG_CFG_A
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_mag_z_orient_get(const stmdev_ctx_t *ctx,
                                   lsm6dso32_mag_z_axis_t *val)
{
  lsm6dso32_mag_cfg_a_t reg;
  int32_t ret;

  ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_MAG_CFG_A,
                                  (uint8_t *)&reg);

  switch (reg.mag_z_axis)
  {
    case LSM6DSO32_Z_EQ_Y:
      *val = LSM6DSO32_Z_EQ_Y;
      break;

    case LSM6DSO32_Z_EQ_MIN_Y:
      *val = LSM6DSO32_Z_EQ_MIN_Y;
      break;

    case LSM6DSO32_Z_EQ_X:
      *val = LSM6DSO32_Z_EQ_X;
      break;

    case LSM6DSO32_Z_EQ_MIN_X:
      *val = LSM6DSO32_Z_EQ_MIN_X;
      break;

    case LSM6DSO32_Z_EQ_MIN_Z:
      *val = LSM6DSO32_Z_EQ_MIN_Z;
      break;

    case LSM6DSO32_Z_EQ_Z:
      *val = LSM6DSO32_Z_EQ_Z;
      break;

    default:
      *val = LSM6DSO32_Z_EQ_Y;
      break;
  }

  return ret;
}

/**
  * @brief   Magnetometer Y-axis coordinates
  *          rotation (to be aligned to
  *          accelerometer/gyroscope axes
  *          orientation).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of mag_y_axis in reg MAG_CFG_A
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_mag_y_orient_set(const stmdev_ctx_t *ctx,
                                   lsm6dso32_mag_y_axis_t val)
{
  lsm6dso32_mag_cfg_a_t reg;
  int32_t ret;

  ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_MAG_CFG_A,
                                  (uint8_t *)&reg);

  if (ret == 0)
  {
    reg.mag_y_axis = (uint8_t)val;
    ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_MAG_CFG_A,
                                     (uint8_t *) &reg);
  }

  return ret;
}

/**
  * @brief  Magnetometer Y-axis coordinates
  *         rotation (to be aligned to
  *         accelerometer/gyroscope axes
  *         orientation).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of mag_y_axis in reg MAG_CFG_A
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_mag_y_orient_get(const stmdev_ctx_t *ctx,
                                   lsm6dso32_mag_y_axis_t *val)
{
  lsm6dso32_mag_cfg_a_t reg;
  int32_t ret;

  ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_MAG_CFG_A,
                                  (uint8_t *)&reg);

  switch (reg.mag_y_axis)
  {
    case LSM6DSO32_Y_EQ_Y:
      *val = LSM6DSO32_Y_EQ_Y;
      break;

    case LSM6DSO32_Y_EQ_MIN_Y:
      *val = LSM6DSO32_Y_EQ_MIN_Y;
      break;

    case LSM6DSO32_Y_EQ_X:
      *val = LSM6DSO32_Y_EQ_X;
      break;

    case LSM6DSO32_Y_EQ_MIN_X:
      *val = LSM6DSO32_Y_EQ_MIN_X;
      break;

    case LSM6DSO32_Y_EQ_MIN_Z:
      *val = LSM6DSO32_Y_EQ_MIN_Z;
      break;

    case LSM6DSO32_Y_EQ_Z:
      *val = LSM6DSO32_Y_EQ_Z;
      break;

    default:
      *val = LSM6DSO32_Y_EQ_Y;
      break;
  }

  return ret;
}

/**
  * @brief  Magnetometer X-axis coordinates
  *         rotation (to be aligned to
  *         accelerometer/gyroscope axes
  *         orientation).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of mag_x_axis in reg MAG_CFG_B
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_mag_x_orient_set(const stmdev_ctx_t *ctx,
                                   lsm6dso32_mag_x_axis_t val)
{
  lsm6dso32_mag_cfg_b_t reg;
  int32_t ret;

  ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_MAG_CFG_B,
                                  (uint8_t *)&reg);

  if (ret == 0)
  {
    reg.mag_x_axis = (uint8_t)val;
    ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_MAG_CFG_B,
                                     (uint8_t *)&reg);
  }

  return ret;
}

/**
  * @brief   Magnetometer X-axis coordinates
  *          rotation (to be aligned to
  *          accelerometer/gyroscope axes
  *          orientation).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of mag_x_axis in reg MAG_CFG_B
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_mag_x_orient_get(const stmdev_ctx_t *ctx,
                                   lsm6dso32_mag_x_axis_t *val)
{
  lsm6dso32_mag_cfg_b_t reg;
  int32_t ret;

  ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_MAG_CFG_B,
                                  (uint8_t *)&reg);

  switch (reg.mag_x_axis)
  {
    case LSM6DSO32_X_EQ_Y:
      *val = LSM6DSO32_X_EQ_Y;
      break;

    case LSM6DSO32_X_EQ_MIN_Y:
      *val = LSM6DSO32_X_EQ_MIN_Y;
      break;

    case LSM6DSO32_X_EQ_X:
      *val = LSM6DSO32_X_EQ_X;
      break;

    case LSM6DSO32_X_EQ_MIN_X:
      *val = LSM6DSO32_X_EQ_MIN_X;
      break;

    case LSM6DSO32_X_EQ_MIN_Z:
      *val = LSM6DSO32_X_EQ_MIN_Z;
      break;

    case LSM6DSO32_X_EQ_Z:
      *val = LSM6DSO32_X_EQ_Z;
      break;

    default:
      *val = LSM6DSO32_X_EQ_Y;
      break;
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  LSM6DSO32_finite_state_machine
  * @brief     This section groups all the functions that manage the
  *            state_machine.
  * @{
  *
  */

/**
  * @brief   Interrupt status bit for FSM long counter
  *          timeout interrupt event.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of is_fsm_lc in reg EMB_FUNC_STATUS
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_long_cnt_flag_data_ready_get(const stmdev_ctx_t *ctx,
                                               uint8_t *val)
{
  lsm6dso32_emb_func_status_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_STATUS,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    *val = reg.is_fsm_lc;
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Final State Machine global enable.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of fsm_en in reg EMB_FUNC_EN_B
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_emb_fsm_en_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  int32_t ret;

  lsm6dso32_emb_func_en_b_t reg;
  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_EN_B,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    reg.fsm_en = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_EMB_FUNC_EN_B,
                              (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Final State Machine global enable.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  uint8_t *: return the values of fsm_en in reg EMB_FUNC_EN_B
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_emb_fsm_en_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  int32_t ret;

  lsm6dso32_emb_func_en_b_t reg;
  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_EN_B,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    *val = reg.fsm_en;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_EMB_FUNC_EN_B,
                              (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Final State Machine enable.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      union of registers from FSM_ENABLE_A to FSM_ENABLE_B
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fsm_enable_set(const stmdev_ctx_t *ctx,
                                 lsm6dso32_emb_fsm_enable_t *val)
{
  int32_t ret;

  lsm6dso32_emb_func_en_b_t reg;
  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_FSM_ENABLE_A,
                              (uint8_t *)&val->fsm_enable_a, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_FSM_ENABLE_B,
                              (uint8_t *)&val->fsm_enable_b, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_EN_B,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    if ((val->fsm_enable_a.fsm1_en   |
         val->fsm_enable_a.fsm2_en  |
         val->fsm_enable_a.fsm3_en  |
         val->fsm_enable_a.fsm4_en  |
         val->fsm_enable_a.fsm5_en  |
         val->fsm_enable_a.fsm6_en  |
         val->fsm_enable_a.fsm7_en  |
         val->fsm_enable_a.fsm8_en  |
         val->fsm_enable_b.fsm9_en  |
         val->fsm_enable_b.fsm10_en  |
         val->fsm_enable_b.fsm11_en  |
         val->fsm_enable_b.fsm12_en  |
         val->fsm_enable_b.fsm13_en  |
         val->fsm_enable_b.fsm14_en  |
         val->fsm_enable_b.fsm15_en  |
         val->fsm_enable_b.fsm16_en)
        != PROPERTY_DISABLE)
    {
      reg.fsm_en = PROPERTY_ENABLE;
    }

    else
    {
      reg.fsm_en = PROPERTY_DISABLE;
    }

    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_EMB_FUNC_EN_B,
                              (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Final State Machine enable.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      union of registers from FSM_ENABLE_A to FSM_ENABLE_B
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fsm_enable_get(const stmdev_ctx_t *ctx,
                                 lsm6dso32_emb_fsm_enable_t *val)
{
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FSM_ENABLE_A, (uint8_t *) val,
                             2);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  FSM long counter status register. Long counter value is an
  *         unsigned integer value (16-bit format).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that contains data to write
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_long_cnt_set(const stmdev_ctx_t *ctx, uint16_t val)
{
  uint8_t buff[2];
  int32_t ret;

  buff[1] = (uint8_t)(val / 256U);
  buff[0] = (uint8_t)(val - (buff[1] * 256U));
  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_FSM_LONG_COUNTER_L, buff, 2);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  FSM long counter status register. Long counter value is an
  *         unsigned integer value (16-bit format).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that stores data read
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_long_cnt_get(const stmdev_ctx_t *ctx, uint16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FSM_LONG_COUNTER_L, buff, 2);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
    *val = buff[1];
    *val = (*val * 256U) +  buff[0];
  }

  return ret;
}

/**
  * @brief  Clear FSM long counter value.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of fsm_lc_clr in
  *                  reg FSM_LONG_COUNTER_CLEAR
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_long_clr_set(const stmdev_ctx_t *ctx,
                               lsm6dso32_fsm_lc_clr_t val)
{
  lsm6dso32_fsm_long_counter_clear_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FSM_LONG_COUNTER_CLEAR,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    reg. fsm_lc_clr = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_FSM_LONG_COUNTER_CLEAR,
                              (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Clear FSM long counter value.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of fsm_lc_clr in
  *                  reg FSM_LONG_COUNTER_CLEAR
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_long_clr_get(const stmdev_ctx_t *ctx,
                               lsm6dso32_fsm_lc_clr_t *val)
{
  lsm6dso32_fsm_long_counter_clear_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FSM_LONG_COUNTER_CLEAR,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    switch (reg.fsm_lc_clr)
    {
      case LSM6DSO32_LC_NORMAL:
        *val = LSM6DSO32_LC_NORMAL;
        break;

      case LSM6DSO32_LC_CLEAR:
        *val = LSM6DSO32_LC_CLEAR;
        break;

      case LSM6DSO32_LC_CLEAR_DONE:
        *val = LSM6DSO32_LC_CLEAR_DONE;
        break;

      default:
        *val = LSM6DSO32_LC_NORMAL;
        break;
    }
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  FSM output registers[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      struct of registers from FSM_OUTS1 to FSM_OUTS16
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fsm_out_get(const stmdev_ctx_t *ctx,
                              lsm6dso32_fsm_out_t *val)
{
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_FSM_OUTS1, (uint8_t *) &val,
                             16);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Finite State Machine ODR configuration.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of fsm_odr in reg EMB_FUNC_ODR_CFG_B
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fsm_data_rate_set(const stmdev_ctx_t *ctx,
                                    lsm6dso32_fsm_odr_t val)
{
  lsm6dso32_emb_func_odr_cfg_b_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_ODR_CFG_B,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    reg.not_used_01 = 3; /* set default values */
    reg.not_used_02 = 1; /* set default values */
    reg.fsm_odr = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_EMB_FUNC_ODR_CFG_B,
                              (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Finite State Machine ODR configuration.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of fsm_odr in reg EMB_FUNC_ODR_CFG_B
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fsm_data_rate_get(const stmdev_ctx_t *ctx,
                                    lsm6dso32_fsm_odr_t *val)
{
  lsm6dso32_emb_func_odr_cfg_b_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_ODR_CFG_B,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    switch (reg.fsm_odr)
    {
      case LSM6DSO32_ODR_FSM_12Hz5:
        *val = LSM6DSO32_ODR_FSM_12Hz5;
        break;

      case LSM6DSO32_ODR_FSM_26Hz:
        *val = LSM6DSO32_ODR_FSM_26Hz;
        break;

      case LSM6DSO32_ODR_FSM_52Hz:
        *val = LSM6DSO32_ODR_FSM_52Hz;
        break;

      case LSM6DSO32_ODR_FSM_104Hz:
        *val = LSM6DSO32_ODR_FSM_104Hz;
        break;

      default:
        *val = LSM6DSO32_ODR_FSM_12Hz5;
        break;
    }

    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  FSM initialization request.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of fsm_init in reg FSM_INIT
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fsm_init_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_emb_func_init_b_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_INIT_B,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    reg.fsm_init = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_EMB_FUNC_INIT_B,
                              (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  FSM initialization request.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of fsm_init in reg FSM_INIT
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fsm_init_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_emb_func_init_b_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_EMB_FUNC_INIT_B,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    *val = reg.fsm_init;
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  FSM long counter timeout register (r/w). The long counter
  *         timeout value is an unsigned integer value (16-bit format).
  *         When the long counter value reached this value,
  *         the FSM generates an interrupt.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that contains data to write
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_long_cnt_int_value_set(const stmdev_ctx_t *ctx,
                                         uint16_t val)
{
  uint8_t buff[2];
  int32_t ret;

  buff[1] = (uint8_t)(val / 256U);
  buff[0] = (uint8_t)(val - (buff[1] * 256U));
  ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_FSM_LC_TIMEOUT_L,
                                   &buff[0]);

  if (ret == 0)
  {
    ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_FSM_LC_TIMEOUT_H,
                                     &buff[1]);
  }

  return ret;
}

/**
  * @brief  FSM long counter timeout register (r/w). The long counter
  *         timeout value is an unsigned integer value (16-bit format).
  *         When the long counter value reached this value,
  *         the FSM generates an interrupt.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that stores data read
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_long_cnt_int_value_get(const stmdev_ctx_t *ctx,
                                         uint16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_FSM_LC_TIMEOUT_L,
                                  &buff[0]);

  if (ret == 0)
  {
    ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_FSM_LC_TIMEOUT_H,
                                    &buff[1]);
    *val = buff[1];
    *val = (*val * 256U) +  buff[0];
  }

  return ret;
}

/**
  * @brief  FSM number of programs register.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that contains data to write
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fsm_number_of_programs_set(const stmdev_ctx_t *ctx,
                                             uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_FSM_PROGRAMS, buff);

  return ret;
}

/**
  * @brief  FSM number of programs register.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that stores data read
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fsm_number_of_programs_get(const stmdev_ctx_t *ctx,
                                             uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_FSM_PROGRAMS, buff);

  return ret;
}

/**
  * @brief  FSM start address register (r/w).
  *         First available address is 0x033C.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that contains data to write
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fsm_start_address_set(const stmdev_ctx_t *ctx,
                                        uint16_t val)
{
  uint8_t buff[2];
  int32_t ret;

  buff[1] = (uint8_t)(val / 256U);
  buff[0] = (uint8_t)(val - (buff[1] * 256U));
  ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_FSM_START_ADD_L,
                                   &buff[0]);

  if (ret == 0)
  {
    ;
    ret = lsm6dso32_ln_pg_write_byte(ctx, LSM6DSO32_FSM_START_ADD_H,
                                     &buff[1]);
  }

  return ret;
}

/**
  * @brief  FSM start address register (r/w).
  *         First available address is 0x033C.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that stores data read
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_fsm_start_address_get(const stmdev_ctx_t *ctx,
                                        uint16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_FSM_START_ADD_L,
                                  &buff[0]);

  if (ret == 0)
  {
    ret = lsm6dso32_ln_pg_read_byte(ctx, LSM6DSO32_FSM_START_ADD_H,
                                    &buff[1]);
    *val = buff[1];
    *val = (*val * 256U) +  buff[0];
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  LSM6DSO32_Sensor_hub
  * @brief     This section groups all the functions that manage the
  *            sensor hub.
  * @{
  *
  */

/**
  * @brief  Sensor hub output registers.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      union of registers from SENSOR_HUB_1 to SENSOR_HUB_18
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_read_data_raw_get(const stmdev_ctx_t *ctx,
                                       lsm6dso32_emb_sh_read_t *val)
{
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_SENSOR_HUB_1,
                             (uint8_t *) val, 18U);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Number of external sensors to be read by the sensor hub.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of aux_sens_on in reg MASTER_CONFIG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_slave_connected_set(const stmdev_ctx_t *ctx,
                                         lsm6dso32_aux_sens_on_t val)
{
  lsm6dso32_master_config_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_MASTER_CONFIG,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    reg.aux_sens_on = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_MASTER_CONFIG,
                              (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Number of external sensors to be read by the sensor hub.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of aux_sens_on in reg MASTER_CONFIG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_slave_connected_get(const stmdev_ctx_t *ctx,
                                         lsm6dso32_aux_sens_on_t *val)
{
  lsm6dso32_master_config_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_MASTER_CONFIG,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    switch (reg.aux_sens_on)
    {
      case LSM6DSO32_SLV_0:
        *val = LSM6DSO32_SLV_0;
        break;

      case LSM6DSO32_SLV_0_1:
        *val = LSM6DSO32_SLV_0_1;
        break;

      case LSM6DSO32_SLV_0_1_2:
        *val = LSM6DSO32_SLV_0_1_2;
        break;

      case LSM6DSO32_SLV_0_1_2_3:
        *val = LSM6DSO32_SLV_0_1_2_3;
        break;

      default:
        *val = LSM6DSO32_SLV_0;
        break;
    }

    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Sensor hub I2C master enable.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of master_on in reg MASTER_CONFIG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_master_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_master_config_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_MASTER_CONFIG,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    reg.master_on = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_MASTER_CONFIG,
                              (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Sensor hub I2C master enable.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of master_on in reg MASTER_CONFIG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_master_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_master_config_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_MASTER_CONFIG,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    *val = reg.master_on;
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Master I2C pull-up enable.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of shub_pu_en in reg MASTER_CONFIG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_pin_mode_set(const stmdev_ctx_t *ctx,
                                  lsm6dso32_shub_pu_en_t val)
{
  lsm6dso32_master_config_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_MASTER_CONFIG,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    reg.shub_pu_en = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_MASTER_CONFIG,
                              (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Master I2C pull-up enable.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of shub_pu_en in reg MASTER_CONFIG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_pin_mode_get(const stmdev_ctx_t *ctx,
                                  lsm6dso32_shub_pu_en_t *val)
{
  lsm6dso32_master_config_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_MASTER_CONFIG,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    switch (reg.shub_pu_en)
    {
      case LSM6DSO32_EXT_PULL_UP:
        *val = LSM6DSO32_EXT_PULL_UP;
        break;

      case LSM6DSO32_INTERNAL_PULL_UP:
        *val = LSM6DSO32_INTERNAL_PULL_UP;
        break;

      default:
        *val = LSM6DSO32_EXT_PULL_UP;
        break;
    }

    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  I2C interface pass-through.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of pass_through_mode in
  *                  reg MASTER_CONFIG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_pass_through_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dso32_master_config_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_MASTER_CONFIG,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    reg.pass_through_mode = val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_MASTER_CONFIG,
                              (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  I2C interface pass-through.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of pass_through_mode in
  *                  reg MASTER_CONFIG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_pass_through_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_master_config_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_MASTER_CONFIG,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    *val = reg.pass_through_mode;
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Sensor hub trigger signal selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of start_config in reg MASTER_CONFIG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_syncro_mode_set(const stmdev_ctx_t *ctx,
                                     lsm6dso32_start_config_t val)
{
  lsm6dso32_master_config_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_MASTER_CONFIG,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    reg.start_config = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_MASTER_CONFIG,
                              (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Sensor hub trigger signal selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of start_config in reg MASTER_CONFIG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_syncro_mode_get(const stmdev_ctx_t *ctx,
                                     lsm6dso32_start_config_t *val)
{
  lsm6dso32_master_config_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_MASTER_CONFIG,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    switch (reg.start_config)
    {
      case LSM6DSO32_EXT_ON_INT2_PIN:
        *val = LSM6DSO32_EXT_ON_INT2_PIN;
        break;

      case LSM6DSO32_XL_GY_DRDY:
        *val = LSM6DSO32_XL_GY_DRDY;
        break;

      default:
        *val = LSM6DSO32_EXT_ON_INT2_PIN;
        break;
    }

    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Slave 0 write operation is performed only at the first
  *         sensor hub cycle.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of write_once in reg MASTER_CONFIG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_write_mode_set(const stmdev_ctx_t *ctx,
                                    lsm6dso32_write_once_t val)
{
  lsm6dso32_master_config_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_MASTER_CONFIG,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    reg.write_once = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_MASTER_CONFIG,
                              (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Slave 0 write operation is performed only at the first sensor
  *         hub cycle.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of write_once in reg MASTER_CONFIG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_write_mode_get(const stmdev_ctx_t *ctx,
                                    lsm6dso32_write_once_t *val)
{
  lsm6dso32_master_config_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_MASTER_CONFIG,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    switch (reg.write_once)
    {
      case LSM6DSO32_EACH_SH_CYCLE:
        *val = LSM6DSO32_EACH_SH_CYCLE;
        break;

      case LSM6DSO32_ONLY_FIRST_CYCLE:
        *val = LSM6DSO32_ONLY_FIRST_CYCLE;
        break;

      default:
        *val = LSM6DSO32_EACH_SH_CYCLE;
        break;
    }

    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Reset Master logic and output registers.[set]
  *
  * @param  ctx      read / write interface definitions
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_reset_set(const stmdev_ctx_t *ctx)
{
  lsm6dso32_master_config_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_MASTER_CONFIG,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    reg.rst_master_regs = PROPERTY_ENABLE;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_MASTER_CONFIG,
                              (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    reg.rst_master_regs = PROPERTY_DISABLE;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_MASTER_CONFIG,
                              (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Reset Master logic and output registers.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of rst_master_regs in reg MASTER_CONFIG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_reset_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dso32_master_config_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_MASTER_CONFIG,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    *val = reg.rst_master_regs;
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Rate at which the master communicates.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of shub_odr in reg slv1_CONFIG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_data_rate_set(const stmdev_ctx_t *ctx,
                                   lsm6dso32_shub_odr_t val)
{
  lsm6dso32_slv0_config_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_SLV0_CONFIG, (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    reg.shub_odr = (uint8_t)val;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_SLV0_CONFIG, (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Rate at which the master communicates.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of shub_odr in reg slv1_CONFIG
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_data_rate_get(const stmdev_ctx_t *ctx,
                                   lsm6dso32_shub_odr_t *val)
{
  lsm6dso32_slv0_config_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_SLV0_CONFIG, (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    switch (reg.shub_odr)
    {
      case LSM6DSO32_SH_ODR_104Hz:
        *val = LSM6DSO32_SH_ODR_104Hz;
        break;

      case LSM6DSO32_SH_ODR_52Hz:
        *val = LSM6DSO32_SH_ODR_52Hz;
        break;

      case LSM6DSO32_SH_ODR_26Hz:
        *val = LSM6DSO32_SH_ODR_26Hz;
        break;

      case LSM6DSO32_SH_ODR_13Hz:
        *val = LSM6DSO32_SH_ODR_13Hz;
        break;

      default:
        *val = LSM6DSO32_SH_ODR_104Hz;
        break;
    }

    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Configure slave 0 for perform a write.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      a structure that contain
  *                      - uint8_t slv1_add;    8 bit i2c device address
  *                      - uint8_t slv1_subadd; 8 bit register device address
  *                      - uint8_t slv1_data;   8 bit data to write
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_cfg_write(const stmdev_ctx_t *ctx,
                               lsm6dso32_sh_cfg_write_t *val)
{
  lsm6dso32_slv0_add_t reg;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    reg.slave0 = val->slv0_add;
    reg.rw_0 = 0;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_SLV0_ADD, (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_SLV0_SUBADD,
                              &(val->slv0_subadd), 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_DATAWRITE_SLV0,
                              &(val->slv0_data), 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Configure slave 0 for perform a read.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Structure that contain
  *                      - uint8_t slv1_add;    8 bit i2c device address
  *                      - uint8_t slv1_subadd; 8 bit register device address
  *                      - uint8_t slv1_len;    num of bit to read
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_slv0_cfg_read(const stmdev_ctx_t *ctx,
                                   lsm6dso32_sh_cfg_read_t *val)
{
  lsm6dso32_slv0_add_t slv0_add;
  lsm6dso32_slv0_config_t slv0_config;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    slv0_add.slave0 = val->slv_add;
    slv0_add.rw_0 = 1;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_SLV0_ADD,
                              (uint8_t *)&slv0_add, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_SLV0_SUBADD,
                              &(val->slv_subadd), 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_SLV0_CONFIG,
                             (uint8_t *)&slv0_config, 1);
  }

  if (ret == 0)
  {
    slv0_config.slave0_numop = val->slv_len;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_SLV0_CONFIG,
                              (uint8_t *)&slv0_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Configure slave 0 for perform a write/read.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Structure that contain
  *                      - uint8_t slv1_add;    8 bit i2c device address
  *                      - uint8_t slv1_subadd; 8 bit register device address
  *                      - uint8_t slv1_len;    num of bit to read
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_slv1_cfg_read(const stmdev_ctx_t *ctx,
                                   lsm6dso32_sh_cfg_read_t *val)
{
  lsm6dso32_slv1_add_t slv1_add;
  lsm6dso32_slv1_config_t slv1_config;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    slv1_add.slave1_add = val->slv_add;
    slv1_add.r_1 = 1;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_SLV1_ADD,
                              (uint8_t *)&slv1_add, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_SLV1_SUBADD,
                              &(val->slv_subadd), 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_SLV1_CONFIG,
                             (uint8_t *)&slv1_config, 1);
  }

  if (ret == 0)
  {
    slv1_config.slave1_numop = val->slv_len;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_SLV1_CONFIG,
                              (uint8_t *)&slv1_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Configure slave 0 for perform a write/read.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Structure that contain
  *                      - uint8_t slv2_add;    8 bit i2c device address
  *                      - uint8_t slv2_subadd; 8 bit register device address
  *                      - uint8_t slv2_len;    num of bit to read
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_slv2_cfg_read(const stmdev_ctx_t *ctx,
                                   lsm6dso32_sh_cfg_read_t *val)
{
  lsm6dso32_slv2_add_t slv2_add;
  lsm6dso32_slv2_config_t slv2_config;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    slv2_add.slave2_add = val->slv_add;
    slv2_add.r_2 = 1;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_SLV2_ADD,
                              (uint8_t *)&slv2_add, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_SLV2_SUBADD,
                              &(val->slv_subadd), 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_SLV2_CONFIG,
                             (uint8_t *)&slv2_config, 1);
  }

  if (ret == 0)
  {
    slv2_config.slave2_numop = val->slv_len;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_SLV2_CONFIG,
                              (uint8_t *)&slv2_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief Configure slave 0 for perform a write/read.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Structure that contain
  *                      - uint8_t slv3_add;    8 bit i2c device address
  *                      - uint8_t slv3_subadd; 8 bit register device address
  *                      - uint8_t slv3_len;    num of bit to read
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_slv3_cfg_read(const stmdev_ctx_t *ctx,
                                   lsm6dso32_sh_cfg_read_t *val)
{
  lsm6dso32_slv3_add_t slv3_add;
  lsm6dso32_slv3_config_t slv3_config;
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    slv3_add.slave3_add = val->slv_add;
    slv3_add.r_3 = 1;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_SLV3_ADD,
                              (uint8_t *)&slv3_add, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_SLV3_SUBADD,
                              &(val->slv_subadd), 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_SLV3_CONFIG,
                             (uint8_t *)&slv3_config, 1);
  }

  if (ret == 0)
  {
    slv3_config.slave3_numop = val->slv_len;
    ret = lsm6dso32_write_reg(ctx, LSM6DSO32_SLV3_CONFIG,
                              (uint8_t *)&slv3_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Sensor hub source register.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      union of registers from STATUS_MASTER to
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dso32_sh_status_get(const stmdev_ctx_t *ctx,
                                lsm6dso32_status_master_t *val)
{
  int32_t ret;

  ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dso32_read_reg(ctx, LSM6DSO32_STATUS_MASTER,
                             (uint8_t *) val, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dso32_mem_bank_set(ctx, LSM6DSO32_USER_BANK);
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @}
  *
  */
