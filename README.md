## ModFinder

ModFinder is a usermode tool for detecting memory regions that are injected via the manual-map method.

Typically, the only addresses you will receive are from manual-mapping flags. Rarely, you may receive a few other results of false catches. These are usually very easy to distinguish from the region you're actually looking for. An upside to ModFinder is that even if the entire optional headers page is erased, you will still be informed of regions that correspond with the first region. The primary reason that ModFinder distinguishes from other manual-map detection programs, is due to how well it performs at detecting regions which were mapped.

Unknowncheats thread

- https://www.unknowncheats.me/forum/anti-cheat-bypass/508290-modfinder-tool-locating-mapped-memory.html

The following injectors have been tested and have successfully been detected:
- Extreme Injector (Latest)
- Xenos (Latest)
- Memject (Latest)
- AlisaAlis (Latest)

## Features
- Mapped memory region enumeration.
- Valid DOS header enumeration.
- Ignore linked module addresses.

## Compatible
- Windows 10 (64-bit)
- Windows 10 (32-bit)
- Every Windows version before or after 10 has not been tested, but should cause no issues.


## To Do
- Display only relevant addresses. (fix / improve false positives)
- Check for DLL manifest string.

## Preview
![5mHMw0QRUc](https://user-images.githubusercontent.com/110091391/181724080-afb7a0b8-b341-4408-b498-792a7711c6cd.png)
