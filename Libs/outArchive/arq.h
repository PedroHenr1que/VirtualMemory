void writeInOutArchive(int virtualAddress, int physicalAddress, int value);
void writeEndArchive(double totalOfVirtualAddressesTranslated, double totalPageFaults,
double totalPageFaultRate, double tlbHits, double tlbHitRate);