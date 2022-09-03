# PyAES for pybind11

把原本C++版本的 AES class用 pybind11 編譯成python模組

## Prerequisites

* A compiler with C++11 support
* Pip 10+ or CMake >= 3.4 (or 3.8+ on Windows, which was the first version to support VS 2015)
* Ninja or Pip 10+


## Installation

Just clone this repository and pip install. 加上 `--recursive` 參數就是要把 pybind11 的 submodule 抓下來:

```bash
git clone --recursive https://github.com/jimmy947788/PyAES.git
pip install ./PyAES
```

With the `setup.py` file included in this example, the `pip install` command will
invoke CMake and build the pybind11 module as specified in `CMakeLists.txt`.



## Building the documentation

Documentation for the example project is generated using Sphinx. Sphinx has the
ability to automatically inspect the signatures and documentation strings in
the extension module to generate beautiful documentation in a variety formats.
The following command generates HTML-based reference documentation; for other
formats please refer to the Sphinx manual:

 - `cd cmake_example/docs`
 - `make html`


## License

Pybind11 is provided under a BSD-style license that can be found in the LICENSE
file. By using, distributing, or contributing to this project, you agree to the
terms and conditions of this license.


## 使用範例

python 範例程式在 [RUN_AES.py](example\RUN_AES.py)
```python
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
encrypt = myAES.EncryptBuffer(packet.Fluent())
print("encrypt:", encrypt)
print()

decrypt= myAES.DecryptBuffer(encrypt)
print("decrypt:",decrypt)
print()

packet2 = StrPacket(decrypt)
print(f"MAC={packet2.MAC}({len(packet2.MAC)}), IP={packet2.IP}({len(packet2.IP)}), \
      DoWork={packet2.DoWork}({len(packet2.DoWork)}),Message={packet2.Message}({len(packet2.Message)})")
```

[`cibuildwheel`]:          https://cibuildwheel.readthedocs.io
[FAQ]: http://pybind11.rtfd.io/en/latest/faq.html#working-with-ancient-visual-studio-2009-builds-on-windows
[vs2015_runtime]: https://www.microsoft.com/en-us/download/details.aspx?id=48145
[scikit-build]: https://scikit-build.readthedocs.io/en/latest/
