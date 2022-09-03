from enum import Enum
from PyAES import CAES, KeySize
from typing import List
from Packet import StrPacket


AESKey = "AES Encrypt Decrypt"
my_aes = CAES()
my_aes.SetKeys(KeySize.BIT128, AESKey)

packet = StrPacket()
packet.MAC =  "00-0C-29-D2-DC-FE"#"".join(['A'] * 20)
packet.IP = "192.168.0.156" #"".join(['B'] * 20)
packet.DoWork = "GetDriveInfo" #"".join(['C'] * 24)
packet.Message = "asdsaddddddddddddddddddddddddd" #"".join(['*'] * 960)

print("raw data:", packet.Fluent())
print()
encrypt = my_aes.EncryptBuffer(packet.Fluent())
print("encrypt:", encrypt)
print()

decrypt= my_aes.DecryptBuffer(encrypt)
print("decrypt:",decrypt)
print()

packet2 = StrPacket(decrypt)
print(f"MAC={packet2.MAC}({len(packet2.MAC)}), IP={packet2.IP}({len(packet2.IP)}), \
      DoWork={packet2.DoWork}({len(packet2.DoWork)}),Message={packet2.Message}({len(packet2.Message)})")