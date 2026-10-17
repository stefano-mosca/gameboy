#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <vector>
#include <cstdint>
#include <string>

enum class MBC {
    rom_only = 0x00,
    MBC1 = 0x01,
    MBC1_ram = 0x02,
    MBC1_ram_battery = 0x03,
    MBC2 = 0x05,
    MBC2_battery = 0x06,
    MBC3_timer_battery = 0x0F,
    MBC3_timer_ram_battery = 0x10,
    MBC3 = 0x11,
    MBC3_ram = 0x12,
    MBC3_ram_battery = 0x13,
    MBC5 = 0x19,
    MBC5_ram = 0x1A,
    MBC5_ram_battery = 0x1B,
    MBC5_rumble = 0x1C,
    MBC5_rumble_ram = 0x1D,
    MBC5_rumble_ram_battery = 0x1E
};

struct Cartridge {
    std::vector<uint8_t> rom;
    std::vector<uint8_t> external_ram;
    MBC mbc_type;
    bool ram_enable;
    uint8_t rom_bank_number;
    uint8_t ram_bank_number;
    bool select_banking_mode;
    bool has_battery;
    bool load(const std::string &path);
};

#endif
