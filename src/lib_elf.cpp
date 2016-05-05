#include "lib_elf.h"

LibElf::LibElf::LibElf()
{
    elf_identification = std::make_unique<ElfIdentification>(this);
    elf_header = std::make_unique<ElfHeader>(this);
    sections = std::make_unique<Sections>(this);
    segments = std::make_unique<Segments>(this);
}

LibElf::LibElf::~LibElf()
{
}

bool LibElf::LibElf::load(std::string filename)
{
    // Save filename
    this->filename = filename;
    
    // Try to open file
    ifs.open(filename, std::ifstream::binary);

    // Check if file has been opened
    if (!ifs.is_open())
        return false;

    // Clear previously loaded data
    this->clear();

    // Try to load ELF identification
    if (!elf_identification->load()) {
        ifs.close();
        return false;
    }

    // Try to load ELF header
    if (!elf_header->load()) {
        ifs.close();
        return false;
    }

    // Try to load Sections
    if (!sections->load()) {
        ifs.close();
        return false;
    }

    // Try to load Segments
    if (!segments->load()) {
        ifs.close();
        return false;
    }
    
    // Close the file
    ifs.close();

    // Everything went fine
    return true;
}

std::ifstream *LibElf::LibElf::get_ifstream()
{
    return &ifs;
}

std::ofstream *LibElf::LibElf::get_ofstream()
{
    return &ofs;
}

uint64_t LibElf::LibElf::get_filesize()
{
    std::ifstream ifs(filename, std::ifstream::ate | std::ifstream::binary);
    return ifs.tellg();
}

LibElf::ElfIdentification *LibElf::LibElf::get_elf_identification() const
{
    return elf_identification.get();
}


LibElf::ElfHeader *LibElf::LibElf::get_elf_header() const
{
    return elf_header.get();
}

LibElf::Sections *LibElf::LibElf::get_sections() const
{
    return sections.get();
}

LibElf::Segments *LibElf::LibElf::get_segments() const
{
    return segments.get();
}

bool LibElf::LibElf::save()
{
    // Try to open file
    ofs.open(filename,
        std::fstream::in | std::fstream::out | std::fstream::binary);
    
    // Check if file has been opened
    if (!ofs.is_open())
        return false;
    
    // Try to save ELF identification
    if (!elf_identification->save())
        return false;

    // Try to save ELF header
    if (!elf_header->save())
        return false;

    // Try to save Section Headers
    if (!sections->save())
        return false;
    
    // Close the file
    ofs.close();
    
    // Everything went fine
    return true;
}

bool LibElf::LibElf::save_elf_identification()
{
    // Try to open file
    ofs.open(filename,
        std::fstream::in | std::fstream::out | std::fstream::binary);

    // Check if file has been opened
    if (!ofs.is_open())
        return false;

    // Try to save ELF identification
    if (!elf_identification->save())
        return false;

    // Close the file
    ofs.close();

    // Everything went fine
    return true;
}

bool LibElf::LibElf::reload()
{
    // Load current file again
    if (!load(filename))
        return false;

    // Everything went fine
    return true;
}

void LibElf::LibElf::clear()
{
    this->get_elf_identification()->clear();
    this->get_elf_header()->clear();
    this->get_sections()->clear();
    this->get_segments()->clear();
}

