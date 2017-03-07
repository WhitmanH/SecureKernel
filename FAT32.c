unsigned char FAT_table[sector_size];
unsigned int fat_offset = active_cluster * 4;
unsigned int fat_sector = first_fat_sector + (fat_offset / sector_size);
unsigned int ent_offset = fat_offset % sector_size;
 
//at this point you need to read from sector "fat_sector" on the disk into "FAT_table".
 
//remember to ignore the high 4 bits.
unsigned int table_value = *(unsigned int*)&FAT_table[ent_offset] & 0x0FFFFFFF;
 
//the variable "table_value" now has the information you need about the next cluster in the chain.
