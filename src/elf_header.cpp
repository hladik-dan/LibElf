#include "elf_header.h"
#include "elf_identification.h"
#include "lib_elf.h"
#include "helper.h"

LibElf::ElfHeader::ElfHeader(LibElf *lib_elf)
{
    this->lib_elf = lib_elf;
    this->elf_identification = lib_elf->get_elf_identification();
}

LibElf::ElfHeader::~ElfHeader()
{
}

bool LibElf::ElfHeader::load()
{
    // Try to read data from ELF header
    if (!read())
        return false;

    // Convert data to correct endianness
    if (Helper::endian() != elf_identification->get_data())
        convert();

    // Set flag
    ok = true;

    // Everything went fine
    return true;
}

bool LibElf::ElfHeader::save()
{
    // Try to write ELF header data
    if (!write())
        return false;
    
    // Everything went fine
    return true;
}

bool LibElf::ElfHeader::is_ok()
{
    return ok;
}

void LibElf::ElfHeader::clear()
{
    ok = false;
}

Elf_Half LibElf::ElfHeader::get_type() const
{
    return type;
}

Elf_Half LibElf::ElfHeader::get_machine() const
{
    return machine;
}

Elf_Word LibElf::ElfHeader::get_version() const
{
    return version;
}

Elf_Addr LibElf::ElfHeader::get_entry() const
{
    return entry;
}

Elf_Off LibElf::ElfHeader::get_phoff() const
{
    return phoff;
}

Elf_Off LibElf::ElfHeader::get_shoff() const
{
    return shoff;
}

Elf_Word LibElf::ElfHeader::get_flags() const
{
    return flags;
}

Elf_Half LibElf::ElfHeader::get_ehsize() const
{
    return ehsize;
}

Elf_Half LibElf::ElfHeader::get_phentsize() const
{
    return phentsize;
}

Elf_Half LibElf::ElfHeader::get_phnum() const
{
    return phnum;
}

Elf_Half LibElf::ElfHeader::get_shentsize() const
{
    return shentsize;
}

Elf_Half LibElf::ElfHeader::get_shnum() const
{
    return shnum;
}

Elf_Half LibElf::ElfHeader::get_shstrndx() const
{
    return shstrndx;
}

void LibElf::ElfHeader::set_type(Elf_Half value)
{
    type = value;
}

void LibElf::ElfHeader::set_machine(Elf_Half value)
{
    machine = value;
}

void LibElf::ElfHeader::set_version(Elf_Word value)
{
    version = value;
}

void LibElf::ElfHeader::set_entry(Elf_Addr value)
{
    entry = value;
}

void LibElf::ElfHeader::set_phoff(Elf_Off value)
{
    phoff = value;
}

void LibElf::ElfHeader::set_shoff(Elf_Off value)
{
    shoff = value;
}

void LibElf::ElfHeader::set_flags(Elf_Word value)
{
    flags = value;
}

void LibElf::ElfHeader::set_ehsize(Elf_Half value)
{
    ehsize = value;
}

void LibElf::ElfHeader::set_phentsize(Elf_Half value)
{
    phentsize = value;
}

void LibElf::ElfHeader::set_phnum(Elf_Half value)
{
    phnum = value;
}

void LibElf::ElfHeader::set_shentsize(Elf_Half value)
{
    shentsize = value;
}

void LibElf::ElfHeader::set_shnum(Elf_Half value)
{
    shnum = value;
}

void LibElf::ElfHeader::set_shstrndx(Elf_Half value)
{
    shstrndx = value;
}

bool LibElf::ElfHeader::check_type()
{
    if (get_type() == ET_NONE)
        return false;
    if (get_type_string() == "Unknown")
        return false;

    return true;
}

bool LibElf::ElfHeader::check_machine()
{
    if (get_machine() == EM_NONE)
        return false;

    return true;
}

bool LibElf::ElfHeader::check_version()
{
    return true;
}

bool LibElf::ElfHeader::check_entry()
{
    return true;
}

bool LibElf::ElfHeader::check_phoff()
{
    if (get_phoff() > lib_elf->get_filesize())
        return false;

    return true;
}

bool LibElf::ElfHeader::check_shoff()
{
    if (get_shoff() > lib_elf->get_filesize())
        return false;

    return true;
}

bool LibElf::ElfHeader::check_flags()
{
    return true;
}

bool LibElf::ElfHeader::check_ehsize()
{
    if (elf_identification->is_32_bit() && get_ehsize() != EHSIZE_32BIT)
        return false;
    if (elf_identification->is_64_bit() && get_ehsize() != EHSIZE_64BIT)
        return false;

    return true;
}

bool LibElf::ElfHeader::check_phentsize()
{
    if (get_phentsize() == 0 && get_phnum() != 0)
        return false;
    if (get_phentsize() != 0 && get_phnum() == 0)
        return false;

    return true;
}

bool LibElf::ElfHeader::check_phnum()
{
    if (get_phnum() == 0 && get_phentsize() != 0)
        return false;
    if (get_phnum() != 0 && get_phentsize() == 0)
        return false;

    return true;
}

bool LibElf::ElfHeader::check_shentsize()
{
    if (get_shentsize() == 0 && get_shnum() != 0)
        return false;
    if (get_shentsize() != 0 && get_shnum() == 0)
        return false;

    return true;
}

bool LibElf::ElfHeader::check_shnum()
{
    if (get_shnum() == 0 && get_shentsize() != 0)
        return false;
    if (get_shnum() != 0 && get_shentsize() == 0)
        return false;

    return true;
}

bool LibElf::ElfHeader::check_shstrndx()
{
    return true;
}

std::string LibElf::ElfHeader::get_type_string() const
{
    if (ET_LOOS <= get_type() && get_type() <= ET_HIOS)
        return "OS specific";
    if (ET_LOPROC <= get_type() && get_type() <= ET_HIPROC)
        return "Processor specific";
    if (e_type.find(get_type()) != e_type.end())
        return e_type.at(get_type());

    return "Unknown";
}

std::string LibElf::ElfHeader::get_machine_string() const
{
    if (e_machine.find(get_machine()) != e_machine.end())
        return e_machine.at(get_machine());

    return "Unknown";
}

std::string LibElf::ElfHeader::get_version_string() const
{
    return std::to_string(get_version());
}

std::string LibElf::ElfHeader::get_entry_string() const
{
    return std::to_string(get_entry());
}

std::string LibElf::ElfHeader::get_phoff_string() const
{
    return std::to_string(get_phoff());
}

std::string LibElf::ElfHeader::get_shoff_string() const
{
    return std::to_string(get_shoff());
}

std::string LibElf::ElfHeader::get_flags_string() const
{
    return std::to_string(get_flags());
}

std::string LibElf::ElfHeader::get_ehsize_string() const
{
    return std::to_string(get_ehsize());
}

std::string LibElf::ElfHeader::get_phentsize_string() const
{
    return std::to_string(get_phentsize());
}

std::string LibElf::ElfHeader::get_phnum_string() const
{
    return std::to_string(get_phnum());
}

std::string LibElf::ElfHeader::get_shentsize_string() const
{
    return std::to_string(get_shentsize());
}

std::string LibElf::ElfHeader::get_shnum_string() const
{
    return std::to_string(get_shnum());
}

std::string LibElf::ElfHeader::get_shstrndx_string() const
{
    return std::to_string(get_shstrndx());
}

bool LibElf::ElfHeader::read()
{
    // Check if class is set correctly
    if (!elf_identification->is_32_bit() && !elf_identification->is_64_bit())
        return false;
    // Try to read values for 32-bit architecture
    else if (elf_identification->is_32_bit() && !read_32_bit())
        return false;
    // Try to read values for 64-bit architecture
    else if (elf_identification->is_64_bit() && !read_64_bit())
        return false;

    // Everything went fine
    return true;
}

bool LibElf::ElfHeader::read_32_bit()
{
    // Get stream
    std::ifstream *ifs = lib_elf->get_ifstream();

    // Try to read data
    ifs->read(reinterpret_cast<char *>(&type), sizeof(Elf32_Half));
    ifs->read(reinterpret_cast<char *>(&machine), sizeof(Elf32_Half));
    ifs->read(reinterpret_cast<char *>(&version), sizeof(Elf32_Word));
    ifs->read(reinterpret_cast<char *>(&entry), sizeof(Elf32_Addr));
    ifs->read(reinterpret_cast<char *>(&phoff), sizeof(Elf32_Off));
    ifs->read(reinterpret_cast<char *>(&shoff), sizeof(Elf32_Off));
    ifs->read(reinterpret_cast<char *>(&flags), sizeof(Elf32_Word));
    ifs->read(reinterpret_cast<char *>(&ehsize), sizeof(Elf32_Half));
    ifs->read(reinterpret_cast<char *>(&phentsize), sizeof(Elf32_Half));
    ifs->read(reinterpret_cast<char *>(&phnum), sizeof(Elf32_Half));
    ifs->read(reinterpret_cast<char *>(&shentsize), sizeof(Elf32_Half));
    ifs->read(reinterpret_cast<char *>(&shnum), sizeof(Elf32_Half));
    ifs->read(reinterpret_cast<char *>(&shstrndx), sizeof(Elf32_Half));

    // Check if stream is good
    if (!ifs->good())
        return false;

    // Everything went fine
    return true;
}

bool LibElf::ElfHeader::read_64_bit()
{
    // Get stream
    std::ifstream *ifs = lib_elf->get_ifstream();

    // Try to read data
    ifs->read(reinterpret_cast<char *>(&type), sizeof(Elf64_Half));
    ifs->read(reinterpret_cast<char *>(&machine), sizeof(Elf64_Half));
    ifs->read(reinterpret_cast<char *>(&version), sizeof(Elf64_Word));
    ifs->read(reinterpret_cast<char *>(&entry), sizeof(Elf64_Addr));
    ifs->read(reinterpret_cast<char *>(&phoff), sizeof(Elf64_Off));
    ifs->read(reinterpret_cast<char *>(&shoff), sizeof(Elf64_Off));
    ifs->read(reinterpret_cast<char *>(&flags), sizeof(Elf64_Word));
    ifs->read(reinterpret_cast<char *>(&ehsize), sizeof(Elf64_Half));
    ifs->read(reinterpret_cast<char *>(&phentsize), sizeof(Elf64_Half));
    ifs->read(reinterpret_cast<char *>(&phnum), sizeof(Elf64_Half));
    ifs->read(reinterpret_cast<char *>(&shentsize), sizeof(Elf64_Half));
    ifs->read(reinterpret_cast<char *>(&shnum), sizeof(Elf64_Half));
    ifs->read(reinterpret_cast<char *>(&shstrndx), sizeof(Elf64_Half));

    // Check if stream is good
    if (!ifs->good())
        return false;

    // Everything went fine
    return true;
}

bool LibElf::ElfHeader::write()
{
    // Check if class is set correctly
    if (!elf_identification->is_32_bit() && !elf_identification->is_64_bit())
        return false;
    // Try to write values for 32-bit architecture
    else if (elf_identification->is_32_bit() && !write_32_bit())
        return false;
    // Try to write values for 64-bit architecture
    else if (elf_identification->is_64_bit() && !write_64_bit())
        return false;

    // Everything went fine
    return true;
}

bool LibElf::ElfHeader::write_32_bit()
{
    // Get stream
    std::ofstream *ofs = lib_elf->get_ofstream();

    // Try to write data
    ofs->write(reinterpret_cast<char *>(&type), sizeof(Elf32_Half));
    ofs->write(reinterpret_cast<char *>(&machine), sizeof(Elf32_Half));
    ofs->write(reinterpret_cast<char *>(&version), sizeof(Elf32_Word));
    ofs->write(reinterpret_cast<char *>(&entry), sizeof(Elf32_Addr));
    ofs->write(reinterpret_cast<char *>(&phoff), sizeof(Elf32_Off));
    ofs->write(reinterpret_cast<char *>(&shoff), sizeof(Elf32_Off));
    ofs->write(reinterpret_cast<char *>(&flags), sizeof(Elf32_Word));
    ofs->write(reinterpret_cast<char *>(&ehsize), sizeof(Elf32_Half));
    ofs->write(reinterpret_cast<char *>(&phentsize), sizeof(Elf32_Half));
    ofs->write(reinterpret_cast<char *>(&phnum), sizeof(Elf32_Half));
    ofs->write(reinterpret_cast<char *>(&shentsize), sizeof(Elf32_Half));
    ofs->write(reinterpret_cast<char *>(&shnum), sizeof(Elf32_Half));
    ofs->write(reinterpret_cast<char *>(&shstrndx), sizeof(Elf32_Half));

    // Check if stream is good
    if (!ofs->good())
        return false;

    // Everything went fine
    return true;
}

bool LibElf::ElfHeader::write_64_bit()
{
    // Get stream
    std::ofstream *ofs = lib_elf->get_ofstream();

    // Try to write data
    ofs->write(reinterpret_cast<char *>(&type), sizeof(Elf64_Half));
    ofs->write(reinterpret_cast<char *>(&machine), sizeof(Elf64_Half));
    ofs->write(reinterpret_cast<char *>(&version), sizeof(Elf64_Word));
    ofs->write(reinterpret_cast<char *>(&entry), sizeof(Elf64_Addr));
    ofs->write(reinterpret_cast<char *>(&phoff), sizeof(Elf64_Off));
    ofs->write(reinterpret_cast<char *>(&shoff), sizeof(Elf64_Off));
    ofs->write(reinterpret_cast<char *>(&flags), sizeof(Elf64_Word));
    ofs->write(reinterpret_cast<char *>(&ehsize), sizeof(Elf64_Half));
    ofs->write(reinterpret_cast<char *>(&phentsize), sizeof(Elf64_Half));
    ofs->write(reinterpret_cast<char *>(&phnum), sizeof(Elf64_Half));
    ofs->write(reinterpret_cast<char *>(&shentsize), sizeof(Elf64_Half));
    ofs->write(reinterpret_cast<char *>(&shnum), sizeof(Elf64_Half));
    ofs->write(reinterpret_cast<char *>(&shstrndx), sizeof(Elf64_Half));

    // Check if stream is good
    if (!ofs->good())
        return false;

    // Everything went fine
    return true;
}

void LibElf::ElfHeader::convert()
{
    if (elf_identification->is_32_bit())
        convert_32_bit();
    else if (elf_identification->is_64_bit())
        convert_64_bit();
}

void LibElf::ElfHeader::convert_32_bit()
{
    Helper::byteswap_16(reinterpret_cast<Elf32_Half *>(&type));
    Helper::byteswap_16(reinterpret_cast<Elf32_Half *>(&machine));
    Helper::byteswap_32(reinterpret_cast<Elf32_Word *>(&version));
    Helper::byteswap_32(reinterpret_cast<Elf32_Addr *>(&entry));
    Helper::byteswap_32(reinterpret_cast<Elf32_Off *>(&phoff));
    Helper::byteswap_32(reinterpret_cast<Elf32_Off *>(&shoff));
    Helper::byteswap_32(reinterpret_cast<Elf32_Word *>(&flags));
    Helper::byteswap_16(reinterpret_cast<Elf32_Half *>(&ehsize));
    Helper::byteswap_16(reinterpret_cast<Elf32_Half *>(&phentsize));
    Helper::byteswap_16(reinterpret_cast<Elf32_Half *>(&phnum));
    Helper::byteswap_16(reinterpret_cast<Elf32_Half *>(&shentsize));
    Helper::byteswap_16(reinterpret_cast<Elf32_Half *>(&shnum));
    Helper::byteswap_16(reinterpret_cast<Elf32_Half *>(&shstrndx));
}

void LibElf::ElfHeader::convert_64_bit()
{
    Helper::byteswap_16(&type);
    Helper::byteswap_16(&machine);
    Helper::byteswap_32(&version);
    Helper::byteswap_64(&entry);
    Helper::byteswap_64(&phoff);
    Helper::byteswap_64(&shoff);
    Helper::byteswap_32(&flags);
    Helper::byteswap_16(&ehsize);
    Helper::byteswap_16(&phentsize);
    Helper::byteswap_16(&phnum);
    Helper::byteswap_16(&shentsize);
    Helper::byteswap_16(&shnum);
    Helper::byteswap_16(&shstrndx);
}
