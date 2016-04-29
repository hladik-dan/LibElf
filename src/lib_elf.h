#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include "elf_identification.h"
#include "elf_header.h"
#include "sections.h"
#include "segments.h"

namespace LibElf
{
    class LibElf
    {
        public:
            LibElf();
            ~LibElf();

            bool load(std::string filename);
            bool save();
            bool save_elf_identification();
            bool reload();
            void clear();

            std::ifstream *get_ifstream();
            std::ofstream *get_ofstream();
            uint64_t get_filesize();
            ElfIdentification *get_elf_identification() const;
            ElfHeader *get_elf_header() const;
            Sections *get_sections() const;
            Segments *get_segments() const;

        private:
            std::string filename;
            std::ifstream ifs;
            std::ofstream ofs;

            std::unique_ptr<ElfIdentification> elf_identification;
            std::unique_ptr<ElfHeader> elf_header;
            std::unique_ptr<Sections> sections;
            std::unique_ptr<Segments> segments;
    };
}
