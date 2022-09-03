
class StrPacket():
    def __init__(self, data=None): 
        str_data = "" if data is None else "".join(data)
        self._mac = "" if data is None else str_data[0:20]
        self._ip = "" if data is None else str_data[20:40]
        self._doWork = "" if data is None else str_data[40:64] 
        self._message = "" if data is None else str_data[64:]
        
    @property
    def MAC(self):
        return self._mac

    @MAC.setter
    def MAC(self, value):
        self._mac = value
        
    @property
    def IP(self):
        return self._ip

    @IP.setter
    def IP(self, value):
        self._ip = value
        
    @property
    def DoWork(self):
        return self._doWork

    @DoWork.setter
    def DoWork(self, value):
        self._doWork = value
    
    @property
    def Message(self):
        return self._message

    @Message.setter
    def Message(self, value):
        self._message = value
        
    def Fluent(self):
        padding = '\0'
        full_str = (self.MAC.ljust(20, padding) + self.IP.ljust(20, padding) + \
            self.DoWork.ljust(24, padding) +   self.Message.ljust(960, padding))
        print(full_str)
        return list(full_str)