from PyAES import CAES, KeySize
from Packet import StrPacket

AESKey = "AES Encrypt Decrypt"
myAES = CAES()
myAES.SetKeys(KeySize.BIT128, AESKey)

packet = StrPacket()
packet.MAC =  "00-0C-29-D2-DC-FE"#"".join(['A'] * 20)
packet.IP = "192.168.0.156" #"".join(['B'] * 20)
packet.DoWork = "GetDriveInfo" #"".join(['C'] * 24)
packet.Message = "asdsaddddddddddddddddddddddddd" #"".join(['*'] * 960)

print("raw data:", packet.Fluent())
print()
ciphertext = myAES.EncryptBuffer(packet.Fluent())
print("encrypt:", ciphertext)
print()

# ciphertext 是 str list 沒有辦法給socket send
# 透過這樣轉換 bytearray 才能送出
ascii_list = [ord(data) for data in ciphertext]
send_data = bytearray(ascii_list)
    

plaintext= myAES.DecryptBuffer(ciphertext)
print(f"decrypt:{plaintext}, type:{ type(plaintext)}")
print()

packet2 = StrPacket(plaintext)
print(f"MAC={packet2.MAC}({len(packet2.MAC)}), IP={packet2.IP}({len(packet2.IP)}), \
      DoWork={packet2.DoWork}({len(packet2.DoWork)}),Message={packet2.Message}({len(packet2.Message)})")

