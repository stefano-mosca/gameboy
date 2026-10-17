#include "cartridge.hpp"
#include <fstream>

bool check_mbc(MBC mbc);
int32_t convert_ram(uint8_t ram_size);

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
    
    uint8_t mbc_value = rom[0x0147];
    mbc_type = static_cast<MBC>(mbc_value);
    if (!check_mbc(mbc_type)) return false;

    int32_t ram_size = convert_ram(rom[0x149]);
    if (ram_size == -1) return false;
    if (ram_size != 0) {
        external_ram.resize(ram_size);
    }

    file.close();
    return true;
}

// Promemoria personale: ricordarsi di aggiornare gli switch in caso facessi piu di un MBC dopo il 5

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

int32_t convert_ram(uint8_t ram_address)
{
    switch (ram_address) {
        case 0x00:
            return 0;
        case 0x02:
            return 8 * 1024;
        case 0x03:
            return 32 * 1024;
        case 0x04:
            return 128 * 1024;
        case 0x05:
            return 64 * 1024;
        default:
            return -1;
    }
}
