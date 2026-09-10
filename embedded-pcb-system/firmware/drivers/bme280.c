#include "bme280.h"

static uint8_t bme280_read_8(i2c_handle_t *hi2c, uint8_t addr, uint8_t reg, uint8_t *val) {
    return i2c_driver_read_reg(hi2c, reg, val);
}

static uint8_t bme280_read_16(i2c_handle_t *hi2c, uint8_t addr, uint8_t reg, uint16_t *val) {
    uint8_t lsb, msb;
    uint8_t ret;
    ret = i2c_driver_read_reg(hi2c, reg, &lsb);
    if (ret != I2C_OK) return ret;
    ret = i2c_driver_read_reg(hi2c, reg + 1, &msb);
    if (ret != I2C_OK) return ret;
    *val = (uint16_t)(msb << 8) | lsb;
    return I2C_OK;
}

static uint8_t bme280_read_24(i2c_handle_t *hi2c, uint8_t addr, uint8_t reg, uint32_t *val) {
    uint8_t buf[3];
    uint8_t ret;
    ret = i2c_driver_read_burst(hi2c, reg, buf, 3);
    if (ret != I2C_OK) return ret;
    *val = (uint32_t)(buf[2] << 16) | (uint32_t)(buf[1] << 8) | buf[0];
    return I2C_OK;
}

static uint8_t bme280_write_8(i2c_handle_t *hi2c, uint8_t addr, uint8_t reg, uint8_t val) {
    return i2c_driver_write_reg(hi2c, reg, val);
}

uint8_t bme280_init(bme280_handle_t *hbme, i2c_handle_t *hi2c, uint8_t addr) {
    hbme->hi2c = hi2c;
    hbme->dev_addr = addr;
    hbme->t_fine = 0;
    uint8_t ret;

    ret = bme280_read_id(hbme, &hbme->dig_T1);
    if (ret != I2C_OK || (uint8_t)hbme->dig_T1 != BME280_CHIP_ID) {
        return 1;
    }

    ret = bme280_write_8(hi2c, addr, BME280_REG_RESET, BME280_RESET);
    if (ret != I2C_OK) return ret;

    hal_delay_ms(100);

    uint16_t dig_T1_u;
    ret = bme280_read_16(hi2c, addr, 0x88, &dig_T1_u);
    hbme->dig_T1 = (int32_t)dig_T1_u;
    if (ret != I2C_OK) return ret;

    int16_t dig_T2_s;
    ret = bme280_read_16(hi2c, addr, 0x8A, (uint16_t *)&dig_T2_s);
    hbme->dig_T2 = (int32_t)dig_T2_s;
    if (ret != I2C_OK) return ret;

    int16_t dig_T3_s;
    ret = bme280_read_16(hi2c, addr, 0x8C, (uint16_t *)&dig_T3_s);
    hbme->dig_T3 = (int32_t)dig_T3_s;
    if (ret != I2C_OK) return ret;

    uint16_t dig_P1_u;
    ret = bme280_read_16(hi2c, addr, 0x8E, &dig_P1_u);
    hbme->dig_P1 = (int32_t)dig_P1_u;
    if (ret != I2C_OK) return ret;

    int16_t dig_P2_s;
    ret = bme280_read_16(hi2c, addr, 0x90, (uint16_t *)&dig_P2_s);
    hbme->dig_P2 = (int32_t)dig_P2_s;
    if (ret != I2C_OK) return ret;

    int16_t dig_P3_s;
    ret = bme280_read_16(hi2c, addr, 0x92, (uint16_t *)&dig_P3_s);
    hbme->dig_P3 = (int32_t)dig_P3_s;
    if (ret != I2C_OK) return ret;

    int16_t dig_P4_s;
    ret = bme280_read_16(hi2c, addr, 0x94, (uint16_t *)&dig_P4_s);
    hbme->dig_P4 = (int32_t)dig_P4_s;
    if (ret != I2C_OK) return ret;

    int16_t dig_P5_s;
    ret = bme280_read_16(hi2c, addr, 0x96, (uint16_t *)&dig_P5_s);
    hbme->dig_P5 = (int32_t)dig_P5_s;
    if (ret != I2C_OK) return ret;

    int16_t dig_P6_s;
    ret = bme280_read_16(hi2c, addr, 0x98, (uint16_t *)&dig_P6_s);
    hbme->dig_P6 = (int32_t)dig_P6_s;
    if (ret != I2C_OK) return ret;

    int16_t dig_P7_s;
    ret = bme280_read_16(hi2c, addr, 0x9A, (uint16_t *)&dig_P7_s);
    hbme->dig_P7 = (int32_t)dig_P7_s;
    if (ret != I2C_OK) return ret;

    int16_t dig_P8_s;
    ret = bme280_read_16(hi2c, addr, 0x9C, (uint16_t *)&dig_P8_s);
    hbme->dig_P8 = (int32_t)dig_P8_s;
    if (ret != I2C_OK) return ret;

    int16_t dig_P9_s;
    ret = bme280_read_16(hi2c, addr, 0x9E, (uint16_t *)&dig_P9_s);
    hbme->dig_P9 = (int32_t)dig_P9_s;
    if (ret != I2C_OK) return ret;

    uint8_t dig_H1_u;
    ret = bme280_read_8(hi2c, addr, 0xA1, &dig_H1_u);
    hbme->dig_H1 = (int32_t)dig_H1_u;
    if (ret != I2C_OK) return ret;

    int16_t dig_H2_s;
    ret = bme280_read_16(hi2c, addr, 0xE1, (uint16_t *)&dig_H2_s);
    hbme->dig_H2 = (int32_t)dig_H2_s;
    if (ret != I2C_OK) return ret;

    uint8_t dig_H3_u;
    ret = bme280_read_8(hi2c, addr, 0xE3, &dig_H3_u);
    hbme->dig_H3 = (int32_t)dig_H3_u;
    if (ret != I2C_OK) return ret;

    uint8_t dig_H4_msb, dig_H4_lsb;
    ret = bme280_read_8(hi2c, addr, 0xE4, &dig_H4_msb);
    if (ret != I2C_OK) return ret;
    ret = bme280_read_8(hi2c, addr, 0xE5, &dig_H4_lsb);
    hbme->dig_H4 = (int32_t)((dig_H4_msb << 4) | (dig_H4_lsb & 0x0F));
    if (ret != I2C_OK) return ret;

    uint8_t dig_H5_msb, dig_H5_lsb;
    ret = bme280_read_8(hi2c, addr, 0xE5, &dig_H5_lsb);
    if (ret != I2C_OK) return ret;
    ret = bme280_read_8(hi2c, addr, 0xE6, &dig_H5_msb);
    hbme->dig_H5 = (int32_t)((dig_H5_msb << 4) | ((dig_H5_lsb >> 4) & 0x0F));
    if (ret != I2C_OK) return ret;

    uint8_t dig_H6_u;
    ret = bme280_read_8(hi2c, addr, 0xE7, &dig_H6_u);
    hbme->dig_H6 = (int32_t)dig_H6_u;
    if (ret != I2C_OK) return ret;

    return I2C_OK;
}

uint8_t bme280_read_id(bme280_handle_t *hbme, uint8_t *id) {
    return i2c_driver_read_reg(hbme->hi2c, BME280_REG_ID, id);
}

uint8_t bme280_configure(bme280_handle_t *hbme, uint8_t osrs_t, uint8_t osrs_p, uint8_t osrs_h, uint8_t mode) {
    uint8_t ret;
    uint8_t ctrl_hum = osrs_h & 0x07;
    ret = i2c_driver_write_reg(hbme->hi2c, BME280_REG_CTRL_HUM, ctrl_hum);
    if (ret != I2C_OK) return ret;

    uint8_t ctrl_meas = ((osrs_t & 0x07) << 5) | ((osrs_p & 0x07) << 2) | (mode & 0x03);
    ret = i2c_driver_write_reg(hbme->hi2c, BME280_REG_CTRL_MEAS, ctrl_meas);
    if (ret != I2C_OK) return ret;

    uint8_t config = (0x01 << 2); // Standby 500ms
    ret = i2c_driver_write_reg(hbme->hi2c, BME280_REG_CONFIG, config);
    return ret;
}

uint8_t bme280_read_raw(bme280_handle_t *hbme, bme280_data_t *data) {
    uint8_t buf[8];
    uint8_t ret;
    ret = i2c_driver_read_burst(hbme->hi2c, BME280_REG_PRESS_MSB, buf, 8);
    if (ret != I2C_OK) return ret;

    uint32_t press_raw = ((uint32_t)buf[0] << 12) | ((uint32_t)buf[1] << 4) | ((uint32_t)buf[2] >> 4);
    uint32_t temp_raw = ((uint32_t)buf[3] << 12) | ((uint32_t)buf[4] << 4) | ((uint32_t)buf[5] >> 4);
    uint16_t hum_raw = ((uint16_t)buf[6] << 8) | buf[7];

    data->pressure = press_raw;
    data->temperature = (int32_t)temp_raw;
    data->humidity = hum_raw;

    return I2C_OK;
}

uint8_t bme280_compensate(bme280_handle_t *hbme, bme280_data_t *raw, bme280_data_t *comp) {
    int32_t var1, var2;

    var1 = ((((raw->temperature >> 3) - (hbme->dig_T1 << 1))) * ((int32_t)hbme->dig_T2)) >> 11;
    var2 = (((((raw->temperature >> 4) - ((int32_t)hbme->dig_T1)) *
             ((raw->temperature >> 4) - ((int32_t)hbme->dig_T1))) >> 12) *
            ((int32_t)hbme->dig_T3)) >> 14;
    hbme->t_fine = var1 + var2;
    comp->temperature = (hbme->t_fine * 5 + 128) >> 8;

    var1 = ((hbme->t_fine) >> 1) - 64000;
    var2 = (((var1 >> 2) * (var1 >> 2)) >> 11) * ((int32_t)hbme->dig_P6);
    var2 = var2 + ((var1 * ((int32_t)hbme->dig_P5)) << 1);
    var2 = (var2 >> 2) + (((int32_t)hbme->dig_P4) << 16);
    var1 = (((hbme->dig_P3 * (((var1 >> 2) * (var1 >> 2)) >> 13)) >> 3) +
            ((((int32_t)hbme->dig_P2) * var1) >> 1)) >> 18;
    var1 = (((32768 + var1) * ((int32_t)hbme->dig_P1)) >> 15);
    if (var1 == 0) {
        comp->pressure = 0;
    } else {
        comp->pressure = (((uint32_t)(1048576 - raw->pressure) - (var2 >> 12))) * 3125;
        if (comp->pressure < 0x80000000) {
            comp->pressure = (comp->pressure << 1) / ((uint32_t)var1);
        } else {
            comp->pressure = (comp->pressure / (uint32_t)var1) * 2;
        }
        var1 = (((int32_t)hbme->dig_P9) * ((int32_t)(((comp->pressure >> 3) * (comp->pressure >> 3)) >> 13))) >> 12;
        var2 = (((int32_t)(comp->pressure >> 2)) * ((int32_t)hbme->dig_P8)) >> 13;
        comp->pressure = (uint32_t)((int32_t)comp->pressure + ((var1 + var2 + hbme->dig_P7) >> 4));
    }

    int32_t h = (hbme->t_fine - ((int32_t)76800));
    if (h == 0) {
        comp->humidity = 0;
    } else {
        var1 = (raw->humidity - (((int32_t)hbme->dig_H4) << 20 -
                (((int32_t)hbme->dig_H5) * h) >> 13)) *
                (((((int32_t)hbme->dig_H6) * h) >> 11) +
                (((int32_t)32768))) >> 10;
        var2 = (((((int32_t)hbme->dig_H2) * (((((h * ((int32_t)hbme->dig_H3)) >> 11)) +
                ((int32_t)32768))) >> 10) + ((int32_t)2097152)) *
                ((int32_t)hbme->dig_H1) + 8192) >> 14;
        h = (var1 * var2) >> 15;
        var1 = (((h - ((int32_t)16384))) * ((int32_t)15700)) >> 10;
        var2 = (((h - ((int32_t)16384))) * ((int32_t)28672)) >> 10;
        h = (var1 + var2) >> 15;
        h += (32768 - h) / 32768;
        comp->humidity = (uint32_t)(h * 100 >> 7);
    }

    return I2C_OK;
}

uint8_t bme280_read_temperature(bme280_handle_t *hbme, float *temp_c) {
    bme280_data_t raw, comp;
    uint8_t ret;
    ret = bme280_read_raw(hbme, &raw);
    if (ret != I2C_OK) return ret;
    ret = bme280_compensate(hbme, &raw, &comp);
    if (ret != I2C_OK) return ret;
    *temp_c = (float)comp.temperature / 100.0f;
    return I2C_OK;
}

uint8_t bme280_read_pressure(bme280_handle_t *hbme, float *pres_pa) {
    bme280_data_t raw, comp;
    uint8_t ret;
    ret = bme280_read_raw(hbme, &raw);
    if (ret != I2C_OK) return ret;
    ret = bme280_compensate(hbme, &raw, &comp);
    if (ret != I2C_OK) return ret;
    *pres_pa = (float)comp.pressure;
    return I2C_OK;
}

uint8_t bme280_read_humidity(bme280_handle_t *hbme, float *hum_pct) {
    bme280_data_t raw, comp;
    uint8_t ret;
    ret = bme280_read_raw(hbme, &raw);
    if (ret != I2C_OK) return ret;
    ret = bme280_compensate(hbme, &raw, &comp);
    if (ret != I2C_OK) return ret;
    *hum_pct = (float)comp.humidity / 1024.0f;
    return I2C_OK;
}
