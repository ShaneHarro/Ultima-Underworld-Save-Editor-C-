#ifndef ULTIMAIO_H
#define ULTIMAIO_H

#include <fstream>
#include <vector>
#include <string>

class UltimaIO {

public:
    /**
    *Class constructor
    */
    UltimaIO();

    /**
    * Takes in save file and reads save file bytes in their unencrypted form
    * @param fileName	the save file to read
    */
    const char* ReadBytes(const std::string &fileName);

    /**
    * Take the save file and write new edited bytes
    * @param encryptedData	the array to write to file
    */
    void WriteBytes(const char encryptedData[]);
       
    /**
    * Decrypt our bytes from save file
    * @param 	byteData	char array to decrypt
    * @return	char* array of decrypted bytes	
    */
    const char* DecryptBytes (const char byteData[]);

    /**
    * Encrypt bytes of new stats 
    * @param 	byteData	array to encrypt
    * @return	char* array of encrypted bytes	
    */
    const char* EncryptBytes (const char byteData[]) const;

    /**
    * Get the players name
    * @param 	decryptedData	decrypted array to read name from
    * @return	string which contains the players name	
    */
    const std::string getPlayerName (const char decryptedData[]) const;


    /**
    * Get the players stats
    * @param 	decryptedData	decrypted array to read name from
    * @return	string which contains the players stats
    */
    const std::string getPlayerStats (const char decryptedData[]) const;

private:
    std::string saveFileName;
    const int bytesLength;
    unsigned char xorKey;
    unsigned const char xorIncrement;
	
};

#endif
