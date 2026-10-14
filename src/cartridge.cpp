#include "cartridge.hpp"
#include <fstream>

bool Cartridge::load(const std::string &path)
{
    std::ifstream file(path, std::ios::binary);
    if (!file) return false;

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    if (size < 0x150) return false;

    rom.resize(size);
    file.read(reinterpret_cast<char*>(rom.data()), size);
    if (!file) return false;
    
    auto result = parse_mbc(mbc[0x0147]);
    if (!parse_mbc) return false;
    


    uint8_t mbc_value = rom[0x0147];
    mbc_type = static_cast<MBC>(mbc_value);
    if (!check_mbc(mbc_type)) return false;
    enable_ram = false;

    file.close();
    return true;
}

bool check_mbc(MBC mbc)
{
    switch (mbc) {
        case MBC::rom_only:
        case MBC::MBC1:
        case MBC::MBC1_ram:
        case MBC::MBC1_ram_battery:
        case MBC::MBC2:
        case MBC::MBC2_battery:
        case MBC::MBC3_timer_battery:
        case MBC::MBC3_timer_ram_battery:
        case MBC::MBC3:
        case MBC::MBC3_ram:
        case MBC::MBC3_ram_battery:
        case MBC::MBC5:
        case MBC::MBC5_ram:
        case MBC::MBC5_ram_battery:
        case MBC::MBC5_rumble:
        case MBC::MBC5_rumble_ram:
        case MBC::MBC5_rumble_ram_battery:
            return true;

        default:
            return false;
    }
}
