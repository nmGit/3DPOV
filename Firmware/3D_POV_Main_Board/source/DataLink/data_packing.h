#ifndef DATA_PACKING_H
#define DATA_PACKING_H

typedef struct
{
    char descriptor[4];
    uint8_t seq;
    uint8_t res;
    uint8_t value;
    uint8_t checksum;
}mtr_spd_packet_t;

mtr_spd_packet_t mtr_spd_packet;

#endif // DATA_PACKING_H
