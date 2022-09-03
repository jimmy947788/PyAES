
class StrPacket():
    """資料交換封包結構
    總長度1024
    """
    def __init__(self, data=None): 
        str_data = "" if data is None else "".join(data)
        
        self._mac = ""
        if data is not None:
            self._mac = str_data[0:20]
            end_index = self._mac.index('\0')
            self._mac = self._mac[:end_index]
         
        self._ip = ""
        if data is not None:
            self._ip = str_data[20:40]
            end_index = self._ip.index('\0')
            self._ip = self._ip[:end_index]
        
        self._doWork = ""
        if data is not None:
            self._doWork = str_data[40:64] 
            end_index = self._doWork.index('\0')
            self._doWork = self._doWork[:end_index]
        
        self._message = ""
        if data is not None:
            self._message = str_data[64:]
            end_index = self._message.index('\0')
            self._message = self._message[:end_index]
        
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
        """把結構內容攤平為一維陣列準備傳送 
        MAC(20) + IP(20) + DoWork(24) + Message(960) = list[1024] \r\n
        各欄位如果字源不足則補 '\\0' 結束字元\r\n
        Returns:
            list[str]: 所有欄位照順序的字串拼接
        """
        padding = '\0'
        full_str = (self.MAC.ljust(20, padding) + self.IP.ljust(20, padding) + \
            self.DoWork.ljust(24, padding) +   self.Message.ljust(960, padding))
        print(full_str)
        return list(full_str)