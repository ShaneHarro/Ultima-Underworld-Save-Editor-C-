#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include "ultimaio.h"

UltimaIO::UltimaIO():bytesLength{54}, xorIncrement{0x03} {


}


const char* UltimaIO::ReadBytes(const std::string &fileName) {

    //Set our private member for later use in writing to file
    saveFileName = fileName;

    //Start reading from file
    std::ifstream saveFile(saveFileName);
	
    //Check if file is OK and open for reading
    if (saveFile.is_open())	{
        std::cout << "File successfully open for reading!\n\n";
        
       //Read the bytes from file into our buffer
       char *buffer = new char[bytesLength];
       saveFile.read(buffer, bytesLength);
       saveFile.close();

       return buffer;
    }

    else {
        std::cout << "Error opening file. Are you sure the file exists?\n";
        exit(0);
    }

}

void UltimaIO::WriteBytes(const char encryptedData[]) {

    //Only way to write to a file without truncating the end is to open it in both read and write mode...
    std::fstream saveFile(saveFileName, std::ios::binary | std::ios::out | std::ios::in);
 
    //Check if file is OK and open for writing
    if (saveFile.is_open()) {
        std::cout << "File successfully open for writing!\n\n";

        //Set offset to byte after XOR key
        long pos = saveFile.tellp();
        saveFile.seekp(pos + 1);

        for (int i = 0; i < (bytesLength - 1); i++)
        {
            saveFile.write(&encryptedData[i], sizeof(char));
        }

        saveFile.close();
    }

    else {
        std::cout << "Error writing to file. Are you sure the file exists?\n";
        exit(0);
    }
}


const char* UltimaIO::DecryptBytes (const char byteData[]) {
    /**Set our XOR key and make room for the decyrpted keys
    *  We subtract one from size of array because we don't need
    *  to include the xorKey.
    */
    xorKey = byteData[0];

    //Subtract one from length since we don't want to include xorKey (first byte)
    char *decryptedBytes = new char[bytesLength  - 1];
    unsigned char currentXor = 0x00;

    for (int i = 0; i < bytesLength ; i++) {
        //Increment xorValue
        currentXor += xorIncrement;

        /**Xor'd with byteData[i+1] because we don't want to xor
        *  with first byte (which is the xor key)
        */
        decryptedBytes[i] = (xorKey + currentXor) xor byteData[i+1];   
    }
  
    return decryptedBytes;  
} 

const char* UltimaIO::EncryptBytes (const char byteData[]) const {

    char *encryptedBytes = new char[bytesLength];
    unsigned char currentXor = 0x00;

    for (int i = 0; i < bytesLength ; i++) {
        //Increment xorValue
        currentXor += xorIncrement;

        /**Don't need to "+1" like the decrypt method
        *  because the XOR was removed from it
        */
        encryptedBytes[i] = (xorKey + currentXor) xor byteData[i];   
    }

    //Remember that this array is returned without the XOR key!!!
    return encryptedBytes;
}


const std::string UltimaIO::getPlayerName (const char decryptedData[]) const {

    //Name is 14 bytes long in save file, including starting byte (0x01)
    const int nameLength = 14;
    std::string characterName;
  
    for (int i = 0; i < nameLength; i++) {
        characterName += decryptedData[i];
    }

    return characterName;    
} 


const std::string UltimaIO::getPlayerStats (const char decryptedData[]) const {

    //Create constant string array for stat names
    const std::string statNames[] = {"Strength: ", "Dexterity: ", "Intelligence: ", "Attack: ",
    "Defense: ", "Unarmed: ", "Sword: ", "Axe: ", "Mace: ", "Missile: ", "Mana: ", "Lore: ",
    "Casting: ", "Traps: ", "Search: ", "Track: ", "Sneak: ", "Repair: ", "Charm: ", "Picklock: ",
    "Acrobat: ", "Appraise: ", "Swimming: "};

    //Starting point in array to read stats from 
    const unsigned int statsStartingPoint = 30;
    std::string stats;

    for (int i = statsStartingPoint; i < bytesLength - 1 ; i++) {
        //Decrypted bytes must be casted to an int to show proper base 10 values
        stats += "[" + std::to_string(i -statsStartingPoint) + "] " + (statNames[i -statsStartingPoint] + std::to_string((int)decryptedData[i]) + "\n");
    }  
  
    return stats;
} 
