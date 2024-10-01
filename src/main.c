#include "../include/elf.h"
#include "../include/print.h"

#define SIZE 64

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("[x] Usage: %s <FILE>\n", argv[0]);
    return 1;
  }
  
  char*   filename      = argv[1];
  int     fd            = 0;
  void*   file    = NULL;
  unsigned char magic[] = {'\x7F', '\x45', '\x4C', '\x46'};
  struct stat st        = { 0 }; 

  if (stat(filename, &st) == 0) {
    if (st.st_size < (off_t)SIZE){
      printf("[x] File not big enough to store the ELF header\n");
      return 1;
    }
  } else {
    printf("[x] Error getting file size\n");
    exit(EXIT_FAILURE);
  }

  fd = open(filename, O_RDONLY);
  if (fd < 0) {
    printf("[x] Failed to open file\n");
    exit(EXIT_FAILURE);
  }

  file = mmap(NULL, (size_t)st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (file == MAP_FAILED) {
    printf("[x] Failed to map header to memory\n");
    exit(EXIT_FAILURE);
  }

  Elf64_Ehdr* elf_header = (Elf64_Ehdr*)file;
  
  for (int i = 0; i < 4; i++) {
    if (elf_header->e_ident[i] != magic[i]) {
      printf("[x] Not a ELF file\n");
      goto cleanup;
    }
  }
  
  puts("┌─────────| ELF Header |─────────┐");
  printELF(elf_header);

  puts("┌─────────| Program Headers |─────────┐");
  for (int i = 0; i < elf_header->e_phnum; ++i) {
    Elf64_Phdr* program_header = (Elf64_Phdr*)((char*)file + elf_header->e_phoff + (elf_header->e_phentsize * i));
    printf("PROGRAM HEADER: 0x%02x\n", i);
    printPH(program_header);
  }

cleanup:
  if (munmap(file, (size_t)st.st_size) == -1) {
    printf("[x] Failed to unmap header from memory\n");
    exit(EXIT_FAILURE);
  }
  
  close(fd);
  return 0;
}

