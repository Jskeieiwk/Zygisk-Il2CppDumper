//
// Created by Perfare on 2020/7/4.
//

#ifndef ZYGISK_IL2CPPDUMPER_IL2CPP_DUMP_H
#define ZYGISK_IL2CPPDUMPER_IL2CPP_DUMP_H

void il2cpp_api_init(void *handle);

// True only when every export the dump needs was resolved and the VM thread is attached.
bool il2cpp_api_ready();

void il2cpp_dump(const char *outDir);

#endif //ZYGISK_IL2CPPDUMPER_IL2CPP_DUMP_H
