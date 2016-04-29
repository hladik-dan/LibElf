#pragma once

#include "lib_data.h"

namespace LibElf
{
    class LibElf;
    class ElfIdentification;

    class ElfHeader
    {
        public:
            ElfHeader(LibElf *lib_elf);
            ~ElfHeader();

            bool load();
            bool save();
            bool is_ok();
            void clear();

            Elf_Half get_type() const;
            Elf_Half get_machine() const;
            Elf_Word get_version() const;
            Elf_Addr get_entry() const;
            Elf_Off get_phoff() const;
            Elf_Off get_shoff() const;
            Elf_Word get_flags() const;
            Elf_Half get_ehsize() const;
            Elf_Half get_phentsize() const;
            Elf_Half get_phnum() const;
            Elf_Half get_shentsize() const;
            Elf_Half get_shnum() const;
            Elf_Half get_shstrndx() const;
            
            void set_type(Elf_Half value);
            void set_machine(Elf_Half value);
            void set_version(Elf_Word value);
            void set_entry(Elf_Addr value);
            void set_phoff(Elf_Off value);
            void set_shoff(Elf_Off value);
            void set_flags(Elf_Word value);
            void set_ehsize(Elf_Half value);
            void set_phentsize(Elf_Half value);
            void set_phnum(Elf_Half value);
            void set_shentsize(Elf_Half value);
            void set_shnum(Elf_Half value);
            void set_shstrndx(Elf_Half value);

            bool check_type();
            bool check_machine();
            bool check_version();
            bool check_entry();
            bool check_phoff();
            bool check_shoff();
            bool check_flags();
            bool check_ehsize();
            bool check_phentsize();
            bool check_phnum();
            bool check_shentsize();
            bool check_shnum();
            bool check_shstrndx();

            std::string get_type_string() const;
            std::string get_machine_string() const;
            std::string get_version_string() const;
            std::string get_entry_string() const;
            std::string get_phoff_string() const;
            std::string get_shoff_string() const;
            std::string get_flags_string() const;
            std::string get_ehsize_string() const;
            std::string get_phentsize_string() const;
            std::string get_phnum_string() const;
            std::string get_shentsize_string() const;
            std::string get_shnum_string() const;
            std::string get_shstrndx_string() const;

        private:
            bool read();
            bool read_32_bit();
            bool read_64_bit();
            bool write();
            bool write_32_bit();
            bool write_64_bit();
            void convert();
            void convert_32_bit();
            void convert_64_bit();

        private:
            const Elf_Half EHSIZE_32BIT = 52;
            const Elf_Half EHSIZE_64BIT = 64;

            bool ok = false;

            LibElf *lib_elf;
            ElfIdentification *elf_identification;

            Elf_Half type = 0;
            Elf_Half machine = 0;
            Elf_Word version = 0;
            Elf_Addr entry = 0;
            Elf_Off phoff = 0;
            Elf_Off shoff = 0;
            Elf_Word flags = 0;
            Elf_Half ehsize = 0;
            Elf_Half phentsize = 0;
            Elf_Half phnum = 0;
            Elf_Half shentsize = 0;
            Elf_Half shnum = 0;
            Elf_Half shstrndx = 0;
    };
}
