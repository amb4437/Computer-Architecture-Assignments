#include "vmm.h"
#include "console.h"
#include "stdint.h"
#include "machine.h"

#define MISSING() do { \
putStr(__FILE__); \
putStr(":"); \
putDec(__LINE__); \
putStr(" is missing\n"); \
shutdown(); \
} while (0)

/* Each frame is 4K */
#define FRAME_SIZE (1 << 12)

/* A table contains 4K/4 = 1K page table entries */
#define TABLE_ENTRIES (FRAME_SIZE / sizeof(uint32_t))

/* A table, either a PD, or a PT */
typedef struct {
    uint32_t entries[TABLE_ENTRIES];
} table_s;



/* Address of first avaialble frame */
uint32_t avail = 0x100000;

/* pointer to page directory */
table_s *pd = 0;

/* zero-fill a frame */
static void zeroFrame(uint32_t ptr) {
    char* p = (char*) ptr;
    for (int i=0; i<FRAME_SIZE; i++) {
        *p = 0;
    }
}

/* The world's simplest frame allocator */
uint32_t vmm_frame(void) {
    uint32_t p = avail;
    avail += FRAME_SIZE;
    zeroFrame(p);
    return p;
}
/* handle a page fault */
void pageFault(uint32_t addr) {
    sayHex("page fault @ ", addr);
    uint32_t faultaddr = vmm_frame();
    vmm_map(addr, faultaddr);
    
    
}

/* Return a pointer to the PD, allocate it if you have to */
table_s* getPD() {
    if (pd == 0) {
        pd = (table_s*) vmm_frame();
    }
    return pd;
}
table_s* getPT(uint32_t va) {
    
    uint32_t newaddress = va >> 22;
    
    table_s* newPD = getPD();
    
    uint32_t PDE = (uint32_t) newPD->entries[newaddress];
    
    
    if (PDE == 0){
        PDE = vmm_frame() + 1;
        getPD()->entries[newaddress] = PDE;}
    
    return (table_s*) (PDE & 0xfffff000);;
    
}

/* Create a new mapping from va to pa */
void vmm_map(uint32_t va, uint32_t pa) {
    
    table_s* pageTable = getPT(va);
    
    uint32_t pageTableAddr = ((va >> 12) & 0x3ff);
    uint32_t pageTableEntry = (pa & 0xfffff000) + 1;

    pageTable->entries[pageTableAddr] = pageTableEntry;
    
}

/* check if the page containing the given PA is dirty */
int vmm_dirty(uint32_t va) {
    
    
    table_s* pageTable = getPT(va);
    uint32_t pageTableAddr = (va >> 12) & 0x03ff;
    uint32_t pageTableEntry = (uint32_t) pageTable->entries[pageTableAddr];

    uint32_t dirtyBit = pageTableEntry & 0x40;
    return dirtyBit >> 6;
    
}

/* check if the page containing the given PA has been accessed */
int vmm_accessed(uint32_t va) {
    
    table_s* pageTable = getPT(va);
    uint32_t pageTableAddr = (va >> 12) & 0x03ff;
    uint32_t pageTableEntry = (uint32_t) pageTable->entries[pageTableAddr];
    
    uint32_t accessed = pageTableEntry & 0x20;
    
    
    return accessed >> 5;
    
    
}

/* return the PA that corresponds to the given VA, 0xffffffff is not mapped */
uint32_t vmm_pa(uint32_t va) {
    
    table_s* pageTable = getPT(va);
    uint32_t pageTableAddr = (va >> 12) & 0x03ff;
    uint32_t pageTableEntry = (uint32_t) pageTable->entries[pageTableAddr];
    
    uint32_t pageAddr;
    
    if (pageTableEntry & 0x1){
        
        pageAddr = (uint32_t) ((pageTableEntry) >> 12);
        
        pageAddr = pageAddr << 12;
        
        pageAddr = pageAddr | (va & 0xfff);}
    
    else {
        pageAddr = 0xffffffff;}
 
    return pageAddr;
}

/* unmap the given va */
void vmm_unmap(uint32_t va) {
    
    
    table_s* pageTable = getPT(va);
    uint32_t pageTableAddr = (va >> 12) & 0x03ff;
    uint32_t pageTableEntry = (uint32_t) pageTable->entries[pageTableAddr];
    
    
    pageTableEntry = pageTableEntry >> 1;
    pageTableEntry = pageTableEntry << 1;
    
    
    pageTable->entries[pageTableAddr] = pageTableEntry;

    invlpg(va);
}

/* print the contents of the page table */
void vmm_dump() {
    table_s *pd = getPD();
    sayHex("PD @ ",(uint32_t) pd);
    for (int i=0; i<TABLE_ENTRIES; i++) {
        uint32_t e = pd->entries[i];
        if (e != 0) {
            putStr("    ");
            putHex(i);
            sayHex(") PDE = ",e);
            table_s * pt = (table_s*) (e & 0xfffff000);
            for (int j=0; j<TABLE_ENTRIES; j++) {
                uint32_t e = pt->entries[j];
                if (e != 0) {
                    putStr("        ");
                    putHex(j);
                    sayHex(") PTE = ",e);
                }
            }
        }
    }
}