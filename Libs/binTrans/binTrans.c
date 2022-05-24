void translateToBinary(int num, int addressInBin[16]) {

        for (int i = 15; i >= 0; i--) {
                if (num % 2 == 0) {
                        addressInBin[i] = 0;

                } else {
                        addressInBin[i] = 1;

                }

                num = num / 2;
        }
}

int translateToDecimal(int arrayInBin[8]) {
        int aux = 128;
        int numInDec = 0;

        for (int i = 0; i < 8; i++) {
                
                if (arrayInBin[i] == 1) {
                        numInDec += aux;
                }

                aux = aux / 2;
        }

        return numInDec;
}

void getPageAndOffset(int address, int returnArray[2]) {

        int addressInBin[16];
        int pageInBin[8], pageInDec = 0;
        int offsetInBin[8], offsetInDec = 0;

        translateToBinary(address, addressInBin);
        
        //Move page from address to a proper page array
        for (int i = 0; i < 8; i++) {
                pageInBin[i] = addressInBin[i];
        }

        //Move offset from address to a proper offset array
        int j = 0;
        for (int i = 8; i < 16; i++ ) {
                offsetInBin[j] = addressInBin[i];
                j++;
        }

        pageInDec = translateToDecimal(pageInBin);
        offsetInDec = translateToDecimal(offsetInBin);

        returnArray[0] = pageInDec;
        returnArray[1] = offsetInDec;
}