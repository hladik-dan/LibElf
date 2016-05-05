LibElf
===================


LibElf is C++ library for simple manipulation with ELF files.

----------


Examples
-------------

Load data from file
``` cpp
#include "lib_elf.h"

LibElf::LibElf lib_elf;
if (!lib_elf.load("filename"))
    return false;
```
<br />
Get data
``` cpp
LibElf::ElfIdentification *elf_identification = lib_elf.get_elf_identification();

std::cout << elf_identification->get_version() << std::endl;
// Output: 1

std::cout << elf_identification->get_version_string() << std::endl;
// Output: Current Version
```
<br />
Set data
``` cpp
LibElf::ElfIdentification *elf_identification = lib_elf.get_elf_identification();

std::cout << elf_identification->get_version() << std::endl;
// Output: 1

// Set version to 0
elf_identification->set_version(0);

std::cout << elf_identification->get_version() << std::endl;
// Output: 0
```
<br />
Check data
``` cpp
LibElf::ElfIdentification *elf_identification = lib_elf.get_elf_identification();

std::cout << elf_identification->get_version() << std::endl;
// Output: 1

bool ok_1 = elf_identification->check_version();
// ok_1 = true

// Set version to 0
elf_identification->set_version(0);

bool ok_2 = elf_identification->check_version();
// ok_2 = false
```
