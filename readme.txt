Ultima Underworld Save Editor - Author: Shane Harrison

Description: A save game editor written in C++ for Ultima Underworld. Tested and working on Linux.
Compile with: g++ -o UUSE UUSE.cpp ultimaio.cpp ultimaio.h -std=c++11

*****************
*Documentation: *
*****************
**************************************************************************************************************************************************************
Like some other MS-DOS games of their day, Ultima Underworlds save files have the players data "encoded" or "encrypted" if you will,
using a simple XOR encoding. The first byte of PLAYER.DAT is the "XOR Key" value which tells us how to decode the rest of the file.
For each subsequent byte, we add 0x03 to the XOR key, and then perform an XOR bitwise operation with the current byte. An example
follows. Here is the first 3 bytes of a PLAYER.DAT file:

F9 AF 97 63 6B

'F9' in this case is the XOR Key, as it's the first byte in the file. And for each subsequent byte, we add 0x03 to the XOR Key and XOR it with the byte, like so:

(F9 + 0x03) XOR 0xAF = 0x53
(F9 + 0x06) XOR 0x97 = 0x68

etc...

**************************************************************************************************************************************************************
*****************
*Offsets:       *
*****************

Key            Offset
-------------------------
XOR value   |  0x00
-------------------------
Name        |  0x01 (14 bytes inclusive)
-------------------------
Strength    |  0x1F
-------------------------
Dexterity   |  0x20
-------------------------
Intelligence|  0x21
-------------------------
Attack      |  0x22
-------------------------
Defense     |  0x23
-------------------------
Unarmed     |  0x24
-------------------------
Sword       |  0x25
-------------------------
Mace        |  0x26
-------------------------
Missile     |  0x27
-------------------------
Mana        |  0x28
-------------------------
Lore        |  0x29
-------------------------
Casting     |  0x2A
-------------------------
Traps       |  0x2B
-------------------------
Search      |  0x2C
-------------------------
Track       |  0x2D
-------------------------
Sneak       |  0x2E
-------------------------
Repair      |  0x2F
-------------------------
Charm       |  0x30
-------------------------
Picklock    |  0x31
-------------------------
Acrobat     |  0x32
-------------------------
Appraise    |  0x33
-------------------------
Swimming    |  0x34
-------------------------

Many thanks to these people for their documentation:

ftp://files.chatnfiles.com/Infomagic-Windows/Infomagic-Games-for-Daze-Summer-95-1/EDITORS/UWEDITOR/UWEDITOR.TXT

http://bootstrike.com/Ultima/Online/uwformat.php

