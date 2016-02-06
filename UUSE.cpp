#include <iostream>
#include <fstream>
#include <string>
#include "ultimaio.h"

int main(int argc, char **argv) {

    //Command line argument checking
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " PLAYER.DAT" << std::endl;
        return 0;
    }

    else {
        std::cout <<
        "\n******************************\n"
        "Ultima Underworld Save Editor\n"
        "Author: Shane Harrison\n"
        "******************************\n";


        //************************************
        //*** FILE READING AND DECRYPTION ****
        //************************************

        UltimaIO ultimaIO;

        //Start to read our bytes    
        const std::string fileName = argv[1]; 
        const char *byteData = ultimaIO.ReadBytes(fileName);

        //Decrypt our bytes
        const char *decryptedBytes = ultimaIO.DecryptBytes(byteData);
        //delete[] byteData;

        //Display character data
        std::cout << "Player name: " << ultimaIO.getPlayerName(decryptedBytes) << "\n\n";
        std::cout << ultimaIO.getPlayerStats(decryptedBytes);


        //************************************
        //* CREATE ARRAY TO HOLD NEW STATS ***
        //************************************

        const unsigned int bytesFromStart = 53;
        char *changedBytes = new char[bytesFromStart];
    
        //Copy decrypted bytes into changed bytes for editing
        for (int i = 0; i < bytesFromStart; i++) {
            changedBytes[i] = decryptedBytes[i];
        } 

        
        //************************************
        //*** USER DATA INPUT  ***************
        //************************************

        std::cout << "Enter which stat to edit ([0] for strength, [1] for dexterity, etc..) :\n";
        unsigned int statSelect;
        std::cin >> statSelect;
     
        //Max and min of user input choice
        const unsigned int selectMaxLimit = 22;
        const unsigned int selectMinLimit = 0;
       
        //Check if input is valid and select stat
        while (std::cin.fail() || statSelect > selectMaxLimit || statSelect < selectMinLimit) {
           std::cout << "\nInvalid input. Please enter a valid value: " << "\n"; 
           std::cin.clear();
           std::cin.ignore();
           std::cin >> statSelect;
        }

        std::cout << "Enter new desired value for this stat (0-250):\n";

        //Max and min level of stat allowed
        const unsigned int statMaxLimit = 250;
        const unsigned int statMinLimit = 0;

        unsigned int newValue;
        std::cin >> newValue;

        //Enter new value for stat
        while (std::cin.fail() || newValue > statMaxLimit || newValue < statMinLimit) {
           std::cout << "\nInvalid input. Please enter a valid value: " << "\n"; 
           std::cin.clear();
           std::cin.ignore();
           std::cin >> newValue;
        }

        //************************************
        //*** FILE ENCRYPTION AND WRITING ****
        //************************************

        //Place new stat value as replacement in array (don't forget to cast it back to char)
        const unsigned int statsStartingPoint = 30;
        changedBytes[statSelect + statsStartingPoint] = (char)newValue;
        
        //Return encrypted bytes for our changed values ready for writing
        const char *encryptedBytes = ultimaIO.EncryptBytes(changedBytes);

        //Write the bytes
        ultimaIO.WriteBytes(encryptedBytes);

        std::cout << "\n\nFile successfully written to!" << std::endl;

        return 0;
    }
}

