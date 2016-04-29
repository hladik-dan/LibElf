#include "elf_identification.h"
#include "lib_elf.h"

LibElf::ElfIdentification::ElfIdentification(LibElf *lib_elf)
{
    this->lib_elf = lib_elf;
}

LibElf::ElfIdentification::~ElfIdentification()
{
}

bool LibElf::ElfIdentification::load()
{
    // Try to read data from ELF header
    if (!read())
        return false;

    // Set flag
    ok = true;

    // Everything went fine
    return true;
}

bool LibElf::ElfIdentification::save()
{
    // Try to write ELF header data
    if (!write())
        return false;

    // Everything went fine
    return true;
}

bool LibElf::ElfIdentification::is_ok()
{
    return ok;
}

void LibElf::ElfIdentification::clear()
{
    ok = false;
}

bool LibElf::ElfIdentification::is_32_bit()
{
    return (get_class() == ELFCLASS32);
}

bool LibElf::ElfIdentification::is_64_bit()
{
    return (get_class() == ELFCLASS64);
}

unsigned char LibElf::ElfIdentification::get_mag_0() const
{
    return ident[EI_MAG0];
}

unsigned char LibElf::ElfIdentification::get_mag_1() const
{
    return ident[EI_MAG1];
}

unsigned char LibElf::ElfIdentification::get_mag_2() const
{
    return ident[EI_MAG2];
}

unsigned char LibElf::ElfIdentification::get_mag_3() const
{
    return ident[EI_MAG3];
}

unsigned char LibElf::ElfIdentification::get_class() const
{
    return ident[EI_CLASS];
}

unsigned char LibElf::ElfIdentification::get_data() const
{
    return ident[EI_DATA];
}

unsigned char LibElf::ElfIdentification::get_version() const
{
    return ident[EI_VERSION];
}

unsigned char LibElf::ElfIdentification::get_osabi() const
{
    return ident[EI_OSABI];
}

unsigned char LibElf::ElfIdentification::get_abiversion() const
{
    return ident[EI_ABIVERSION];
}

void LibElf::ElfIdentification::set_mag_0(unsigned char value)
{
    ident[EI_MAG0] = value;
}

void LibElf::ElfIdentification::set_mag_1(unsigned char value)
{
    ident[EI_MAG1] = value;
}

void LibElf::ElfIdentification::set_mag_2(unsigned char value)
{
    ident[EI_MAG2] = value;
}

void LibElf::ElfIdentification::set_mag_3(unsigned char value)
{
    ident[EI_MAG3] = value;
}

void LibElf::ElfIdentification::set_class(unsigned char value)
{
    ident[EI_CLASS] = value;
}

void LibElf::ElfIdentification::set_data(unsigned char value)
{
    ident[EI_DATA] = value;
}

void LibElf::ElfIdentification::set_version(unsigned char value)
{
    ident[EI_VERSION] = value;
}

void LibElf::ElfIdentification::set_osabi(unsigned char value)
{
    ident[EI_OSABI] = value;
}

void LibElf::ElfIdentification::set_abiversion(unsigned char value)
{
    ident[EI_ABIVERSION] = value;
}

bool LibElf::ElfIdentification::check_mag_0()
{
    return (ident[EI_MAG0] == ELFMAG0);
}

bool LibElf::ElfIdentification::check_mag_1()
{
    return (ident[EI_MAG1] == ELFMAG1);
}

bool LibElf::ElfIdentification::check_mag_2()
{
    return (ident[EI_MAG2] == ELFMAG2);
}

bool LibElf::ElfIdentification::check_mag_3()
{
    return (ident[EI_MAG3] == ELFMAG3);
}

bool LibElf::ElfIdentification::check_class()
{
    if ((get_class() != ELFCLASS32) && (get_class() != ELFCLASS64))
        return false;

    return true;
}

bool LibElf::ElfIdentification::check_data()
{
    if ((get_data() != ELFDATA2LSB) && (get_data() != ELFDATA2MSB))
        return false;
    return true;
}

bool LibElf::ElfIdentification::check_version()
{
    if (get_version() != EV_CURRENT)
        return false;

    return true;
}

bool LibElf::ElfIdentification::check_osabi()
{
    return true;
}

bool LibElf::ElfIdentification::check_abiversion()
{
    return true;
}

std::string LibElf::ElfIdentification::get_mag_0_string() const
{
    return std::to_string(get_mag_0());
}

std::string LibElf::ElfIdentification::get_mag_1_string() const
{
    return std::string(1, get_mag_1());
}

std::string LibElf::ElfIdentification::get_mag_2_string() const
{
    return std::string(1, get_mag_2());
}

std::string LibElf::ElfIdentification::get_mag_3_string() const
{
    return std::string(1, get_mag_3());
}

std::string LibElf::ElfIdentification::get_class_string() const
{
    if (ei_class.find(get_class()) != ei_class.end())
        return ei_class.at(get_class());

    return "Unknown";
}

std::string LibElf::ElfIdentification::get_data_string() const
{
    if (ei_data.find(get_data()) != ei_data.end())
        return ei_data.at(get_data());

    return "Unknown";
}

std::string LibElf::ElfIdentification::get_version_string() const
{
    if (ei_version.find(get_version()) != ei_version.end())
        return ei_version.at(get_version());

    return "Unknown";
}

std::string LibElf::ElfIdentification::get_osabi_string() const
{
    if (ei_osabi.find(get_osabi()) != ei_osabi.end())
        return ei_osabi.at(get_osabi());

    return "Unknown";
}

std::string LibElf::ElfIdentification::get_abiversion_string() const
{
    return std::to_string(get_abiversion());
}

bool LibElf::ElfIdentification::read()
{
    // Get stream
    std::ifstream *ifs = lib_elf->get_ifstream();

    // Try to read data
    ifs->read(reinterpret_cast<char *>(ident), EI_NIDENT);

    // Check if stream is good
    if (!ifs->good())
        return false;

    // Everything went fine
    return true;
}

bool LibElf::ElfIdentification::write()
{
    // Get stream
    std::ofstream *ofs = lib_elf->get_ofstream();

    // Try to write data
    ofs->write(reinterpret_cast<char *>(&ident), EI_NIDENT);

    // Check if stream is good
    if (!ofs->good())
        return false;

    // Everything went fine
    return true;
}
