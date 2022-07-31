# FineDust

## Overview

My first project.  
It is simple C++ project that uses Class & Open API service.  
Due to this project, I can unserstand Class, url-encoding, utf-encoding and Open API.

Class�� Open Api ���񽺸� Ȱ���� ���� ù��° ������Ʈ �Դϴ�.  
C++�� Open Api���� �̼����� �����͸� �Ľ��ϴ� ������ ����, Class �� url-encoding, utf-encoding, Open Api � ���� ������ �� �־����ϴ�.  
<br/>

## References

* [libcurl examples](https://curl.se/libcurl/c/example.html)  
  * https://stackoverflow.com/questions/50013204/jsoncpp-to-parse-from-url
  * https://stackoverflow.com/questions/19582838/add-paramethers-to-libcurl-get-in-c/19582883#19582883
* [cp949 <-> UTF-8 / using libiconv](https://webnautes.tistory.com/1466)
* [URL-encode](http://codepad.org/lCypTglt)
* [Unicode to UTF-8](https://stackoverflow.com/questions/2619897/how-can-i-deal-with-this-encoding)
* https://3001ssw.tistory.com/79  
<br/>

## How To

### Servie key

����Ű�� [���������� ����](https://www.data.go.kr/index.do) ȸ������ �� 
[[����������]](https://www.data.go.kr/data/15073877/openapi.do), 
[[����������]](https://www.data.go.kr/data/15073861/openapi.do)���� ����� �߱޹����� �� �ֽ��ϴ�.  
�߱� ���� ����Ű�� `src/search.cpp` ������ ������ ���� �κп� �Է��Ͻø� �˴ϴ�.  
```C++
char* servicekey1(void) {
	std::string apiKey1 = "{���⿡ ����Ű�� �Է��ϼ��� [https://www.data.go.kr/data/15073877/openapi.do]}";
	std::string param_apikey1 = "servicekey=" + apiKey1;
    static char ch_apiKey1[256];
    strcpy_s(ch_apiKey1, param_apikey1.c_str());
    return ch_apiKey1;
}


char* servicekey2(void) {
	std::string apiKey2 = "{���⿡ ����Ű�� �Է��ϼ��� [https://www.data.go.kr/data/15073861/openapi.do]}";
	std::string param_apikey2 = "servicekey=" + apiKey2;
    static char ch_apiKey2[256];
    strcpy_s(ch_apiKey2, param_apikey2.c_str());
    return ch_apiKey2;
}
```  
  
### Build

�� ������Ʈ�� `win32` ȯ�濡�� [CMake](https://cmake.org/)�� [VcPkg](https://github.com/microsoft/vcpkg)�� ����Ͽ� ������ ���� ������ �� �ֽ��ϴ�.  

```console
$ cmake -B build -S . "-DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]\vcpkg\scripts\buildsystems\vcpkg.cmake"
$ cmake --build build --config debug
```  
  
### Run
```console
$ .\build\debug\finedust.exe
```
<br/>

***

## Dependencies

This project uses external libraries:

- cURL, inspired by MIT/X license,https://curl.se/docs/copyright.html
- Jsoncpp, MIT license, https://github.com/open-source-parsers/jsoncpp
- libiconv, LGPL, https://www.gnu.org/software/libiconv/


## License

FineDust is released under the unlicense. In short, use for any purpose 
as long as you don't hold me responsible for anything. It would be 
nice if you'd toss me a mail if you play with this thing.

