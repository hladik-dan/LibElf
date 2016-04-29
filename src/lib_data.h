#pragma once

#include <map>

typedef uint64_t Elf_Addr;
typedef uint32_t Elf32_Addr;
typedef uint64_t Elf64_Addr;

typedef uint64_t Elf_Off;
typedef uint32_t Elf32_Off;
typedef uint64_t Elf64_Off;

typedef uint16_t Elf_Half;
typedef uint16_t Elf32_Half;
typedef uint16_t Elf64_Half;

typedef uint32_t Elf_Word;
typedef uint32_t Elf32_Word;
typedef uint32_t Elf64_Word;

typedef int32_t Elf_Sword;
typedef int32_t Elf32_Sword;
typedef int32_t Elf64_Sword;

typedef uint64_t Elf_Xword;
typedef uint64_t Elf64_Xword;

typedef int64_t Elf_Sxword;
typedef int64_t Elf64_Sxword;

#define EI_MAG0 0
#define EI_MAG1 1
#define EI_MAG2 2
#define EI_MAG3 3
#define EI_CLASS 4
#define EI_DATA 5
#define EI_VERSION 6
#define EI_OSABI 7
#define EI_ABIVERSION 8
#define EI_PAD 9
#define EI_NIDENT 16

#define ELFMAG0 0x7F
#define ELFMAG1 'E'
#define ELFMAG2 'L'
#define ELFMAG3 'F'

#define ELFCLASSNONE 0
#define ELFCLASS32 1
#define ELFCLASS64 2

#define ELFDATANONE 0
#define ELFDATA2LSB 1
#define ELFDATA2MSB 2

#define EV_NONE 0
#define EV_CURRENT 1

#define ELFOSABI_NONE 0
#define ELFOSABI_HPUX 1
#define ELFOSABI_NETBSD 2
#define ELFOSABI_GNU 3
#define ELFOSABI_SOLARIS 6
#define ELFOSABI_AIX 7
#define ELFOSABI_IRIX 8
#define ELFOSABI_FREEBDS 9
#define ELFOSABI_TRU64 10
#define ELFOSABI_MODESTO 11
#define ELFOSABI_OPENBSD 12
#define ELFOSABI_OPENVMS 13
#define ELFOSABI_NSK 14
#define ELFOSABI_AROS 15
#define ELFOSABI_FENIXOS 16
#define ELFOSABI_CLOUDABI 17
#define ELFOSABI_OPENVOS 18

#define ET_NONE 0
#define ET_REL 1
#define ET_EXEC 2
#define ET_DYN 3
#define ET_CORE 4
#define ET_LOOS 0xFE00
#define ET_HIOS 0xFEFF
#define ET_LOPROC 0xFF00
#define ET_HIPROC 0xFFFF

#define EM_NONE 0
#define EM_68K 4
#define EM_X86_64 62

#define SHT_NULL 0
#define SHT_PROGBITS 1
#define SHT_SYMTAB 2
#define SHT_STRTAB 3
#define SHT_RELA 4
#define SHT_HASH 5
#define SHT_DYNAMIC 6
#define SHT_NOTE 7
#define SHT_NOBITS 8
#define SHT_REL 9
#define SHT_SHLIB 10
#define SHT_DYNSYM 11
#define SHT_INIT_ARRAY 14
#define SHT_FINI_ARRAY 15
#define SHT_PREINIT_ARRAY 16
#define SHT_GROUP 17
#define SHT_SYMTAB_SHNDX 18
#define SHT_LOOS 0x60000000
#define SHT_HIOS 0x6FFFFFFF
#define SHT_LOPROC 0x70000000
#define SHT_HIPROC 0x7FFFFFFF
#define SHT_LOUSER 0x80000000
#define SHT_HIUSER 0xFFFFFFFF

#define SHF_WRITE 0x1
#define SHF_ALLOC 0x2
#define SHF_EXECINSTR 0x4
#define SHF_MERGE 0x10
#define SHF_STRINGS 0x20
#define SHF_INFO_LINK 0x40
#define SHF_LINK_ORDER 0x80
#define SHF_OS_NONCONFORMING 0x100
#define SHF_GROUP 0x200
#define SHF_TLS 0x400
#define SHF_COMPRESSED 0x800
#define SHF_MASKOS 0x0FF00000
#define SHF_MASKPROC 0xF0000000

#define PT_NULL 0
#define PT_LOAD 1
#define PT_DYNAMIC 2
#define PT_INTERP 3
#define PT_NOTE 4
#define PT_SHLIB 5
#define PT_PHDR 6
#define PT_TLS 7
#define PT_LOOS 0x60000000
#define PT_HIOS 0x6FFFFFFF
#define PT_LOPROC 0x70000000
#define PT_HIPROC 0x7FFFFFFF

#define PF_X 0x1
#define PF_W 0x2
#define PF_R 0x4
#define PF_MASKOS 0x0FF00000
#define PF_MASKPROC 0xF0000000

const std::map<unsigned char, const char *> ei_class =
{
    { ELFCLASSNONE, "Invalid class" },
    { ELFCLASS32, "ELF32" },
    { ELFCLASS64, "ELF64" },
};

const std::map<unsigned char, const char *> ei_data =
{
    { ELFDATANONE, "Invalid data encoding" },
    { ELFDATA2LSB, "Little endian" },
    { ELFDATA2MSB, "Big Endian" },
};

const std::map<unsigned char, const char *> ei_version =
{
    { EV_NONE, "Invalid version" },
    { EV_CURRENT, "Current version" },
};

const std::map<unsigned char, const char *> ei_osabi =
{
    { ELFOSABI_NONE, "System V" },
    { ELFOSABI_HPUX, "HP-UX" },
    { ELFOSABI_NETBSD, "NetBSD" },
    { ELFOSABI_GNU, "GNU/Linux" },
    { ELFOSABI_SOLARIS, "Solaris" },
    { ELFOSABI_AIX, "AIX" },
    { ELFOSABI_IRIX, "IRIX" },
    { ELFOSABI_FREEBDS, "FreeBSD" },
    { ELFOSABI_TRU64, "TRU64" },
    { ELFOSABI_MODESTO, "Modesto" },
    { ELFOSABI_OPENBSD, "OpenBSD" },
    { ELFOSABI_OPENVMS, "OpenVMS" },
    { ELFOSABI_NSK, "Non-Stop Kernel" },
    { ELFOSABI_AROS, "Research OS" },
    { ELFOSABI_FENIXOS, "FenixOS" },
    { ELFOSABI_CLOUDABI, "CloudABI" },
    { ELFOSABI_OPENVOS, "OpenVOS" },
};

const std::map<Elf_Half, const char *> e_type =
{
    { ET_NONE, "No file type" },
    { ET_REL, "Relocatable file" },
    { ET_EXEC, "Executable file" },
    { ET_DYN, "Shared object file" },
    { ET_CORE, "Core file" },
};

const std::map<Elf_Half, const char *> e_machine =
{
    { EM_NONE, "No machine" },
    { EM_68K, "Motorola 68000" },
    { EM_X86_64, "Advanced Micro Devices X86-64"},
};

const std::map<Elf_Word, const char *> sh_type =
{
    { SHT_NULL, "NULL" },
    { SHT_PROGBITS, "PROGBITS" },
    { SHT_SYMTAB, "SYMTAB" },
    { SHT_STRTAB, "STRTAB" },
    { SHT_RELA, "RELA" },
    { SHT_HASH, "HASH" },
    { SHT_DYNAMIC, "DYNAMIC" },
    { SHT_NOTE, "NOTE" },
    { SHT_NOBITS, "NOBITS" },
    { SHT_REL, "REL" },
    { SHT_SHLIB, "SHLIB" },
    { SHT_DYNSYM, "DYNSYM" },
    { SHT_INIT_ARRAY, "INIT_ARRAY" },
    { SHT_FINI_ARRAY, "FINI_ARRAY" },
    { SHT_PREINIT_ARRAY, "PREINIT_ARRAY" },
    { SHT_GROUP, "GROUP" },
    { SHT_SYMTAB_SHNDX, "SYMTAB_SHNDX" },
};

const std::map<Elf_Xword, const char *> sh_flags =
{
    { SHF_WRITE, "WRITE" },
    { SHF_ALLOC, "ALLOC" },
    { SHF_EXECINSTR, "EXECINSTR" },
    { SHF_MERGE, "MERGE" },
    { SHF_STRINGS, "STRINGS" },
    { SHF_INFO_LINK, "INFO_LINK" },
    { SHF_LINK_ORDER, "LINK_ORDER" },
    { SHF_OS_NONCONFORMING, "OS_NONCONFORMING" },
    { SHF_GROUP, "GROUP" },
    { SHF_TLS, "TLS" },
    { SHF_COMPRESSED, "COMPRESSED" },
    { SHF_MASKOS, "OS specific" },
    { SHF_MASKPROC, "Processor specific" },
};

const std::map<Elf_Word, const char *> p_type =
{
    { PT_NULL, "NULL" },
    { PT_LOAD, "LOAD" },
    { PT_DYNAMIC, "DYNAMIC" },
    { PT_INTERP, "INTERP" },
    { PT_NOTE, "NOTE" },
    { PT_SHLIB, "SHLIB" },
    { PT_PHDR, "PHDR" },
    { PT_TLS, "TLS" },
};

const std::map<Elf_Word, const char *> p_flags =
{
    { PF_X, "EXECUTE" },
    { PF_W, "WRITE" },
    { PF_R, "READ" },
    { PF_MASKOS, "OS specific" },
    { PF_MASKPROC, "Processor specific" },
};
